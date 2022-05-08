// Autor: xhorac19, xmurga01

#pragma once

#include <memory>

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QListWidgetItem>

#include "environment.h"
#include "classdiagramscene.h"
#include "sequencediagramscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

///
/// \brief Qt class representing the main window.
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// \brief Class constructor.
    /// \param parent pointer to the parent widget of the main window.
    MainWindow(QWidget *parent = nullptr);
    /// \brief Class destructor.
    ~MainWindow();

private:
    /// \brief Method for initializing the options in the menu bar.
    void InitMenuBar();
    /// \brief Method for initializing the actions within the main window.
    void InitActions();
    /// \brief Method for initializing the scenes.
    void InitGraphicView();
    /// \brief Method for highlighting invalid events in the sequence diagram.
    void UpdateTimelineColors();

    /// \brief UI of the main window.
    Ui::MainWindow* ui;
    /// \brief Singleton environment variable.
    Environment* _environment;
    /// \brief Reference to the currently opened file.
    QString _currentFile;
    /// \brief Pointer to the class diagram scene.
    ClassDiagramScene* _classScene;
    /// \brief Pointer to the sequence diagram scene.
    SequenceDiagramScene* _sequenceScene;
    /// \brief Action for deleting an event in the sequence diagram.
    QAction* _deleteEvent;
    /// \brief Action for editing an event in the sequence diagram.
    QAction* _editEvent;

    /// \brief Method for deleting an event in the sequence diagram.
    void DeleteEvent(QListWidgetItem* eventItem);
    /// \brief Method for editing an event in the sequence diagram.
    void EditEvent(QListWidgetItem* eventItem);

private slots:
    /// \brief Slot for creating a new environment.
    void EnvironNew();
    /// \brief Slot for opening an environment.
    void EnvironOpen();
    /// \brief Slot for saving the environment into the currently opened file.
    void EnvironSave();
    /// \brief Slot for saving the environment into the specificed file.
    void EnvironSaveAs();

    /// \brief Slot for refreshing the class list.
    void RefreshClassList();
    /// \brief Slot for refreshing the timeline list.
    void RefreshTimelineList();

    /// \brief Slot for moving an event earlier into the timeline.
    void MoveEventUp();
    /// \brief Slot for moving an event later into the timeline.
    void MoveEventDown();

    /// \brief Slot for displaying a context menu when rightclicking an event.
    void SequenceListContextMenu(QPoint point);
signals:
    /// \brief Signal for clearing all data in the class/sequence diagram scenes.
    void ClearScenes();
};
