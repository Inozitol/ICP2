#include "lifelinedialog.h"
#include "ui_lifelinedialog.h"

LifelineDialog::LifelineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LifelineDialog),
    _environment(Environment::GetEnvironment())
{
    ui->setupUi(this);
    InitComboBox();
}

LifelineDialog::~LifelineDialog()
{
    delete(ui);
}

std::shared_ptr<SequenceLifeline> LifelineDialog::GetLifeline(){
    auto metaclass = _environment->GetClassDiagram()->GetClass(ui->classComboBox->currentText().toStdString());
    return std::make_shared<SequenceLifeline>(ui->name->text().toStdString(), metaclass);
}

void LifelineDialog::InitComboBox(){
    for(auto metaclass : _environment->GetClassDiagram()->GetClasses()){
        ui->classComboBox->addItem(QString::fromStdString(metaclass.first));
    }
}
