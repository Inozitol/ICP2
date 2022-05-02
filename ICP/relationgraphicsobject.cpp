#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> relation, Relation::Type type)
    : _relation(relation),
      _graphicsLine({_relation.first->GetItemCenter(), _relation.second->GetItemCenter()}, this),
      _type(type)
{
    setZValue(-1);
    srcCollisionPoint = new QPointF;
    LineRectCollision(srcCollisionPoint, _graphicsLine.line(), _relation.first->boundingRect());
}

RelationGraphicsObject::~RelationGraphicsObject(){
    delete(srcCollisionPoint);
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }

    painter->setBrush({WHOLEBOX_CLR});
    painter->setPen({Qt::black, 10});
    painter->drawPoint(*srcCollisionPoint);
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
    QRectF bndRectSrc = _relation.first->boundingRect();
    bndRectSrc.moveTo(_relation.first->pos());

    LineRectCollision(srcCollisionPoint, _graphicsLine.line(), bndRectSrc);
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
