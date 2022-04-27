#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> relation)
    : _relation(relation),
      _graphicsLine({_relation.first->GetItemCenter(), _relation.second->GetItemCenter()}, this)
{
    setZValue(-1);
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }

    painter->setBrush({WHOLEBOX_CLR});
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
    update();
}
