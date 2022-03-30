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

    std::shared_ptr<MetaClass> metaclass2 = std::make_shared<MetaClass>("Kekw");
    metaclass2->AddAttribute(std::make_shared<MetaClassAttribute>("AlsoYoMom", '+', "Person"));
    std::shared_ptr<MetaClassMethod> metamethod2 = std::make_shared<MetaClassMethod>("Access", '+');
    metamethod2->AddParameter("Time");
    metamethod2->AddParameter("Place");
    metamethod2->ChangeReturnType("Confirmation");
    metaclass2->AddMethod(metamethod);
    environment->InsertClass(metaclass2);

    std::shared_ptr<SequenceDiagram> sequence = std::make_shared<SequenceDiagram>();
    sequence->InsertLifeline("Alice", metaclass);
    sequence->InsertLifeline("Amanda", metaclass2);
    sequence->EventPush(std::make_shared<SequenceActivation>(sequence->GetLifelines().front()));
    sequence->EventPush(std::make_shared<SequenceMessage>(sequence->GetLifelines().front(), sequence->GetLifelines().back(), "Access(now,somewhere)"));
    environment->InsertSequence(sequence);

    //environment->ImportEnvironment("./testfile");
    environment->ExportEnvironment("./outputTest");
}

MainWindow::~MainWindow()
{
    delete ui;
}

