
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _environment = Environment::GetEnvironment();
    InitMenuBar();
}

void MainWindow::InitMenuBar(){
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::FileOpen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FileOpen(){
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open UML file"));
    _environment->ImportEnvironment(fileName.toStdString());
    _currentFile = fileName;
}
