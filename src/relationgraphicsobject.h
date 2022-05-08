// Autor: xhorac19, xmurga01

#pragma once

#define FONT "Arial"

#include <QGraphicsObject>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>

#include <cmath>

#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"

class ClassGraphicsObject;

///
/// \brief Class representing the graphic objects for relations.
///
class RelationGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param relation shared pointer to the relation.
    /// \param pair pair of linked graphic objects.
    RelationGraphicsObject(std::shared_ptr<Relation> relation, std::pair<ClassGraphicsObject*, ClassGraphicsObject*> pair);
    /// \brief Class destructor.
    ~RelationGraphicsObject();
    /// \brief Redefined method for obtaining a rectangle within which the graphic object is.
    /// \return the rectangle.
    [[nodiscard]] QRectF boundingRect() const override;
    /// \brief Redefined Qt method for painting graphic objects onto the scene.
    /// \param painter Qt painter.
    /// \param option Qt paint options - not used.
    /// \param widget Qt paint widget - not used.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    /// \brief Redefined method defining context menu event behaviour.
    /// \param event event for the context menu in the graphic object.
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    /// \brief Method for obtaining the two parts of the relation.
    /// \return pair of meta class names.
    std::pair<MetaClass::Name, MetaClass::Name> GetRelationParts();
    /// \brief Method for obtaining the index of a relation.
    /// \return the index of the relation.
    int GetIndex();
    /// \brief Method for getting a pair of connected class graphics objects
    /// \return Pair of class graphics objects
    std::pair<ClassGraphicsObject*, ClassGraphicsObject*> GetPair();

public slots:
    /// \brief Slot for adjusting the relation line when class objects are moved.
    void updateLine();

private:
    /// \brief Method for initializing different relation UML symbols.
    void InitSymbol();
    /// \brief Method for initializing relation cardinality circles.
    void InitCircles();
    /// \brief Method for initializing relation related actions.
    void InitActions();
    /// \brief Method for initializing relation message box.
    void InitMessage();
    /// \brief Method for updating relation symbols when class graphic objects are moved.
    void UpdateSymbol();
    /// \brief Method for updating cardinality circles when class graphic objects are moved.
    void UpdateCircles();
    /// \brief Method for updating message box.
    void UpdateMessage();
    /// \brief Method for determining point of contact of two lines.
    /// \param pointBuffer buffer for the point of contact.
    /// \param line1 first line.
    /// \param line2 second line.
    inline void LineLineCollision(QPointF* pointBuff, QLineF line1, QLineF line2);
    /// \brief Method for determining point of contact between a line and a rectangle.
    /// \param pointBuff buffer for the point of contact.
    /// \param line line symbolizing a relation.
    /// \param rect rectangle of the graphic object.
    inline void LineRectCollision(QPointF* pointBuff, QLineF line, QRectF rect);
    /// \brief Pair of graphic objects, which are in relation.
    std::pair<ClassGraphicsObject*,ClassGraphicsObject*> _pair;
    /// \brief Shared pointer to the relation.
    std::shared_ptr<Relation> _relation;
    /// \brief Index of the relation.
    int _index;
    /// \brief Qt line graphic object.
    QGraphicsLineItem _graphicsLine;
    /// \brief Point of contact between the source of the relation and the object.
    QPointF* _srcCollisionPoint;
    /// \brief Point of contact between the destination of the relation and the object.
    QPointF* _dstCollisionPoint;
    /// \brief Point, where the source cardinality circle is drawn.
    QPointF* _srcCirclePoint;
    /// \brief Point, where the destination cardinality circle is drawn.
    QPointF* _dstCirclePoint;
    /// \brief Destination relation symbol.
    QGraphicsPolygonItem* _dstSymb;
    /// \brief Source cardinality circle.
    QGraphicsEllipseItem* _srcCircle;
    /// \brief Destination cardinality circle.
    QGraphicsEllipseItem* _dstCircle;
    /// \brief Type of relation.
    Relation::Type _type;
    /// \brief Action for deleting the relation.
    QAction* _deleteRelation;
    /// \brief Font of the text in the graphic objects.
    QFont _font;
    /// \brief Graphic item for message text.
    QGraphicsTextItem* _msgItem;

    /// \brief Predefined length of polygon side.
    const qreal POLYGON_SIDE = 15.0;
    /// \brief Predefined circle radius.
    const qreal CIRCLE_RADIUS = 20.0;
    /// \brief Distance between destination circle center and rectangle.
    const qreal CIRCLE_DST_DISTANCE = 65.0;
    /// \brief Source between destination circle center and rectangle.
    const qreal CIRCLE_SRC_DISTANCE = 40.0;
    /// \brief Minimal line length for it to be displayed.
    const qreal LEN_THRESHOLD = 200.0;

signals:
    /// \brief Signal for making a graphic object delete itself.
    void killSelf(RelationGraphicsObject*);
};
