#include "lifelinedialog.h"
#include "ui_lifelinedialog.h"

LifelineDialog::LifelineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LifelineDialog),
    _environment(Environment::GetEnvironment()),
    _lifeline(nullptr)
{
    ui->setupUi(this);
    InitComboBox();
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LifelineDialog::acceptCondition);
    connect(this, &LifelineDialog::acceptedSafe, this, &QDialog::accept);
}

LifelineDialog::LifelineDialog(std::shared_ptr<SequenceLifeline> lifeline, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LifelineDialog),
    _environment(Environment::GetEnvironment()),
    _lifeline(lifeline)
{
    ui->setupUi(this);
    InitComboBox();
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LifelineDialog::acceptCondition);
    connect(this, &LifelineDialog::acceptedSafe, this, &QDialog::accept);
    ui->name->setText(QString::fromStdString(_lifeline->GetName()));
}

LifelineDialog::~LifelineDialog()
{
    delete(ui);
}

std::shared_ptr<SequenceLifeline> LifelineDialog::GetLifeline(){
    auto metaclass = _environment->GetClassDiagram()->GetClass(ui->classComboBox->currentText().toStdString());
    if(_lifeline){
        _lifeline->ChangeName(ui->name->text().toStdString());
        _lifeline->ChangeClass(metaclass);
        return _lifeline;
    }
    return std::make_shared<SequenceLifeline>(antiwhite(ui->name->text().toStdString()), metaclass);
}

void LifelineDialog::InitComboBox(){
    for(auto metaclass : _environment->GetClassDiagram()->GetClasses()){
        ui->classComboBox->addItem(QString::fromStdString(metaclass.first));
    }
    if(_lifeline){
        int index = ui->classComboBox->findText(QString::fromStdString(_lifeline->GetClass()->GetName()));
        ui->classComboBox->setCurrentIndex(index);
    }
}

void LifelineDialog::acceptCondition(){
    if(ui->classComboBox->currentIndex() == -1){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(tr("Class type is not set"));
        msgBox.setInformativeText(tr("Please select class type"));
        msgBox.exec();
    }else if(ui->name->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(tr("Lifeline name is not set"));
        msgBox.setInformativeText(tr("Please enter lifeline name"));
        msgBox.exec();
    }else{
        emit acceptedSafe();
    }

}
