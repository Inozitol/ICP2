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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitMenuBar();
    void InitActions();
    void InitGraphicView();
    void UpdateTimelineColors();

    Ui::MainWindow* ui;
    Environment* _environment;
    QString _currentFile;
    ClassDiagramScene* _classScene;
    SequenceDiagramScene* _sequenceScene;
    QAction* _deleteEvent;
    QAction* _editEvent;
    void DeleteEvent(QListWidgetItem*);
    void EditEvent(QListWidgetItem*);

private slots:
    void EnvironNew();
    void EnvironOpen();
    void EnvironSave();
    void EnvironSaveAs();

    void RefreshClassList();
    void RefreshTimelineList();

    void MoveEventUp();
    void MoveEventDown();

    void SequenceListContextMenu(QPoint);
signals:
    void ClearScenes();
};
