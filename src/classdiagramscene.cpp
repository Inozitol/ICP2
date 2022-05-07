#include "classdiagramscene.h"

ClassDiagramScene::ClassDiagramScene(QWidget* parent)
    : QGraphicsScene(parent),
      _parent(parent),
      _environment(Environment::GetEnvironment()),
      _relationPair(nullptr, nullptr)
{
    setBackgroundBrush({B_CLR});
    InitActions();
}

ClassDiagramScene::~ClassDiagramScene(){
    delete(_newClass);
}

void ClassDiagramScene::InitActions(){
    _newClass = new QAction(tr("New Class"), this);
    connect(_newClass, &QAction::triggered, this, &ClassDiagramScene::CreateClass);
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
        auto relationitem = static_cast<RelationGraphicsObject*>(item);
        relationitem->contextMenuEvent(event);
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

void ClassDiagramScene::CreateClass(){
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
    newclass->setPos(metaclass->GetPos());
    newclass->setData(Qt::UserRole, GraphicsItem::Class);
    connect(newclass, &ClassGraphicsObject::killSelf, this, &ClassDiagramScene::DeleteClass);
    connect(newclass, &ClassGraphicsObject::initRelation, this, &ClassDiagramScene::CreateRelation);
    connect(newclass, &ClassGraphicsObject::changed, this, &ClassDiagramScene::ClassUpdate);
    connect(this, &ClassDiagramScene::SyncClassPos, newclass, &ClassGraphicsObject::SyncClassPos);
    addItem(newclass);
    _graphicsObjectMap.insert(std::make_pair(metaclass->GetName(), newclass));
}

void ClassDiagramScene::DeleteClass(ClassGraphicsObject* classitem){
    removeItem(classitem);
    _environment->GetClassDiagram()->EraseClass(classitem->GetClassName());
    emit ClassUpdate();
    _graphicsObjectMap.erase(classitem->GetClassName());
    for(const auto &relation : classitem->GetRelations()){
        DeleteRelation(relation);
    }
    delete(classitem);
}

void ClassDiagramScene::ClearScene(){
    _graphicsObjectMap.clear();
}

void ClassDiagramScene::PlaceRelation(std::shared_ptr<Relation> relation){
    auto relationPair = std::make_pair(_graphicsObjectMap.at(relation->GetSource()->GetName()), _graphicsObjectMap.at(relation->GetDestination()->GetName()));
    auto newrelation = new RelationGraphicsObject(relation, relationPair);
    addItem(newrelation);

    newrelation->setData(Qt::UserRole, GraphicsItem::Relation);
    relationPair.first->AddRelation(newrelation);
    relationPair.second->AddRelation(newrelation);

    connect(relationPair.first, 	&QGraphicsObject::xChanged, 		newrelation, 	&RelationGraphicsObject::updateLine);
    connect(relationPair.first, 	&QGraphicsObject::yChanged, 		newrelation, 	&RelationGraphicsObject::updateLine);
    connect(relationPair.second, 	&QGraphicsObject::xChanged, 		newrelation, 	&RelationGraphicsObject::updateLine);
    connect(relationPair.second, 	&QGraphicsObject::yChanged, 		newrelation, 	&RelationGraphicsObject::updateLine);
    connect(newrelation, 			&RelationGraphicsObject::killSelf, 	this, 			&ClassDiagramScene::DeleteRelation);
}

void ClassDiagramScene::DeleteRelation(RelationGraphicsObject* item){
    int index = item->GetIndex();
    removeItem(item);
    _environment->GetClassDiagram()->EraseRelation(index);
    auto pair = item->GetPair();
    pair.first->RemoveRelation(item);
    pair.second->RemoveRelation(item);
    delete(item);
}

QWidget* ClassDiagramScene::GetParent(){
    return _parent;
}

void ClassDiagramScene::CreateRelation(ClassGraphicsObject* item){
    if(!_relationPair.first){
        _relationPair.first = item;
        views().at(0)->setCursor(Qt::PointingHandCursor);
    }else{
        if(_relationPair.first == item){
            ResetRelation();
        }else{
            _relationPair.second = item;
            RelationDialog dialog(_relationPair, _parent);
            if(dialog.exec()){
                std::shared_ptr<Relation> relation = dialog.GetRelation();
                _environment->GetClassDiagram()->InsertRelation(relation);
                PlaceRelation(relation);
                ResetRelation();
            }
        }
    }
}

void ClassDiagramScene::ResetRelation(){
    _relationPair = {nullptr, nullptr};
    views().at(0)->setCursor(Qt::ArrowCursor);
}

void ClassDiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    auto item = itemAt(event->scenePos().toPoint(), QTransform());
    if(!item){
        ResetRelation();
        event->ignore();
        return;
    }

    switch(item->data(Qt::UserRole).toInt()){

    case GraphicsItem::Class:
    {
        auto classitem = static_cast<ClassGraphicsObject*>(item);
        CreateRelation(classitem);
    }
    break;

    default:
        ResetRelation();
    break;

    }
}
