#include "classdiagramscene.h"

ClassDiagramScene::ClassDiagramScene(QWidget* parent)
    : QGraphicsScene(parent), _parent(parent), _environment(Environment::GetEnvironment())
{
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
    auto item = itemAt(event->scenePos().toPoint(), QTransform());

    qDebug() << item->data(Qt::UserRole).toInt();

    switch(item->data(Qt::UserRole).toInt()){

    case GraphicsItem::Class:
    {
        auto classitem = static_cast<ClassGraphicsObject*>(item);
        classitem->contextMenuEvent(event);
        return;

    }
        break;

    case GraphicsItem::Relation:
    {
        //auto relationitem = static_cast<RelationGraphicsObject*>(item);
        //relationitem->contextMenuEvent(event);
        event->accept();
    }
        break;

    default:
    {
        QMenu menu;
        menu.addAction(_newClass);
        menu.exec(event->screenPos());
        event->accept();
    }
        break;
    }

}

void ClassDiagramScene::NewClass(){
    ClassEditDialog diagram(_parent);
    if(diagram.exec()){
        auto metaclass = diagram.GetClassPtr();
        _environment->GetClassDiagram()->InsertClass(diagram.GetClassPtr());
        PlaceClass(metaclass);
        emit ClassUpdate();
    }
}

void ClassDiagramScene::PlaceClass(std::shared_ptr<MetaClass> metaclass){
    auto newclass = new ClassGraphicsObject(metaclass);
    newclass->setData(Qt::UserRole, GraphicsItem::Class);
    connect(newclass, &ClassGraphicsObject::killSelf, this, &ClassDiagramScene::DeleteClass);
    addItem(newclass);
    _graphicsObjectMap.insert(std::make_pair(metaclass->GetName(), newclass));
}

void ClassDiagramScene::DeleteClass(ClassGraphicsObject* classitem){
    removeItem(classitem);
    _environment->GetClassDiagram()->EraseClass(classitem->GetClassName());
    emit ClassUpdate();
    _graphicsObjectMap.erase(classitem->GetClassName());
}

void ClassDiagramScene::ClearScene(){
    _graphicsObjectMap.clear();
}

void ClassDiagramScene::PlaceRelation(std::shared_ptr<Relation> relation){
    auto relationPair = std::make_pair(_graphicsObjectMap.at(relation->GetSource()->GetName()), _graphicsObjectMap.at(relation->GetDestination()->GetName()));
    auto newrelation = new RelationGraphicsObject(relationPair);
    newrelation->setData(Qt::UserRole, GraphicsItem::Relation);
    connect(relationPair.first, &QGraphicsObject::xChanged, newrelation, &RelationGraphicsObject::updateLine);
    connect(relationPair.first, &QGraphicsObject::yChanged, newrelation, &RelationGraphicsObject::updateLine);
    connect(relationPair.second, &QGraphicsObject::xChanged, newrelation, &RelationGraphicsObject::updateLine);
    connect(relationPair.second, &QGraphicsObject::yChanged, newrelation, &RelationGraphicsObject::updateLine);
    addItem(newrelation);
}

QWidget* ClassDiagramScene::GetParent(){
    return _parent;
}
