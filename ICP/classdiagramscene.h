#pragma once

#define B_CLR "#606060"
#define F_CLR "#C0C0C0"

#include "environment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPointF>

#include "newclassform.h"

class ClassDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    ClassDiagramScene(QWidget*);
    ~ClassDiagramScene();

    void drawBackground(QPainter*, const QRectF&) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;

private:

    void InitActions();

    QAction* _newClass;
    QWidget* _parent;

    enum Dimensions{
        sceneX = -1000,
        sceneY = -1000,
        sceneW = 2000,
        sceneH = 2000
    };

    Environment* _environ;

private slots:
    void NewClass();

signals:
    void ClassChange();
};
