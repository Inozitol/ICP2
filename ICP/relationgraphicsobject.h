#pragma once

#include <QGraphicsObject>

#include "classgraphicsobject.h"

class RelationGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    RelationGraphicsObject(std::pair<ClassGraphicsObject*,ClassGraphicsObject*>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    std::pair<MetaClass::Name, MetaClass::Name> GetRelationParts();
public slots:
    void updateLine();

private:
    std::pair<ClassGraphicsObject*,ClassGraphicsObject*> _relation;
    QLineF relationLine;
};
