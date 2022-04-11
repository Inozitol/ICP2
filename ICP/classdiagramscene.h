#pragma once

#define B_CLR "#606060"
#define F_CLR "#C0C0C0"

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPointF>

#include "environment.h"
#include "newclassform.h"
#include "classgraphicsobject.h"

class ClassDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    ClassDiagramScene(QWidget*);
    ~ClassDiagramScene();

    void drawBackground(QPainter*, const QRectF&) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;

private:

    void InitActions();
    void PlaceClass(std::shared_ptr<MetaClass>);

    QAction* _newClass;
    QWidget* _parent;

    enum Dimensions{
        sceneX = -1000,
        sceneY = -1000,
        sceneW = 2000,
        sceneH = 2000
    };

    Environment* _environment;

private slots:
    void NewClass();

signals:
    void ClassChange();
};
