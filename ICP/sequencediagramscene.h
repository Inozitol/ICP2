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
#include "eventdialog.h"

class SequenceDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    SequenceDiagramScene(QWidget*);
    ~SequenceDiagramScene();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;
    void RedrawScene();
private:
    const int V_MARGIN = 25;
    const int H_MARGIN = 100;
    const int FONT_SIZE = 9;

    void InitActions();

    QAction* _newLifeline;
    QAction* _newEvent;
    QWidget* _parent;
    QFont _font;

    Environment* _environment;

    std::map<SequenceLifeline::Name, LifelineGraphicsObject*> _lifelineGraphics;
    std::map<SequenceLifeline::Name, qreal> _actPoints;

public slots:
    void DataChange();

private slots:
    void NewLifeline();
    void DeleteLifeline(LifelineGraphicsObject*);
    void NewEvent();

signals:
    void SceneUpdate();
};
