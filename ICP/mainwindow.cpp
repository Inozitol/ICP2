#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Environment* environment = Environment::GetEnvironment();
    std::shared_ptr<MetaClass> metaclass = std::make_shared<MetaClass>("Kekw");
    metaclass->AddAttribute(std::make_shared<MetaClassAttribute>("YoMom", '+', "Person"));
    std::shared_ptr<MetaClassMethod> metamethod = std::make_shared<MetaClassMethod>("Access", '+');
    metamethod->AddParameter("Time");
    metamethod->AddParameter("Place");
    metamethod->ChangeReturnType("Confirmation");
    metaclass->AddMethod(metamethod);
    environment->InsertClass(metaclass);
    environment->ExportEnvironment("./testfile");
}

MainWindow::~MainWindow()
{
    delete ui;
}

