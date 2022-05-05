#pragma once

#define FONT "Arial"

#include <QGraphicsObject>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>

#include <cmath>

#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"

class RelationGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    RelationGraphicsObject(std::shared_ptr<Relation> relation, std::pair<ClassGraphicsObject*, ClassGraphicsObject*> pair);
    ~RelationGraphicsObject();
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    std::pair<MetaClass::Name, MetaClass::Name> GetRelationParts();
    int GetIndex();

public slots:
    void updateLine();

private:
    void InitSymbol();
    void InitCircles();
    void InitActions();
    void UpdateSymbol();
    void UpdateCircles();

    inline void LineLineCollision(QPointF*, QLineF, QLineF);
    inline void LineRectCollision(QPointF*, QLineF, QRectF);

    std::pair<ClassGraphicsObject*,ClassGraphicsObject*> _pair;
    std::shared_ptr<Relation> _relation;
    int _index;
    QGraphicsLineItem _graphicsLine;
    QPointF* _srcCollisionPoint;
    QPointF* _dstCollisionPoint;
    QPointF* _srcCirclePoint;
    QPointF* _dstCirclePoint;
    QGraphicsPolygonItem* _dstSymb;
    QGraphicsEllipseItem* _srcCircle;
    QGraphicsEllipseItem* _dstCircle;
    Relation::Type _type;
    QAction* _deleteRelation;
    QFont _font;

    const qreal POLYGON_SIDE = 15.0;
    const qreal CIRCLE_RADIUS = 20.0;
    const qreal CIRCLE_DST_DISTANCE = 65.0;
    const qreal CIRCLE_SRC_DISTANCE = 40.0;
    const qreal LEN_THRESHOLD = 200.0;

signals:
    void killSelf(RelationGraphicsObject*);
};
