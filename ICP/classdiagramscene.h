#pragma once

#define B_CLR "#FFF"
#define F_CLR "#000"

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPointF>
#include <QGuiApplication>
#include <QScreen>

#include "environment.h"
#include "newclassform.h"
#include "classgraphicsobject.h"
#include "relationgraphicsobject.h"

class ClassDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    ClassDiagramScene(QWidget*);
    ~ClassDiagramScene();

    void drawBackground(QPainter*, const QRectF&) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;

    void PlaceClass(std::shared_ptr<MetaClass>);
    void PlaceRelation(std::shared_ptr<Relation>);

private:

    void InitActions();

    QAction* _newClass;
    QWidget* _parent;

    Environment* _environment;

    std::map<MetaClass::Name, ClassGraphicsObject*> _graphicsObjectMap;

public slots:
    void ClearScene();

private slots:
    void NewClass();
    void DeleteClass(ClassGraphicsObject*);

signals:
    void ClassChange();
};
