#include "sequencediagramscene.h"

SequenceDiagramScene::SequenceDiagramScene(QWidget* parent)
    :QGraphicsScene(parent), _parent(parent), _font(FONT), _environment(Environment::GetEnvironment())
{
    _font.setPointSize(FONT_SIZE);
    setBackgroundBrush({B_CLR});
    InitActions();
}

SequenceDiagramScene::~SequenceDiagramScene(){
    delete(_newLifeline);
    delete(_newEvent);
}

void SequenceDiagramScene::InitActions(){
    _newLifeline = new QAction(tr("New Lifeline"), this);
    connect(_newLifeline, &QAction::triggered, this, &SequenceDiagramScene::NewLifeline);

    _newEvent = new QAction(tr("New Event"), this);
    connect(_newEvent, &QAction::triggered, this, &SequenceDiagramScene::NewEvent);
}

void SequenceDiagramScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){

    auto item = itemAt(event->scenePos().toPoint(), QTransform());
    if(item->data(Qt::UserRole) == GraphicsItem::Lifeline){
        auto lifelineitem = static_cast<LifelineGraphicsObject*>(item);
        lifelineitem->contextMenuEvent(event);
        return;
    }

    QMenu menu;
    menu.addAction(_newLifeline);
    menu.addAction(_newEvent);
    menu.exec(event->screenPos());
    event->accept();
}

void SequenceDiagramScene::RedrawScene(){
    emit clear();

    qreal xPos = H_MARGIN;
    qreal yPos = V_MARGIN;
    for(auto lifeline : _environment->GetSequenceDiagram()->GetLifelines()){
        auto lifelinegraphics = new LifelineGraphicsObject(lifeline.second);
        lifelinegraphics->setData(Qt::UserRole, GraphicsItem::Lifeline);
        connect(lifelinegraphics, &LifelineGraphicsObject::killSelf, this, &SequenceDiagramScene::DeleteLifeline);
        lifelinegraphics->setPos({xPos, yPos});
        addItem(lifelinegraphics);
        _lifelineGraphics[lifeline.first] = lifelinegraphics;

        xPos += H_MARGIN + lifelinegraphics->boundingRect().width();
    }

    yPos += LifelineGraphicsObject::height() + V_MARGIN;

    SequenceEvent::Type prev_type = SequenceEvent::Nop;
    for(auto event : _environment->GetSequenceDiagram()->GetTimeline()){
        switch(event->GetType()){
            case SequenceEvent::Activation:
            {
                /*
                if(prev_type != SequenceEvent::Deactivation){
                    yPos += V_MARGIN;
                }
                */

                auto activation = std::static_pointer_cast<SequenceActivation>(event);
                SequenceLifeline::Name name = activation->GetLifeline()->GetName();
                if(!_actPoints.count(name)){
                    _actPoints[name] = yPos;
                }
            }
            break;

            case SequenceEvent::Deactivation:
            {
            /*
                if(prev_type != SequenceEvent::Activation){
                    yPos += V_MARGIN;
                }
            */
                if(prev_type == SequenceEvent::Activation){
                    break;
                }

                auto deactivation = std::static_pointer_cast<SequenceDeactivation>(event);
                SequenceLifeline::Name name = deactivation->GetLifeline()->GetName();
                if(_actPoints.count(name)){

                    qreal actPoint = _actPoints.at(name);
                    _actPoints.erase(name);

                    qreal ll_middle = _lifelineGraphics.at(deactivation->GetLifeline()->GetName())->middle();

                    QRectF rect = {
                        ll_middle - 5.0,
                        actPoint,
                        10.0,
                        yPos-actPoint
                    };

                    addRect(rect, QPen(), QBrush(Qt::red));

                }else{
                    // TODO Error
                    // Actor is not activated
                }
            }
            break;

            // Return event will be static_cased into Message event, but headers are basically the same, so it works
            // ...still feels like sticking a fork into an outlet tho
            case SequenceEvent::Return:
            case SequenceEvent::Message:
            {
            /*
                if(prev_type == SequenceEvent::Message){
                    yPos += V_MARGIN;
                }
            */

                auto message = std::static_pointer_cast<SequenceMessage>(event);
                SequenceLifeline::Name origin_ll_name = message->GetOrigin()->GetName();
                SequenceLifeline::Name destination_ll_name = message->GetDestination()->GetName();
                qreal ll_origin_middle = _lifelineGraphics.at(origin_ll_name)->middle();
                qreal ll_destination_middle = _lifelineGraphics.at(destination_ll_name)->middle();

                QLineF line = {
                    ll_origin_middle, 		yPos,		// Origin point
                    ll_destination_middle, 	yPos		// Destination point
                };

                if(event->GetType() == SequenceEvent::Return){
                    addLine(line, QPen(Qt::DashLine))->setZValue(1);
                }else{
                    addLine(line)->setZValue(1);
                }

                if(ll_destination_middle > ll_origin_middle){

                    QPainterPath arrow;
                    arrow.moveTo({ll_destination_middle-6.0, yPos-6.0});
                    arrow.lineTo({ll_destination_middle, yPos});
                    arrow.lineTo({ll_destination_middle-6.0, yPos+6.0});
                    arrow.lineTo({ll_destination_middle-6.0, yPos-6.0});
                    arrow.setFillRule(Qt::WindingFill);

                    addPath(arrow, QPen(), QBrush(Qt::SolidPattern))->setZValue(1);

                    QFontMetrics fm(_font);
                    QString msg_str = QString::fromStdString(message->GetMessage());
                    auto textitem = addText(msg_str, _font);
                    qreal linelen = ll_destination_middle - ll_origin_middle;
#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
                    textitem->setPos(ll_origin_middle + (linelen - fm.width(msg_str))/2, yPos - fm.height() - 3);
#else
                    textitem->setPos(ll_origin_middle + (linelen - fm.horizontalAdvance(msg_str))/2, yPos - fm.height() - 3);
#endif

                }else{

                    QPainterPath arrow;
                    arrow.moveTo({ll_destination_middle+6.0, yPos-6.0});
                    arrow.lineTo({ll_destination_middle, yPos});
                    arrow.lineTo({ll_destination_middle+6.0, yPos+6.0});
                    arrow.lineTo({ll_destination_middle+6.0, yPos-6.0});
                    arrow.setFillRule(Qt::WindingFill);

                    addPath(arrow, QPen(), QBrush(Qt::SolidPattern))->setZValue(1);

                    QFontMetrics fm(_font);
                    QString msg_str = QString::fromStdString(message->GetMessage());
                    auto textitem = addText(msg_str, _font);
                    qreal linelen = ll_origin_middle - ll_destination_middle;
#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
                    textitem->setPos(ll_destination_middle + (linelen - fm.width(msg_str))/2, yPos - fm.height() - 3);
#else
                    textitem->setPos(ll_destination_middle + (linelen - fm.horizontalAdvance(msg_str))/2, yPos - fm.height() - 3);
#endif
                }

            }
            break;

            case SequenceEvent::Nop:
                yPos += V_MARGIN;
            break;
        }
        yPos += V_MARGIN;
        prev_type = event->GetType();
    }

    yPos += V_MARGIN;

    for(auto lifeline : _environment->GetSequenceDiagram()->GetLifelines()){
        QPointF line_start = {
            _lifelineGraphics.at(lifeline.first)->middle(),
            V_MARGIN + LifelineGraphicsObject::height()
        };

        QPointF line_end = {
            _lifelineGraphics.at(lifeline.first)->middle(),
            yPos
        };

        addLine({line_start, line_end})->setZValue(-1);
    }
}

void SequenceDiagramScene::DataChange(){
    emit SceneUpdate();
}

void SequenceDiagramScene::NewLifeline(){
    LifelineDialog dialog(_parent);
    if(dialog.exec()){
        auto lifeline = dialog.GetLifeline();
        _environment->GetSequenceDiagram()->InsertLifeline(lifeline);
        RedrawScene();
        emit SceneUpdate();
    }
}

void SequenceDiagramScene::DeleteLifeline(LifelineGraphicsObject* lifeline){
    removeItem(lifeline);
    _environment->GetSequenceDiagram()->EraseLifeline(lifeline->GetName());
    RedrawScene();
    emit SceneUpdate();
}

void SequenceDiagramScene::NewEvent(){
    EventDialog dialog(_parent);
    if(dialog.exec()){
        auto event = dialog.GetEvent();
        _environment->GetSequenceDiagram()->EventPush(event);
        RedrawScene();
        emit SceneUpdate();
    }
}
