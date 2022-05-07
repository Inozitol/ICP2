#include "relationdialog.h"
#include "ui_relationdialog.h"

RelationDialog::RelationDialog(std::pair<ClassGraphicsObject*, ClassGraphicsObject*> pair, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationDialog),
    _pair(pair)
{
    ui->setupUi(this);
    InitNames();
    InitCombo();
}

void RelationDialog::InitNames(){
    auto srcName = QString::fromStdString(_pair.first->GetClassName());
    auto dstName = QString::fromStdString(_pair.second->GetClassName());

    ui->srcLine->setText(srcName);
    ui->dstLine->setText(dstName);
}

void RelationDialog::InitCombo(){
    for(auto [index, str]: _comboText){
        ui->typeComboBox->insertItem(index, str);
    }
    ui->typeComboBox->setCurrentIndex(Relation::Assoc);
}

std::shared_ptr<Relation> RelationDialog::GetRelation(){
    std::shared_ptr<MetaClass> srcClass = _pair.first->GetClass();
    std::shared_ptr<MetaClass> dstClass = _pair.second->GetClass();

    std::string srcCrd = antiwhite(ui->srcCrd->text().toStdString());
    std::string dstCrd = antiwhite(ui->dstCrd->text().toStdString());

    switch(ui->typeComboBox->currentIndex()){
        case Relation::Assoc:
        {
            _relation = std::make_shared<Association>(srcClass, dstClass);
        }
        break;

        case Relation::Aggre:
        {
            _relation = std::make_shared<Aggregation>(srcClass, dstClass);
        }
        break;

        case Relation::Compo:
        {
            _relation = std::make_shared<Composition>(srcClass, dstClass);
        }
        break;

        case Relation::Gener:
        {
            _relation = std::make_shared<Generalization>(srcClass, dstClass);
        }
        break;
    }
    _relation->SetSrcCardinality(srcCrd);
    _relation->SetDstCardinality(dstCrd);

    return _relation;
}

RelationDialog::~RelationDialog()
{
    delete(ui);
}
