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
#include <QGraphicsView>

#include "environment.h"
#include "newclassform.h"
#include "classgraphicsobject.h"
#include "relationgraphicsobject.h"
#include "graphicsenum.h"
#include "relationdialog.h"

class ClassDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    ClassDiagramScene(QWidget*);
    ~ClassDiagramScene();

    void drawBackground(QPainter*, const QRectF&) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;

    void PlaceClass(std::shared_ptr<MetaClass>);
    void PlaceRelation(std::shared_ptr<Relation>);
    QWidget* GetParent();
private:

    void InitActions();
    void ResetRelation();

    QAction* _newClass;
    QWidget* _parent;

    Environment* _environment;

    std::map<MetaClass::Name, ClassGraphicsObject*> _graphicsObjectMap;

    std::pair<ClassGraphicsObject*, ClassGraphicsObject*> _relationPair;

public slots:
    void ClearScene();

private slots:
    void CreateClass();
    void DeleteClass(ClassGraphicsObject*);
    void CreateRelation(ClassGraphicsObject*);
    void DeleteRelation(RelationGraphicsObject*);

signals:
    void ClassUpdate();
    void SyncClassPos();
};
