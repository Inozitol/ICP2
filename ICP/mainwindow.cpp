
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
}

void MainWindow::InitGraphicView(){
    _classScene = new ClassDiagramScene(this);
    ui->classView->setScene(_classScene);

    _sequenceScene = new SequenceDiagramScene(this);
    ui->sequenceView->setScene(_sequenceScene);

    connect(_classScene, &ClassDiagramScene::ClassChange, this, &MainWindow::RefreshClassList);
}

void MainWindow::RefreshClassList(){
    ui->classList->clear();
    for(auto metaclass : _environment->GetClassDiagram()->GetClasses()){
        ui->classList->addItem(QString::fromStdString(metaclass.first));
    }
}

void MainWindow::EnvironOpen(){
    _currentFile = QFileDialog::getOpenFileName(this, tr("Open UML file"));
    _environment->ImportEnvironment(_currentFile.toStdString());
    RefreshClassList();
    for(auto [name,metaclass] : _environment->GetClassDiagram()->GetClasses()){
        _classScene->PlaceClass(metaclass);

    }
    for(auto [index, relation] : _environment->GetClassDiagram()->GetRelations()){
        _classScene->PlaceRelation();
    }
    _sequenceScene->RedrawScene();
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
