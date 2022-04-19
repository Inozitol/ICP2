#pragma once

#define B_CLR "#FFF"
#define F_CLR "#000"
#define FONT "Arial"

#include <map>

#include <QGraphicsScene>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QPainter>

#include "environment.h"
#include "lifelinedialog.h"
#include "lifelinegraphicsobject.h"

class SequenceDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    SequenceDiagramScene(QWidget*);
    ~SequenceDiagramScene();

    //void drawBackground(QPainter*, const QRectF&) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;
    void RedrawScene();
private:
    const int V_MARGIN = 10;
    const int H_MARGIN = 100;
    const int FONT_SIZE = 9;

    void InitActions();

    QAction* _newLifeline;
    QWidget* _parent;
    QFont _font;

    Environment* _environment;

    std::map<SequenceLifeline::Name, LifelineGraphicsObject*> _lifelineGraphics;
    std::map<SequenceLifeline::Name, qreal> _actPoints;

private slots:
    void NewLifeline();
};
