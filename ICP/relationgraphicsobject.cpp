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
    int x1 = _relation.first->GetItemCenter().x();
    int y1 = _relation.first->GetItemCenter().y();
    int x2 = _relation.second->GetItemCenter().x();
    int y2 = _relation.second->GetItemCenter().y();
    if(x1 <= x2 && y1 <= y2){
        rectangle.setBottomLeft(_relation.first->GetItemCenter());
        rectangle.setTopRight(_relation.second->GetItemCenter());
        if(x1 == x2) rectangle.setWidth(1);
        if(y1 == y2) rectangle.setHeight(1);
    } else if(x1 <= x2 && y1 >= y2){
        rectangle.setTopLeft(_relation.first->GetItemCenter());
        rectangle.setBottomRight(_relation.second->GetItemCenter());
        if(x1 == x2) rectangle.setWidth(1);
        if(y1 == y2) rectangle.setHeight(1);
    } else if(x1 >= x2 && y1 <= y2){
        rectangle.setTopLeft(_relation.second->GetItemCenter());
        rectangle.setBottomRight(_relation.first->GetItemCenter());
        if(x1 == x2) rectangle.setWidth(1);
        if(y1 == y2) rectangle.setHeight(1);
    } else if(x1 >= x2 && y1 >= y2){
        rectangle.setBottomLeft(_relation.second->GetItemCenter());
        rectangle.setTopRight(_relation.first->GetItemCenter());
        if(x1 == x2) rectangle.setWidth(1);
        if(y1 == y2) rectangle.setHeight(1);
    }

    return rectangle;
}

std::pair<MetaClass::Name, MetaClass::Name> RelationGraphicsObject::GetRelationParts(){
    return std::make_pair(_relation.first->GetClassName(), _relation.second->GetClassName());
}

void RelationGraphicsObject::updateLine(){
    relationLine.setP1(_relation.first->GetItemCenter());
    relationLine.setP2(_relation.second->GetItemCenter());
    update();
}
