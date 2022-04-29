
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon.png"));
    setWindowTitle("Diagramy alespoň za 50 bodů");
    int largeWidth = QGuiApplication::primaryScreen()->virtualSize().width();
    ui->classSplitter->setSizes(QList<int>{largeWidth/7,6*(largeWidth/7)});
    ui->sequenceSplitter->setSizes(QList<int>{largeWidth/7,6*(largeWidth/7)});
    setWindowState(Qt::WindowMaximized);
    _environment = Environment::GetEnvironment();
    _currentFile = "";
    InitGraphicView();
    InitMenuBar();
}

MainWindow::~MainWindow(){
    delete(ui);
}

void MainWindow::InitMenuBar(){
    connect(ui->actionNew, 		&QAction::triggered, 	this, 	&MainWindow::EnvironNew);
    connect(ui->actionOpen, 	&QAction::triggered, 	this, 	&MainWindow::EnvironOpen);
    connect(ui->actionSave, 	&QAction::triggered, 	this, 	&MainWindow::EnvironSave);
    connect(ui->actionSaveAs, 	&QAction::triggered, 	this, 	&MainWindow::EnvironSaveAs);

    connect(ui->actionNew, 		&QAction::triggered, 	_classScene, 		&QGraphicsScene::clear);
    connect(ui->actionNew, 		&QAction::triggered,	_sequenceScene, 	&QGraphicsScene::clear);

    connect(ui->actionOpen, 	&QAction::triggered, 	_sequenceScene,		&SequenceDiagramScene::DataChange);
}

void MainWindow::InitGraphicView(){
    _classScene = new ClassDiagramScene(this);
    ui->classView->setScene(_classScene);

    _sequenceScene = new SequenceDiagramScene(this);
    ui->sequenceView->setScene(_sequenceScene);

    connect(_classScene, 	&ClassDiagramScene::ClassUpdate, 		this, 	&MainWindow::RefreshClassList);
    connect(_sequenceScene, &SequenceDiagramScene::SceneUpdate, 	this,	&MainWindow::RefreshTimelineList);

    connect(this, &MainWindow::ClearScenes, _classScene, 	&ClassDiagramScene::clear);
    connect(this, &MainWindow::ClearScenes, _classScene, 	&ClassDiagramScene::ClearScene);
    connect(this, &MainWindow::ClearScenes, _sequenceScene, &SequenceDiagramScene::clear);

    connect(ui->buttonDown, &QPushButton::pressed, this, &MainWindow::MoveEventDown);
    connect(ui->buttonUp, &QPushButton::pressed, this, &MainWindow::MoveEventUp);
}

void MainWindow::RefreshClassList(){
    ui->classList->clear();
    for(auto metaclass : _environment->GetClassDiagram()->GetClasses()){
        ui->classList->addItem(QString::fromStdString(metaclass.first));
    }
}

void MainWindow::RefreshTimelineList(){
    ui->sequenceList->clear();

    for(std::size_t i = 0, end = _environment->GetSequenceDiagram()->GetTimeline().size(); i != end; ++i){
        auto event = _environment->GetSequenceDiagram()->GetEventIndex(i);

        switch(event->GetType()){
        case SequenceEvent::Activation:
        {
            auto activation = std::static_pointer_cast<SequenceActivation>(event);
            QString str("Activate ");
            str.append(QString::fromStdString(activation->GetLifeline()->GetName()));

            ui->sequenceList->addItem(str);
        }
        break;

        case SequenceEvent::Deactivation:
        {
            auto deactivation = std::static_pointer_cast<SequenceDeactivation>(event);
            QString str("Deactivate ");
            str.append(QString::fromStdString(deactivation->GetLifeline()->GetName()));

            ui->sequenceList->addItem(str);
        }
        break;

        case SequenceEvent::Message:
        {
            auto message = std::static_pointer_cast<SequenceMessage>(event);
            QString str(QString::fromStdString(message->GetOrigin()->GetName()));
            str.append(" -> ");
            str.append(QString::fromStdString(message->GetDestination()->GetName()));
            str.append(" : ");
            str.append(QString::fromStdString(message->GetMessage()));

            ui->sequenceList->addItem(str);
        }
        break;

        case SequenceEvent::Nop:
        {
            QString str("Spacer");

            ui->sequenceList->addItem(str);
        }
        break;

        }
    }
}

void MainWindow::EnvironOpen(){
    emit ClearScenes();

    _currentFile = QFileDialog::getOpenFileName(this, tr("Open UML file"));
    _environment->ImportEnvironment(_currentFile.toStdString());
    RefreshClassList();
    for(auto [name,metaclass] : _environment->GetClassDiagram()->GetClasses()){
        _classScene->PlaceClass(metaclass);
    }
    for(auto [index, relation] : _environment->GetClassDiagram()->GetRelations()){
        _classScene->PlaceRelation(relation);
    }
    _sequenceScene->RedrawScene();
    _environment->CheckSequenceEvents();
}

void MainWindow::EnvironSave(){
    if(_currentFile == ""){
        _currentFile = QFileDialog::getSaveFileName(this, tr("Save UML file"));
    }
    _environment->ExportEnvironment(_currentFile.toStdString());
}

void MainWindow::EnvironSaveAs(){
    _currentFile = QFileDialog::getSaveFileName(this, tr("Save UML file"));
    _environment->ExportEnvironment(_currentFile.toStdString());
}

void MainWindow::EnvironNew(){
    _environment->GetClassDiagram()->Clear();
    _environment->GetSequenceDiagram()->Clear();
    _currentFile = "";
    RefreshClassList();
}

void MainWindow::MoveEventUp(){
    QListWidgetItem* item;
    int currRow = ui->sequenceList->currentRow();
    if(currRow > 0){
        item = ui->sequenceList->takeItem(currRow);
        ui->sequenceList->insertItem(currRow-1, item);
        ui->sequenceList->setCurrentRow(currRow-1);

        _environment->GetSequenceDiagram()->EventMoveUp(currRow);

        _sequenceScene->RedrawScene();
    }
}

void MainWindow::MoveEventDown(){
    QListWidgetItem* item;
    int currRow = ui->sequenceList->currentRow();
    int itemCount = ui->sequenceList->count();
    if(currRow < itemCount-1){
        item = ui->sequenceList->takeItem(currRow);
        ui->sequenceList->insertItem(currRow+1, item);
        ui->sequenceList->setCurrentRow(currRow+1);

        _environment->GetSequenceDiagram()->EventMoveDown(currRow);

        _sequenceScene->RedrawScene();
    }
}
