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
    perms->addItems(_perms_list);

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
    perms->addItems(_perms_list);

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
