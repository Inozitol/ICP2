#include "newclassform.h"
#include "ui_newclassform.h"

ClassEditDialog::ClassEditDialog(QWidget* parent)
    :QDialog(parent),
     ui(new Ui::NewClassForm),
     _environment(Environment::GetEnvironment()),
     _class(nullptr)
{
    ui->setupUi(this);
    InitButtons();
}

ClassEditDialog::ClassEditDialog(std::shared_ptr<MetaClass> metaclass, QWidget* parent)
    :QDialog(parent),
    ui(new Ui::NewClassForm),
     _environment(Environment::GetEnvironment()),
    _class(metaclass)
{
    ui->setupUi(this);
    InitButtons();
    InitContent();
}

void ClassEditDialog::InitContent(){
    ui->className->setText(QString::fromStdString(_class->GetName()));
    for(auto attr : _class->GetAttributes()){
        _AddAttrRow(attr.second);
    }
    for(auto meth : _class->GetMethods()){
        _AddMethRow(meth.second);
    }
}

ClassEditDialog::~ClassEditDialog(){
    delete(ui);
}

std::shared_ptr<MetaClass> ClassEditDialog::GetClassPtr(){
    if(_class){
        MetaClass::Name oldName = _class->GetName();
        MetaClass::Name newName = antiwhite(ui->className->text().toStdString());
        _class->Clear();
        _class->SetName(newName);
        _environment->GetClassDiagram()->RenameClass(oldName, newName);
    }else{
        _class = std::make_shared<MetaClass>(antiwhite(ui->className->text().toStdString()));
    }

    QComboBox* q_perm;
    QTableWidgetItem* q_dtype;
    QTableWidgetItem* q_name;
    QTableWidgetItem* q_params;

    MetaClassObject::Permission perm;
    MetaClassObject::DataType dtype;
    MetaClass::Name name;

    int rowCount = ui->attrTable->rowCount();
    for(int row=0; row < rowCount; row++){
        q_perm =  static_cast<QComboBox*>(ui->attrTable->cellWidget(row, A_PERM));
        q_dtype = ui->attrTable->item(row, A_DATA_TYPE);
        q_name =  ui->attrTable->item(row, A_NAME);

        perm = 	q_perm->currentData().toInt();

        if(q_dtype == nullptr){
            dtype = "";
        }else{
            dtype = antiwhite(q_dtype->text().toStdString());
        }

        if(q_name == nullptr){
            name = "";
        }else{
            name = 	antiwhite(q_name->text().toStdString());
        }

        _class->AddAttribute(std::make_shared<MetaClassAttribute>(name, perm, dtype));
    }

    rowCount = ui->methTable->rowCount();
    for(int row=0; row < rowCount; row++){
        q_perm =  	static_cast<QComboBox*>(ui->methTable->cellWidget(row, M_PERM));
        q_dtype = 	ui->methTable->item(row, M_RETURN_TYPE);
        q_name =  	ui->methTable->item(row, M_NAME);
        q_params = 	ui->methTable->item(row, M_PARAMS);

        perm = 	q_perm->currentData().toInt();
        if(q_dtype == nullptr){
            dtype = "";
        }else{
            dtype = antiwhite(q_dtype->text().toStdString());
        }

        if(q_name == nullptr){
            name = "";
        }else{
            name = 	antiwhite(q_name->text().toStdString());
        }

        auto method = std::make_shared<MetaClassMethod>(name, perm, dtype);

        if(q_params != nullptr){
            std::stringstream ss(antiwhite(q_params->text().toStdString()));
            MetaClassObject::DataType param;
            while(std::getline(ss, param, ',')){
                method->AddParameter(param);
            }
        }

        _class->AddMethod(method);
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

void ClassEditDialog::_AddAttrRow(std::shared_ptr<MetaClassAttribute> attr){

    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int index = perms->findData(QChar(attr->GetPermission()));
    perms->setCurrentIndex(index);

    int rowCount = ui->attrTable->rowCount();
    ui->attrTable->setRowCount(rowCount+1);

    ui->attrTable->setCellWidget(rowCount, A_PERM, perms);
    ui->attrTable->setItem(rowCount, A_DATA_TYPE, new QTableWidgetItem(QString::fromStdString(attr->GetDataType())));
    ui->attrTable->setItem(rowCount, A_NAME, new QTableWidgetItem(QString::fromStdString(attr->GetName())));
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
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int rowCount = ui->methTable->rowCount();
    ui->methTable->setRowCount(rowCount+1);

    ui->methTable->setCellWidget(rowCount, 0, perms);
}

void ClassEditDialog::_AddMethRow(std::shared_ptr<MetaClassMethod> meth){
    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int index = perms->findData(QChar(meth->GetPermission()));
    perms->setCurrentIndex(index);

    int rowCount = ui->methTable->rowCount();
    ui->methTable->setRowCount(rowCount+1);

    ui->methTable->setCellWidget(rowCount, M_PERM, perms);
    ui->methTable->setItem(rowCount, M_RETURN_TYPE, new QTableWidgetItem(QString::fromStdString(meth->GetReturnType())));
    ui->methTable->setItem(rowCount, M_NAME, new QTableWidgetItem(QString::fromStdString(meth->GetName())));
    QString str;
    std::set<MetaClassMethod::DataType>::iterator it;
    auto params = meth->GetParameters();
    for(it = params.begin(); it != params.end(); ++it){
        str.append(QString::fromStdString(*it));
        if(it != std::prev(params.cend())){
            str.append(',');
        }
    }
    ui->methTable->setItem(rowCount, M_PARAMS, new QTableWidgetItem(str));
}

void ClassEditDialog::RemoveMethRow(){
    QModelIndexList sel_indexes = ui->methTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        int sel_row = index.row();
        emit SigRemoveMethRow(sel_row);
    }
}






