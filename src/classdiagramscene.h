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

///
/// \brief Class representing the scene for viewing the class diagram.
///
class ClassDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param parent pointer to the main window.
    ClassDiagramScene(QWidget* parent);
    /// \brief Class destructor.
    ~ClassDiagramScene();

    /// \brief Redefined method for drawing the background of the class diagram.
    /// \param painter Qt painter.
    /// \param rect scene rectangle.
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    /// \brief Redefined method defining context menu event behaviour.
    /// \param event event for the context menu in the scene.
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    /// \brief Redefined method for double click events on the scene.
    /// \param event event for the double click in the scene.
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    /// \brief Method for placing a meta class into the scene.
    /// \param metaclass shared pointer to the meta class, which is to be placed.
    void PlaceClass(std::shared_ptr<MetaClass> metaclass);
    /// \brief Method for placing a relations into the scene.
    /// \param relation shared pointer to the relation, which is to be placed.
    void PlaceRelation(std::shared_ptr<Relation> relation);
    /// \brief Method for obtaining the parent of the scene.
    /// \return parent of the scene (most likely main window).
    QWidget* GetParent();
private:
    /// \brief Method for initializing context menu actions.
    void InitActions();
    /// \brief Method for resetting relation creation variable.
    void ResetRelation();
    /// \brief Method for renaming a class to maintain consistency accross map keys.
    /// \param from Old map name
    /// \param to New map name
    void RenameClass(MetaClass::Name from, MetaClass::Name to);
    /// \brief Action for creating a new meta class.
    QAction* _newClass;
    /// \brief Parent of the scene.
    QWidget* _parent;
    /// \brief Pointer to a global environment.
    Environment* _environment;
    /// \brief Map, which binds graphic objects to their name.
    std::map<MetaClass::Name, ClassGraphicsObject*> _graphicsObjectMap;
    /// \brief Pair of graphic objects, temporarily holding a relation between them.
    std::pair<ClassGraphicsObject*, ClassGraphicsObject*> _relationPair;

public slots:
    /// \brief Slot for clearing the graphic objects map.
    void ClearScene();

private slots:
    /// \brief Slot for starting the process of class creation.
    void CreateClass();
    /// \brief Slot for starting the process of class deletion.
    /// \param classitem graphic object of the class, which is to be deleted.
    void DeleteClass(ClassGraphicsObject* classitem);
    /// \brief Slot for starting the process of class editing.
    /// \param classitem graphic object of the class, which is to be edited.
    void EditClass(ClassGraphicsObject* classitem);
    /// \brief Slot for initializing and completing the process of relation creation.
    /// \param item one of the meta class graphic objects of the relation.
    void CreateRelation(ClassGraphicsObject* item);
    /// \brief Slot for deleting a relation.
    /// \param item graphic item of the relation.
    void DeleteRelation(RelationGraphicsObject* item);

signals:
    /// \brief Signal for updating the class graphic objects list.
    void ClassUpdate();
    /// \brief Signal for synchronizing positions of graphic objects into backend.
    void SyncClassPos();
    /// \brief Signal that's called when any class get's changed
};
