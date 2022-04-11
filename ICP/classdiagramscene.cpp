#include "classdiagramscene.h"

ClassDiagramScene::ClassDiagramScene(QWidget* parent)
    : QGraphicsScene(parent), _parent(parent), _environment(Environment::GetEnvironment()){
    setSceneRect(sceneX, sceneY, sceneW, sceneH);
    setBackgroundBrush({B_CLR});
    InitActions();
}

ClassDiagramScene::~ClassDiagramScene(){
    delete(_newClass);
}

void ClassDiagramScene::InitActions(){
    _newClass = new QAction(tr("New Class"), this);
    connect(_newClass, &QAction::triggered, this, &ClassDiagramScene::NewClass);
}

void ClassDiagramScene::drawBackground(QPainter* painter, const QRectF& rect){
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

void ClassDiagramScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_newClass);
    menu.exec(event->screenPos());
    event->accept();
}

void ClassDiagramScene::NewClass(){
    ClassEditDialog diagram(_parent);
    if(diagram.exec()){
        _environment->GetClass()->InsertClass(diagram.GetClassPtr());
        emit ClassChange();
    }
}
