#include "sequencediagramscene.h"

SequenceDiagramScene::SequenceDiagramScene(QWidget* parent)
    :QGraphicsScene(parent), _parent(parent),_environment(Environment::GetEnvironment())
{
    setBackgroundBrush({B_CLR});
    InitActions();
}

SequenceDiagramScene::~SequenceDiagramScene(){
    delete(_newLifeline);
}

void SequenceDiagramScene::InitActions(){
    _newLifeline = new QAction(tr("New Lifeline"), this);
    connect(_newLifeline, &QAction::triggered, this, &SequenceDiagramScene::NewLifeline);
}

void SequenceDiagramScene::drawBackground(QPainter* painter, const QRectF& rect){
    QGraphicsScene::drawBackground(painter, rect);

    const uint8_t grid_freq = 20;
    auto leftBord = static_cast<int>(rect.left());
    auto rightBord = static_cast<int>(rect.right());
    auto topBord = static_cast<int>(rect.top());
    auto downBord = static_cast<int>(rect.bottom());

    const auto f_left = leftBord - (leftBord % grid_freq);
    const auto f_top = topBord - (topBord % grid_freq);

    for(auto y = f_top; y <= downBord; y += grid_freq) {
        std::vector<QPoint> vec;
        for (auto x = f_left; x <= rightBord; x += grid_freq) {
            auto point = QPoint(x,y);
            vec.push_back(point);
        }
        painter->setPen(F_CLR);
        painter->drawPoints(vec.data(), int(vec.size()));
    }
}

void SequenceDiagramScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    /*
    auto item = static_cast<ClassGraphicsObject*>(itemAt(event->scenePos().toPoint(),QTransform()));
    if(item){
        item->contextMenuEvent(event);
        return;
    }
    */

    QMenu menu;
    menu.addAction(_newLifeline);
    menu.exec(event->screenPos());
    event->accept();
}

void SequenceDiagramScene::NewLifeline(){
    LifelineDialog diagram(_parent);
    if(diagram.exec()){
        auto lifeline = diagram.GetLifeline();
        _environment->GetSequenceDiagram()->InsertLifeline(lifeline);
        RedrawScene();
    }
}

void SequenceDiagramScene::RedrawScene(){
    emit clear();

    qreal xPos = H_MARGIN;
    qreal yPos = V_MARGIN;
    for(auto lifeline : _environment->GetSequenceDiagram()->GetLifelines()){
        auto lifelinegraphics = new LifelineGraphicsObject(lifeline);
        lifelinegraphics->setPos({xPos, yPos});
        addItem(lifelinegraphics);
        _lifelineGraphics[lifeline->GetName()] = lifelinegraphics;

        xPos += H_MARGIN + lifelinegraphics->boundingRect().width();
    }

    yPos += LifelineGraphicsObject::height() + V_MARGIN;

    for(auto event : _environment->GetSequenceDiagram()->GetTimeline()){
        switch(event->GetType()){
            case SequenceEvent::Activation:
            {
                auto activation = std::static_pointer_cast<SequenceActivation>(event);
                SequenceLifeline::Name name = activation->GetLifeline()->GetName();
                if(_actPoints.count(name)){
                    // TODO Error
                    // Actor is already activated
                }else{
                    _actPoints[name] = yPos;
                }
            }
            break;

            case SequenceEvent::Deactivation:
            {
                auto deactivation = std::static_pointer_cast<SequenceDeactivation>(event);
                SequenceLifeline::Name name = deactivation->GetLifeline()->GetName();
                if(_actPoints.count(name)){

                    qreal actPoint = _actPoints.at(name);
                    _actPoints.erase(name);

                    qreal ll_middle = _lifelineGraphics.at(deactivation->GetLifeline()->GetName())->middle();

                    QRectF rect = {
                        ll_middle - 10.0,
                        actPoint,
                        20.0,
                        yPos-actPoint
                    };

                    addRect(rect, QPen(), QBrush(Qt::red));

                }else{
                    // TODO Error
                    // Actor is not activated
                }

            }
            break;

            case SequenceEvent::Message:
                auto message = std::static_pointer_cast<SequenceMessage>(event);
                SequenceLifeline::Name origin_ll_name = message->GetOrigin()->GetName();
                SequenceLifeline::Name destination_ll_name = message->GetDestination()->GetName();
                qreal ll_origin_middle = _lifelineGraphics.at(origin_ll_name)->middle();
                qreal ll_destination_middle = _lifelineGraphics.at(destination_ll_name)->middle();

                QLineF line = {
                    ll_origin_middle, 		yPos,		// Origin point
                    ll_destination_middle, 	yPos		// Destination point
                };

                addLine(line);

                QPainterPath arrow;
                arrow.moveTo({ll_destination_middle-6.0, yPos-6.0});
                arrow.lineTo({ll_destination_middle, yPos});
                arrow.lineTo({ll_destination_middle-6.0, yPos+6.0});
                arrow.lineTo({ll_destination_middle-6.0, yPos-6.0});
                arrow.setFillRule(Qt::WindingFill);

                addPath(arrow, QPen(), QBrush(Qt::SolidPattern));



            break;
        }
        yPos += V_MARGIN;
    }

    for(auto lifeline : _environment->GetSequenceDiagram()->GetLifelines()){
        QPointF line_start = {
            _lifelineGraphics.at(lifeline->GetName())->middle(),
            V_MARGIN + LifelineGraphicsObject::height()
        };

        QPointF line_end = {
            _lifelineGraphics.at(lifeline->GetName())->middle(),
            yPos
        };

        addLine({line_start, line_end})->setZValue(-1);
    }
}
