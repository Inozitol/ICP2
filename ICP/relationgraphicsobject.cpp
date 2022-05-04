#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> relation, Relation::Type type, int index)
    : _relation(relation),
      _index(index),
      _graphicsLine({_relation.first->GetItemCenter(), _relation.second->GetItemCenter()}, this),
      _type(type),
      _dstSymb(new QGraphicsPolygonItem)
{
    setZValue(-1);
    dstCollisionPoint = new QPointF;
    InitPolygon();
    InitActions();
    InitSymbol();
}

int RelationGraphicsObject::GetIndex(){
    return _index;
}

void RelationGraphicsObject::InitPolygon(){

    QPolygonF polygon;
    switch(_type){
        case Relation::Gener:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);
            _dstSymb->setBrush({Qt::gray, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;

        case Relation::Compo:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(2*POLYGON_SIDE, 0.0)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);

            _dstSymb->setBrush({Qt::gray, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;

        case Relation::Aggre:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(2*POLYGON_SIDE, 0.0)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);

            _dstSymb->setBrush({Qt::white, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;
    }

    _dstSymb->setPolygon(polygon);
    _dstSymb->setParentItem(this);
    _dstSymb->setPos(*dstCollisionPoint);
}

void RelationGraphicsObject::InitActions(){
    _deleteRelation = new QAction(tr("Delete relation"));
    connect(_deleteRelation, &QAction::triggered, this, [this](){emit killSelf(this);});
}

void RelationGraphicsObject::InitSymbol(){
    QRectF bndRectDst = _relation.second->boundingRect();
    bndRectDst.moveTo(_relation.second->pos());

    LineRectCollision(dstCollisionPoint, _graphicsLine.line(), bndRectDst);

    _dstSymb->setPos(*dstCollisionPoint);
    _dstSymb->setRotation((-_graphicsLine.line().angle())+180.0);
}

RelationGraphicsObject::~RelationGraphicsObject(){
    delete(dstCollisionPoint);
    delete(_dstSymb);
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }
}

void RelationGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_deleteRelation);
    menu.exec(event->screenPos());
    event->accept();
}

[[nodiscard]] QRectF RelationGraphicsObject::boundingRect() const{
    return _graphicsLine.boundingRect();
}

std::pair<MetaClass::Name, MetaClass::Name> RelationGraphicsObject::GetRelationParts(){
    return std::make_pair(_relation.first->GetClassName(), _relation.second->GetClassName());
}

void RelationGraphicsObject::updateLine(){
    prepareGeometryChange();
    _graphicsLine.setLine({_relation.first->GetItemCenter(), _relation.second->GetItemCenter()});
    QRectF bndRectDst = _relation.second->boundingRect();
    bndRectDst.moveTo(_relation.second->pos());

    LineRectCollision(dstCollisionPoint, _graphicsLine.line(), bndRectDst);

    _dstSymb->setPos(*dstCollisionPoint);
    _dstSymb->setRotation((-_graphicsLine.line().angle())+180.0);
    update();
}

void RelationGraphicsObject::LineLineCollision(QPointF* pointBuff, QLineF line1, QLineF line2){
    qreal x1 = line1.x1();
    qreal y1 = line1.y1();
    qreal x2 = line1.x2();
    qreal y2 = line1.y2();

    qreal x3 = line2.x1();
    qreal y3 = line2.y1();
    qreal x4 = line2.x2();
    qreal y4 = line2.y2();

    qreal uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    qreal uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

    if(uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1){
        pointBuff->setX(x1 + (uA * (x2-x1)));
        pointBuff->setY(y1 + (uA * (y2-y1)));
    }
}

void RelationGraphicsObject::LineRectCollision(QPointF* pointBuff, QLineF line, QRectF rect){
    QLineF leftL = 		QLineF(rect.topLeft(), 		rect.bottomLeft());
    QLineF rightL = 	QLineF(rect.topRight(), 	rect.bottomRight());
    QLineF topL = 		QLineF(rect.topLeft(), 		rect.topRight());
    QLineF bottomL =	QLineF(rect.bottomLeft(), 	rect.bottomRight());

    LineLineCollision(pointBuff, line, leftL);
    LineLineCollision(pointBuff, line, rightL);
    LineLineCollision(pointBuff, line, topL);
    LineLineCollision(pointBuff, line, bottomL);
}
