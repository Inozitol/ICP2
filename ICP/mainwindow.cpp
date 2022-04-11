
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _environment = Environment::GetEnvironment();
    _currentFile = "";
    InitMenuBar();
    InitGraphicView();
}

MainWindow::~MainWindow(){
    delete(ui);
}

void MainWindow::InitMenuBar(){
    connect(ui->actionNew, 		&QAction::triggered, 	this, 	&MainWindow::EnvironNew);
    connect(ui->actionOpen, 	&QAction::triggered, 	this, 	&MainWindow::EnvironOpen);
    connect(ui->actionSave, 	&QAction::triggered, 	this, 	&MainWindow::EnvironSave);
    connect(ui->actionSaveAs, 	&QAction::triggered, 	this, 	&MainWindow::EnvironSaveAs);
}

void MainWindow::InitGraphicView(){
    _classScene = new ClassDiagramScene(this);
    ui->classView->setScene(_classScene);

    connect(_classScene, &ClassDiagramScene::ClassChange, this, &MainWindow::RefreshClassList);
}

void MainWindow::RefreshClassList(){
    ui->classList->clear();
    for(auto metaclass : _environment->GetClass()->GetClasses()){
        ui->classList->addItem(QString::fromStdString(metaclass.first));
    }
}

void MainWindow::EnvironOpen(){
    _currentFile = QFileDialog::getOpenFileName(this, tr("Open UML file"));
    _environment->ImportEnvironment(_currentFile.toStdString());
    RefreshClassList();
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
    _environment->GetClass()->Clear();
    _environment->GetSequence()->Clear();
    _currentFile = "";
    RefreshClassList();
}
