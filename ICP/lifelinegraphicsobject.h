#pragma once

#define WHOLEBOX_CLR "#BFBFBF"
#define TITLEBOX_CLR "#DFC6AE"
#define FONT "Arial"

#include <QGraphicsObject>
#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

#include "SequenceDiagram/sequencelifeline.h"

class LifelineGraphicsObject : public QGraphicsObject
{
public:
    LifelineGraphicsObject(std::shared_ptr<SequenceLifeline>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    // TODO context menu
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    qreal middle();

    static qreal height();

private:
    static const int DEF_WIDTH = 75;
    static const int V_MARGIN = 2;
    static const int H_MARGIN = 2;

    void InitStrings();
    void CalcHeight();
    inline bool willOverflow(QString);

    std::shared_ptr<SequenceLifeline> _lifeline;

    QFont _font;

    QString _lifelineName;
    QString _className;
    int _width;
    int _height;
};
