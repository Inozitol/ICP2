#pragma once

#include <QGraphicsObject>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>

#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"

class RelationGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    RelationGraphicsObject(std::pair<ClassGraphicsObject*,ClassGraphicsObject*>, Relation::Type);
    ~RelationGraphicsObject();
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    std::pair<MetaClass::Name, MetaClass::Name> GetRelationParts();

public slots:
    void updateLine();

private:
    void InitPolygon();

    inline void LineLineCollision(QPointF*, QLineF, QLineF);
    inline void LineRectCollision(QPointF*, QLineF, QRectF);

    std::pair<ClassGraphicsObject*,ClassGraphicsObject*> _relation;
    QGraphicsLineItem _graphicsLine;
    QPointF* srcCollisionPoint;
    Relation::Type _type;
    QGraphicsPolygonItem* _dstSymb;

    const qreal POLYGON_SIDE = 15.0;
};
