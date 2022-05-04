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
    RelationGraphicsObject(std::pair<ClassGraphicsObject*,ClassGraphicsObject*>, Relation::Type, int);
    ~RelationGraphicsObject();
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    std::pair<MetaClass::Name, MetaClass::Name> GetRelationParts();
    int GetIndex();

public slots:
    void updateLine();

private:
    void InitPolygon();
    void InitActions();
    void InitSymbol();

    inline void LineLineCollision(QPointF*, QLineF, QLineF);
    inline void LineRectCollision(QPointF*, QLineF, QRectF);

    std::pair<ClassGraphicsObject*,ClassGraphicsObject*> _relation;
    int _index;
    QGraphicsLineItem _graphicsLine;
    QPointF* dstCollisionPoint;
    Relation::Type _type;
    QGraphicsPolygonItem* _dstSymb;
    QAction* _deleteRelation;

    const qreal POLYGON_SIDE = 15.0;

signals:
    void killSelf(RelationGraphicsObject*);
};
