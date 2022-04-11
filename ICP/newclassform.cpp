#include "newclassform.h"
#include "ui_newclassform.h"

ClassEditDialog::ClassEditDialog(QWidget* parent)
    :QDialog(parent)
    , ui(new Ui::NewClassForm)
{
    ui->setupUi(this);
    InitButtons();
}

ClassEditDialog::~ClassEditDialog(){
    delete(ui);
}

std::shared_ptr<MetaClass> ClassEditDialog::GetClassPtr(){
    _class = std::make_shared<MetaClass>(ui->className->text().toStdString());
    QComboBox* q_perm;
    QTableWidgetItem* q_dtype;
    QTableWidgetItem* q_name;
    QTableWidgetItem* q_params;

    MetaClassObject::Permission perm;
    MetaClassObject::DataType dtype;
    MetaClass::Name name;

    QModelIndexList sel_indexes = ui->attrTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        q_perm =  static_cast<QComboBox*>(ui->attrTable->cellWidget(index.row(), A_PERM));
        q_dtype = ui->attrTable->item(index.row(), A_DATA_TYPE);
        q_name =  ui->attrTable->item(index.row(), A_NAME);

        perm = 	q_perm->currentData().toInt();

        if(q_dtype == nullptr){
            dtype = "";
        }else{
            dtype = q_dtype->text().toStdString();
        }

        if(q_name == nullptr){
            name = "";
        }else{
            name = 	q_name->text().toStdString();
        }

        qDebug() << "Attr: " << name.data() << " " << dtype.data();

        _class->AddAttribute(std::make_shared<MetaClassAttribute>(name, perm, dtype));
    }

    sel_indexes = ui->methTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        q_perm =  	static_cast<QComboBox*>(ui->methTable->cellWidget(index.row(), M_PERM));
        q_dtype = 	ui->attrTable->item(index.row(), M_RETURN_TYPE);
        q_name =  	ui->attrTable->item(index.row(), M_NAME);
        q_params = 	ui->methTable->item(index.row(), M_PARAMS);

        perm = 	q_perm->currentData().toInt();
        if(q_dtype == nullptr){
            dtype = "";
        }else{
            dtype = q_dtype->text().toStdString();
        }

        if(q_name == nullptr){
            name = "";
        }else{
            name = 	q_name->text().toStdString();
        }

        auto method = std::make_shared<MetaClassMethod>(name, perm, dtype);

        std::stringstream ss(q_params->text().toStdString());
        MetaClassObject::DataType param;
        while(std::getline(ss, param, ',')){
            method->AddParameter(param);
        }
    }

    return _class;
}

void ClassEditDialog::InitButtons(){
    connect(ui->attrButtAdd, 	&QToolButton::clicked, 	this, 	&ClassEditDialog::AddAttrRow);
    connect(ui->attrButtRemove, &QToolButton::clicked, 	this, 	&ClassEditDialog::RemoveAttrRow);
    connect(ui->methButtAdd, 	&QToolButton::clicked, 	this, 	&ClassEditDialog::AddMethRow);
    connect(ui->methButtRemove, &QToolButton::clicked, 	this, 	&ClassEditDialog::RemoveMethRow);

    connect(this, &ClassEditDialog::SigRemoveAttrRow, ui->attrTable, &QTableWidget::removeRow);
    connect(this, &ClassEditDialog::SigRemoveMethRow, ui->methTable, &QTableWidget::removeRow);
}

void ClassEditDialog::AddAttrRow(){

    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int rowCount = ui->attrTable->rowCount();
    ui->attrTable->setRowCount(rowCount+1);

    ui->attrTable->setCellWidget(rowCount, 0, perms);
}

void ClassEditDialog::RemoveAttrRow(){
    QModelIndexList sel_indexes = ui->attrTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        int sel_row = index.row();
        emit SigRemoveAttrRow(sel_row);
    }
}

void ClassEditDialog::AddMethRow(){

    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	'+');
    perms->addItem(tr("Private"), 	'-');
    perms->addItem(tr("Protected"), '#');
    perms->addItem(tr("Package"), 	'~');

    int rowCount = ui->methTable->rowCount();
    ui->methTable->setRowCount(rowCount+1);

    ui->methTable->setCellWidget(rowCount, 0, perms);
}

void ClassEditDialog::RemoveMethRow(){
    QModelIndexList sel_indexes = ui->methTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        int sel_row = index.row();
        emit SigRemoveMethRow(sel_row);
    }
}






