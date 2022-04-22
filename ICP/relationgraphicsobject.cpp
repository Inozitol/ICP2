#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> relation)
    : _relation(relation)
{
    setZValue(-1);
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }

    //relationLine.setLine(_relation.first->GetItemCenter(), _relation.second->GetItemCenter());
    relationLine.setP1(_relation.first->GetItemCenter());
    relationLine.setP2(_relation.second->GetItemCenter());
    painter->setBrush({WHOLEBOX_CLR});
    painter->drawLine(relationLine);

}

[[nodiscard]] QRectF RelationGraphicsObject::boundingRect() const{
    QRectF rectangle;
    float x1 = _relation.first->GetItemCenter().x();
    float y1 = _relation.first->GetItemCenter().y();
    float x2 = _relation.second->GetItemCenter().x();
    float y2 = _relation.second->GetItemCenter().y();

    if(x1 < x2 && y1 < y2){
        rectangle.setTopLeft(_relation.first->GetItemCenter());
        rectangle.setBottomRight(_relation.second->GetItemCenter());
    } else if(x1 < x2 && y1 > y2){
        rectangle.setBottomLeft(_relation.first->GetItemCenter());
        rectangle.setTopRight(_relation.second->GetItemCenter());
    } else if(x1 > x2 && y1 < y2){
        rectangle.setTopRight(_relation.first->GetItemCenter());
        rectangle.setBottomLeft(_relation.second->GetItemCenter());
    } else if(x1 > x2 && y1 > y2){
        rectangle.setBottomRight(_relation.first->GetItemCenter());
        rectangle.setTopLeft(_relation.second->GetItemCenter());
    }
    return rectangle;
}

std::pair<MetaClass::Name, MetaClass::Name> RelationGraphicsObject::GetRelationParts(){
    return std::make_pair(_relation.first->GetClassName(), _relation.second->GetClassName());
}

void RelationGraphicsObject::updateLine(){
    prepareGeometryChange();
    relationLine.setP1(_relation.first->GetItemCenter());
    relationLine.setP2(_relation.second->GetItemCenter());
    update();
}
