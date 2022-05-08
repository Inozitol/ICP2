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
#include "graphicsenum.h"

///
/// \brief Class representing the scene for viewing the sequence diagram.
///
class SequenceDiagramScene : public QGraphicsScene{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param parent pointer to the main window.
    SequenceDiagramScene(QWidget* parent);
    /// \brief Class destructor.
    ~SequenceDiagramScene();
    /// \brief Redefined method defining context menu event behaviour.
    /// \param event event for the context menu in the scene.
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    /// \brief Method for redrawing the sequence diagram after each change.
    void RedrawScene();

private:
    /// \brief Class graphic object vertical margin.
    const int V_MARGIN = 25;
    /// \brief Class graphic object horizontal margin.
    const int H_MARGIN = 100;
    /// \brief Size of font.
    const int FONT_SIZE = 9;
    /// \brief Method for initializing actions within the sequence diagram.
    void InitActions();
    /// \brief Method for renaming lifeline correctly
    /// \param from Old name
    /// \param to New name
    void RenameLifeline(SequenceLifeline::Name from, SequenceLifeline::Name to);
    /// \brief Action for creating a new lifeline.
    QAction* _newLifeline;
    /// \brief Action for creating a new event.
    QAction* _newEvent;
    /// \brief Reference to the parent Qt widget.
    QWidget* _parent;
    /// \brief Font of the text in the graphic objects.
    QFont _font;
    /// \brief Singleton environment variable.
    Environment* _environment;
    /// \brief Map, which binds lifeline graphic objects to their name.
    std::map<SequenceLifeline::Name, LifelineGraphicsObject*> _lifelineGraphics;
    /// \brief Map, which binds lifeline x coordinates to their name.
    std::map<SequenceLifeline::Name, qreal> _actPoints;

private slots:
    /// \brief Slot for creating a new lifeline.
    void NewLifeline();
    /// \brief Slot for deleting a lifeline.
    void DeleteLifeline(LifelineGraphicsObject*);
    /// \brief Slot for editing a lifeline.
    void EditLifeline(LifelineGraphicsObject*);
    /// \brief Slot for creating a new event
    void NewEvent();

signals:
    /// \brief Signal for signaling a change in the sequence diagram.
    void SceneUpdate();
};
