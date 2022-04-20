#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> relation)
    : _relation(relation)
{
    //counting size
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }

    QLine relationLine(10,10,2000,2000);
    painter->setBrush({WHOLEBOX_CLR});
    painter->drawLine(relationLine);

}

[[nodiscard]] QRectF RelationGraphicsObject::boundingRect() const{
    QRectF rectangle;
    if(_relation.first->GetItemCenter().x() < _relation.second->GetItemCenter().x()){
       rectangle.setTopLeft(_relation.first->GetItemCenter());
       rectangle.setBottomRight(_relation.second->GetItemCenter());
    } else {
       rectangle.setTopLeft(_relation.second->GetItemCenter());
       rectangle.setBottomRight(_relation.first->GetItemCenter());
    }
    return rectangle;
}

std::pair<MetaClass::Name, MetaClass::Name> RelationGraphicsObject::GetRelationParts(){
    return std::make_pair(_relation.first->GetClassName(), _relation.second->GetClassName());
}
