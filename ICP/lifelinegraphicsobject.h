#pragma once

#define WHOLEBOX_CLR "#BFBFBF"
#define TITLEBOX_CLR "#DFC6AE"
#define FONT "Arial"

#define LIFELINE_DEF 420

#include <QGraphicsObject>
#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>

#include "SequenceDiagram/sequencelifeline.h"

class LifelineGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    LifelineGraphicsObject(std::shared_ptr<SequenceLifeline>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    // TODO context menu
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    qreal middle();
    void InitActions();
    SequenceLifeline::Name GetName();

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
    QAction* _deleteLifeline;

    QString _lifelineName;
    QString _className;
    int _width;
    int _height;

private slots:

    void killSelfSlot();

signals:
    void killSelf(LifelineGraphicsObject*);

};
