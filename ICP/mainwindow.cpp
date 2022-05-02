
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon.png"));
    setWindowTitle(tr("Diagramy alespoň za 50 bodů"));

    int largeWidth = QGuiApplication::primaryScreen()->virtualSize().width();
    ui->classSplitter->setSizes(QList<int>{largeWidth/7,6*(largeWidth/7)});
    ui->sequenceSplitter->setSizes(QList<int>{largeWidth/7,6*(largeWidth/7)});
    setWindowState(Qt::WindowMaximized);
    _environment = Environment::GetEnvironment();
    _currentFile = "";
    InitActions();
    InitGraphicView();
    InitMenuBar();
    UpdateTimelineColors();
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

void MainWindow::InitActions(){
    connect(ui->sequenceList, &QListWidget::customContextMenuRequested, this, &MainWindow::SequenceListContextMenu);

    _deleteEvent = new QAction(tr("Delete Event"));
    connect(_deleteEvent, &QAction::triggered, [this](){
        auto item = ui->sequenceList->currentItem();
        if(item){
            DeleteEvent(item);
        }
    });
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
        QListWidgetItem* item = new QListWidgetItem();
        QVariant data;
        data.setValue(event);
        item->setData(Qt::UserRole, data);

        switch(event->GetType()){
        case SequenceEvent::Activation:
        {
            auto activation = std::static_pointer_cast<SequenceActivation>(event);
            QString str("Activate ");
            str.append(QString::fromStdString(activation->GetLifeline()->GetName()));

            item->setText(str);
            ui->sequenceList->addItem(item);
        }
        break;

        case SequenceEvent::Deactivation:
        {
            auto deactivation = std::static_pointer_cast<SequenceDeactivation>(event);
            QString str("Deactivate ");
            str.append(QString::fromStdString(deactivation->GetLifeline()->GetName()));

            item->setText(str);
            ui->sequenceList->addItem(item);
        }
        break;

        case SequenceEvent::Return:
        case SequenceEvent::Message:
        {
            auto message = std::static_pointer_cast<SequenceMessage>(event);

            QString str(QString::fromStdString(message->GetOrigin()->GetName()));
            str.append(" -> ");
            str.append(QString::fromStdString(message->GetDestination()->GetName()));
            str.append(" : ");
            str.append(QString::fromStdString(message->GetMessage()));

            item->setText(str);
            ui->sequenceList->addItem(item);
        }
        break;

        case SequenceEvent::Nop:
        {
            QString str("Spacer");

            item->setText(str);
            ui->sequenceList->addItem(item);
        }
        break;

        }
    }
}

void MainWindow::EnvironOpen(){

    _currentFile = QFileDialog::getOpenFileName(this, tr("Open UML file"));
    if(_currentFile.isEmpty()){
        return;
    }

    emit ClearScenes();
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
        UpdateTimelineColors();

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
    if(currRow < itemCount-1 && currRow != -1){
        UpdateTimelineColors();

        item = ui->sequenceList->takeItem(currRow);
        ui->sequenceList->insertItem(currRow+1, item);
        ui->sequenceList->setCurrentRow(currRow+1);

        _environment->GetSequenceDiagram()->EventMoveDown(currRow);

        _sequenceScene->RedrawScene();
    }
}

void MainWindow::UpdateTimelineColors(){
    _environment->CheckSequenceEvents();

    QListWidgetItem* item;
    std::shared_ptr<SequenceEvent> event;
    for(int i=0; i < ui->sequenceList->count(); ++i){
        item = ui->sequenceList->item(i);
        event = qvariant_cast<std::shared_ptr<SequenceEvent>>(item->data(Qt::UserRole));
        if(event->GetStatus()){
            item->setBackground(QBrush(Qt::white));
        }else{
            item->setBackground(QBrush(Qt::darkRed));
        }
    }
}

void MainWindow::SequenceListContextMenu(QPoint point){
    auto item = ui->sequenceList->itemAt(point);
    if(item){
        QMenu menu;
        menu.addAction(_deleteEvent);
        menu.exec(ui->sequenceList->mapToGlobal(point));
    }
}

void MainWindow::DeleteEvent(QListWidgetItem* eventItem){
    auto row = ui->sequenceList->row(eventItem);
    _environment->GetSequenceDiagram()->RemoveEvent(row);
    delete(eventItem);
    _sequenceScene->RedrawScene();
}
