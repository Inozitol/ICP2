#include "eventdialog.h"
#include "ui_eventdialog.h"
#include "ui_event_activation.h"
#include "ui_event_deactivation.h"
#include "ui_event_message.h"
#include "ui_event_return.h"
#include "ui_event_spacer.h"

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog),
    uiAct(new Ui::EventActivation),
    uiDea(new Ui::EventDeactivation),
    uiMsg(new Ui::EventMessage),
    uiRet(new Ui::EventReturn),
    uiSpa(new Ui::EventSpacer),
    _actWidget(new QWidget()),
    _deaWidget(new QWidget()),
    _msgWidget(new QWidget()),
    _retWidget(new QWidget()),
    _spaWidget(new QWidget()),
    _environment(Environment::GetEnvironment()),
    _event(nullptr)
{
    ui->setupUi(this);
    uiAct->setupUi(_actWidget);
    uiDea->setupUi(_deaWidget);
    uiMsg->setupUi(_msgWidget);
    uiRet->setupUi(_retWidget);
    uiSpa->setupUi(_spaWidget);
    InitConnects();
    InitLayouts();
}

EventDialog::EventDialog(std::shared_ptr<SequenceEvent> event, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::EventDialog),
    uiAct(new Ui::EventActivation),
    uiDea(new Ui::EventDeactivation),
    uiMsg(new Ui::EventMessage),
    uiRet(new Ui::EventReturn),
    uiSpa(new Ui::EventSpacer),
    _actWidget(new QWidget()),
    _deaWidget(new QWidget()),
    _msgWidget(new QWidget()),
    _retWidget(new QWidget()),
    _spaWidget(new QWidget()),
    _environment(Environment::GetEnvironment()),
    _event(event)
{
    ui->setupUi(this);
    uiAct->setupUi(_actWidget);
    uiDea->setupUi(_deaWidget);
    uiMsg->setupUi(_msgWidget);
    uiRet->setupUi(_retWidget);
    uiSpa->setupUi(_spaWidget);
    InitConnects();
    InitLayouts();

}

EventDialog::~EventDialog()
{
    delete(ui);
    delete(uiAct);
    delete(uiDea);
    delete(uiMsg);
    delete(uiRet);
    delete(uiSpa);
}

void EventDialog::InitConnects(){
    connect(ui->radioActivate, 		&QRadioButton::clicked, this, [this](){switchEvent(SequenceEvent::Activation);});
    connect(ui->radioDeactivate, 	&QRadioButton::clicked, this, [this](){switchEvent(SequenceEvent::Deactivation);});
    connect(ui->radioMessage, 		&QRadioButton::clicked, this, [this](){switchEvent(SequenceEvent::Message);});
    connect(ui->radioReturn, 		&QRadioButton::clicked, this, [this](){switchEvent(SequenceEvent::Return);});
    connect(ui->radioNop, 			&QRadioButton::clicked, this, [this](){switchEvent(SequenceEvent::Nop);});

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this](){if(isValid()) emit acceptedSafe();});
    connect(this, &EventDialog::acceptedSafe, this, &QDialog::accept);
}

void EventDialog::InitLayouts(){

    for(auto lifeline : _environment->GetSequenceDiagram()->GetLifelines()){
        uiAct->comboBox->addItem(QString::fromStdString(lifeline.first));
        uiDea->comboBox->addItem(QString::fromStdString(lifeline.first));
        uiMsg->originComboBox->addItem(QString::fromStdString(lifeline.first));
        uiMsg->destinationComboBox->addItem(QString::fromStdString(lifeline.first));
        uiRet->originComboBox->addItem(QString::fromStdString(lifeline.first));
        uiRet->destinationComboBox->addItem(QString::fromStdString(lifeline.first));
    }

    ui->stackedWidget->insertWidget(SequenceEvent::Activation, 		_actWidget);
    ui->stackedWidget->insertWidget(SequenceEvent::Deactivation, 	_deaWidget);
    ui->stackedWidget->insertWidget(SequenceEvent::Message, 		_msgWidget);
    ui->stackedWidget->insertWidget(SequenceEvent::Return, 			_retWidget);
    ui->stackedWidget->insertWidget(SequenceEvent::Nop, 			_spaWidget);

    if(_event){
        _currType = _event->GetType();
        ui->radioActivate->setDisabled(true);
        ui->radioDeactivate->setDisabled(true);
        ui->radioMessage->setDisabled(true);
        ui->radioReturn->setDisabled(true);
        ui->radioNop->setDisabled(true);
        ui->groupRadioBox->setToolTip(tr("Can't change event type while editing"));
    }else{
        _currType = SequenceEvent::Activation;
    }
    ui->stackedWidget->setCurrentIndex(_currType);

    if(_event){
        switch(_currType){
        case SequenceEvent::Activation:
        {
            ui->radioActivate->setChecked(true);
            int index = uiAct->comboBox->findText(QString::fromStdString(std::static_pointer_cast<SequenceActivation>(_event)->GetLifeline()->GetName()));
            uiAct->comboBox->setCurrentIndex(index);
        }
        break;

        case SequenceEvent::Deactivation:
        {
            ui->radioDeactivate->setChecked(true);
            int index = uiAct->comboBox->findText(QString::fromStdString(std::static_pointer_cast<SequenceDeactivation>(_event)->GetLifeline()->GetName()));
            uiDea->comboBox->setCurrentIndex(index);
        }
        break;

        case SequenceEvent::Message:
        {
            ui->radioMessage->setChecked(true);
            auto msgSrc = QString::fromStdString(std::static_pointer_cast<SequenceMessage>(_event)->GetOrigin()->GetName());
            auto msgDst = QString::fromStdString(std::static_pointer_cast<SequenceMessage>(_event)->GetDestination()->GetName());
            auto msgTxt = QString::fromStdString(std::static_pointer_cast<SequenceMessage>(_event)->GetMessage());

            int srcindex = uiMsg->originComboBox->findText(msgSrc);
            int dstindex = uiMsg->destinationComboBox->findText(msgDst);

            uiMsg->originComboBox->setCurrentIndex(srcindex);
            uiMsg->destinationComboBox->setCurrentIndex(dstindex);
            uiMsg->messageLineEdit->setText(msgTxt);
        }
        break;

        case SequenceEvent::Return:
        {
            ui->radioReturn->setChecked(true);
            auto msgSrc = QString::fromStdString(std::static_pointer_cast<SequenceReturn>(_event)->GetOrigin()->GetName());
            auto msgDst = QString::fromStdString(std::static_pointer_cast<SequenceReturn>(_event)->GetDestination()->GetName());
            auto msgTxt = QString::fromStdString(std::static_pointer_cast<SequenceReturn>(_event)->GetMessage());
            auto msgType = QString::fromStdString(std::static_pointer_cast<SequenceReturn>(_event)->GetReturnType());

            int srcindex = uiMsg->originComboBox->findText(msgSrc);
            int dstindex = uiMsg->destinationComboBox->findText(msgDst);

            uiRet->originComboBox->setCurrentIndex(srcindex);
            uiRet->destinationComboBox->setCurrentIndex(dstindex);
            uiRet->valueLineEdit->setText(msgTxt);
            uiRet->returnLineEdit->setText(msgType);
        }
        break;

        case SequenceEvent::Nop:
            ui->radioNop->setChecked(true);
        break;
        }
    }
}

void EventDialog::switchEvent(SequenceEvent::Type type){
    ui->stackedWidget->setCurrentIndex(type);
    _currType = type;
}

bool EventDialog::isValid(){
    switch(_currType){
        case SequenceEvent::Activation:
            if(uiAct->comboBox->currentIndex() == -1){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Lifeline is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else{
                return true;
            }
        break;

        case SequenceEvent::Deactivation:
            if(uiDea->comboBox->currentIndex() == -1){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Lifeline is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else{
                return true;
            }
        break;

        case SequenceEvent::Message:
            if(uiMsg->originComboBox->currentIndex() == -1 || uiMsg->destinationComboBox->currentIndex() == -1){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Lifeline is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else if(uiMsg->messageLineEdit->text().isEmpty()){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Message is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else{
                return true;
            }
        break;

        case SequenceEvent::Return:
            if(uiRet->originComboBox->currentIndex() == -1 || uiRet->destinationComboBox->currentIndex() == -1){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Lifeline is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else if(uiRet->valueLineEdit->text().isEmpty()){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Return value is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else if(uiRet->returnLineEdit->text().isEmpty()){
                QMessageBox msgBox(QMessageBox::Critical,
                                   tr("Error"),
                                   tr("Return type is not set"),
                                   QMessageBox::Ok);
                msgBox.exec();
                return false;
            }else{
                return true;
            }
        break;

        case SequenceEvent::Nop:
            return true;
        break;
    }
}

std::shared_ptr<SequenceEvent> EventDialog::GetEvent(){
    switch(_currType){
        case SequenceEvent::Activation:
        {
            SequenceLifeline::Name name = uiAct->comboBox->currentText().toStdString();
            std::shared_ptr<SequenceLifeline> lifeline = _environment->GetSequenceDiagram()->GetLifeline(name);
            if(_event){
                auto activation = std::static_pointer_cast<SequenceActivation>(_event);
                activation->SetLifeline(lifeline);
                return activation;
            }
            return std::make_shared<SequenceActivation>(lifeline);
        }
        break;

        case SequenceEvent::Deactivation:
        {
            SequenceLifeline::Name name = uiDea->comboBox->currentText().toStdString();
            std::shared_ptr<SequenceLifeline> lifeline = _environment->GetSequenceDiagram()->GetLifeline(name);
            if(_event){
                auto deactivation = std::static_pointer_cast<SequenceDeactivation>(_event);
                deactivation->SetLifeline(lifeline);
                return deactivation;
            }
            return std::make_shared<SequenceDeactivation>(lifeline);
        }
        break;

        case SequenceEvent::Message:
        {
            SequenceLifeline::Name origin_name = uiMsg->originComboBox->currentText().toStdString();
            SequenceLifeline::Name destination_name = uiMsg->destinationComboBox->currentText().toStdString();

            std::string msg = uiMsg->messageLineEdit->text().toStdString();

            std::shared_ptr<SequenceLifeline> origin_lifeline = _environment->GetSequenceDiagram()->GetLifeline(origin_name);
            std::shared_ptr<SequenceLifeline> destination_lifeline = _environment->GetSequenceDiagram()->GetLifeline(destination_name);

            if(_event){
                auto message = std::static_pointer_cast<SequenceMessage>(_event);
                message->SetOrigin(origin_lifeline);
                message->SetDestination(destination_lifeline);
                message->SetMessage(msg);
                return message;
            }

            return std::make_shared<SequenceMessage>(origin_lifeline, destination_lifeline, msg);
        }
        break;

        case SequenceEvent::Return:
        {
            SequenceLifeline::Name origin_name = uiRet->originComboBox->currentText().toStdString();
            SequenceLifeline::Name destination_name = uiRet->destinationComboBox->currentText().toStdString();

            std::string msg = uiRet->valueLineEdit->text().toStdString();
            std::string type = uiRet->returnLineEdit->text().toStdString();

            std::shared_ptr<SequenceLifeline> origin_lifeline = _environment->GetSequenceDiagram()->GetLifeline(origin_name);
            std::shared_ptr<SequenceLifeline> destination_lifeline = _environment->GetSequenceDiagram()->GetLifeline(destination_name);

            if(_event){
                auto retr = std::static_pointer_cast<SequenceReturn>(_event);
                retr->SetOrigin(origin_lifeline);
                retr->SetDestination(destination_lifeline);
                retr->SetMessage(msg);
                retr->SetReturnType(type);
                return retr;
            }

            return std::make_shared<SequenceReturn>(origin_lifeline, destination_lifeline, msg, type);
        }
        break;

        case SequenceEvent::Nop:
            if(_event) return _event;
            return std::make_shared<SequenceSpacer>();
        break;
    }
}
