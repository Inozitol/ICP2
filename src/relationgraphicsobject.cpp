#include "relationgraphicsobject.h"

RelationGraphicsObject::RelationGraphicsObject(std::shared_ptr<Relation> relation, std::pair<ClassGraphicsObject*, ClassGraphicsObject*> pair)
    : _pair(pair),
      _relation(relation),
      _index(relation->GetIndex()),
      _graphicsLine({pair.first->GetItemCenter(), pair.second->GetItemCenter()}, this),
      _type(relation->GetType()),
      _font(FONT)
{
    setZValue(-1);
    _srcCollisionPoint = new QPointF;
    _dstCollisionPoint = new QPointF;
    InitSymbol();
    InitCircles();
    InitActions();
}

int RelationGraphicsObject::GetIndex(){
    return _index;
}

void RelationGraphicsObject::InitSymbol(){

    _dstSymb = new QGraphicsPolygonItem(this);

    QPolygonF polygon;
    switch(_type){
        case Relation::Gener:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);
            _dstSymb->setBrush({Qt::gray, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;

        case Relation::Compo:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(2*POLYGON_SIDE, 0.0)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);

            _dstSymb->setBrush({Qt::gray, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;

        case Relation::Aggre:
            polygon << QPointF(0.0, 0.0)
                    << QPointF(POLYGON_SIDE, -POLYGON_SIDE/2)
                    << QPointF(2*POLYGON_SIDE, 0.0)
                    << QPointF(POLYGON_SIDE, POLYGON_SIDE/2);

            _dstSymb->setBrush({Qt::white, Qt::SolidPattern});
            _dstSymb->setPen({Qt::black});
        break;
    }

    _dstSymb->setPolygon(polygon);

    UpdateSymbol();
}

void RelationGraphicsObject::InitCircles(){
    _dstCircle = new QGraphicsEllipseItem(this);
    _srcCircle = new QGraphicsEllipseItem(this);

    _srcCirclePoint = new QPointF;
    _dstCirclePoint = new QPointF;

    QRectF rect(-CIRCLE_RADIUS, -CIRCLE_RADIUS, 2*CIRCLE_RADIUS, 2*CIRCLE_RADIUS);

    _srcCircle->setRect(rect);
    _dstCircle->setRect(rect);

    _srcCircle->setBrush(Qt::white);
    _dstCircle->setBrush(Qt::white);

    auto fm = QFontMetrics(_font);

    QString srcCrdStr = QString::fromStdString(_relation->GetSrcCardinality());
    QString dstCrdStr = QString::fromStdString(_relation->GetDstCardinality());

#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
    qreal srcwidth = fm.width(srcCrdStr);
    qreal dstwidth = fm.width(srcCrdStr);
#else
    qreal srcwidth = fm.horizontalAdvance(srcCrdStr);
    qreal dstwidth = fm.horizontalAdvance(dstCrdStr);
#endif

    qreal xSrcPos = ((2*CIRCLE_RADIUS - srcwidth)/2)-CIRCLE_RADIUS;
    qreal ySrcPos = (round(fm.height()/2.0))-CIRCLE_RADIUS;

    qreal xDstPos = ((2*CIRCLE_RADIUS - dstwidth)/2)-CIRCLE_RADIUS;
    qreal yDstPos = (round(fm.height()/2.0))-CIRCLE_RADIUS;

    QGraphicsTextItem* srcCrdGraphic = new QGraphicsTextItem(srcCrdStr, _srcCircle);
    QGraphicsTextItem* dstCrdGraphic = new QGraphicsTextItem(dstCrdStr, _dstCircle);
    srcCrdGraphic->setPos(xSrcPos, ySrcPos);
    dstCrdGraphic->setPos(xDstPos, yDstPos);

    UpdateCircles();
    if(_relation->GetSrcCardinality().empty()){
        _srcCircle->setVisible(false);
    }
    if(_relation->GetDstCardinality().empty()){
        _dstCircle->setVisible(false);
    }
}

void RelationGraphicsObject::InitActions(){
    _deleteRelation = new QAction(tr("Delete relation"));
    connect(_deleteRelation, &QAction::triggered, this, [this](){emit killSelf(this);});
}

void RelationGraphicsObject::UpdateSymbol(){
    QRectF srcBndRect = _pair.first->boundingRect();
    QRectF dstBndRect = _pair.second->boundingRect();
    srcBndRect.moveTo(_pair.first->pos());
    dstBndRect.moveTo(_pair.second->pos());

    LineRectCollision(_srcCollisionPoint, _graphicsLine.line(), srcBndRect);
    LineRectCollision(_dstCollisionPoint, _graphicsLine.line(), dstBndRect);

    _dstSymb->setPos(*_dstCollisionPoint);
    _dstSymb->setRotation((-_graphicsLine.line().angle())+180.0);
}

void RelationGraphicsObject::UpdateCircles(){
    if(_graphicsLine.line().length() < LEN_THRESHOLD){
        _srcCircle->setVisible(false);
        _dstCircle->setVisible(false);
        _dstSymb->setVisible(false);
    }else{
        if(!_relation->GetSrcCardinality().empty()){
            _srcCircle->setVisible(true);
        }
        if(!_relation->GetDstCardinality().empty()){
            _dstCircle->setVisible(true);
        }
        _dstSymb->setVisible(true);
    }

    QRectF srcBndRect = _pair.first->boundingRect();
    QRectF dstBndRect = _pair.second->boundingRect();
    srcBndRect.moveTo(_pair.first->pos());
    dstBndRect.moveTo(_pair.second->pos());

    qreal dx = _graphicsLine.line().x2() - _graphicsLine.line().x1();
    qreal dy = _graphicsLine.line().y2() - _graphicsLine.line().y1();

    qreal len = _graphicsLine.line().length();

    qreal ux = dx/len;
    qreal uy = dy/len;

    _srcCirclePoint->setX((*_srcCollisionPoint).x() + ux * CIRCLE_SRC_DISTANCE);
    _srcCirclePoint->setY((*_srcCollisionPoint).y() + uy * CIRCLE_SRC_DISTANCE);

    ux = -ux;
    uy = -uy;

    _dstCirclePoint->setX((*_dstCollisionPoint).x() + ux * CIRCLE_DST_DISTANCE);
    _dstCirclePoint->setY((*_dstCollisionPoint).y() + uy * CIRCLE_DST_DISTANCE);

    _srcCircle->setPos(*_srcCirclePoint);
    _dstCircle->setPos(*_dstCirclePoint);

}

RelationGraphicsObject::~RelationGraphicsObject(){
    delete(_srcCollisionPoint);
    delete(_dstCollisionPoint);
    delete(_srcCirclePoint);
    delete(_dstCirclePoint);
    delete(_dstSymb);
    delete(_srcCircle);
    delete(_dstCircle);
    delete(_deleteRelation);
}

void RelationGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }
}

void RelationGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_deleteRelation);
    menu.exec(event->screenPos());
    event->accept();
}

[[nodiscard]] QRectF RelationGraphicsObject::boundingRect() const{
    return _graphicsLine.boundingRect();
}

std::pair<MetaClass::Name, MetaClass::Name> RelationGraphicsObject::GetRelationParts(){
    return std::make_pair(_pair.first->GetClassName(), _pair.second->GetClassName());
}

void RelationGraphicsObject::updateLine(){
    prepareGeometryChange();
    _graphicsLine.setLine({_pair.first->GetItemCenter(), _pair.second->GetItemCenter()});

    UpdateSymbol();
    UpdateCircles();

    update();
}

/// Taken from http://jeffreythompson.org/collision-detection/line-line.php
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

/// Taken from http://jeffreythompson.org/collision-detection/line-rect.php
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

std::pair<ClassGraphicsObject*, ClassGraphicsObject*> RelationGraphicsObject::GetPair(){
    return _pair;
}
