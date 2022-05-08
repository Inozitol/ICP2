#include "classdialog.h"
#include "ui_classdialog.h"

ClassDialog::ClassDialog(QWidget* parent)
    :QDialog(parent),
      ui(new Ui::ClassDialog),
      _environment(Environment::GetEnvironment()),
      _class(nullptr)
{
    ui->setupUi(this);
    InitButtons();
    InitConnections();
}

ClassDialog::ClassDialog(std::shared_ptr<MetaClass> metaclass, QWidget* parent)
    :QDialog(parent),
      ui(new Ui::ClassDialog),
      _environment(Environment::GetEnvironment()),
      _class(metaclass)
{
    ui->setupUi(this);
    InitButtons();
    InitContent();
    InitConnections();
}

void ClassDialog::InitConnections(){
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this](){if(isValid()) emit acceptedSafe();});
    connect(this, &ClassDialog::acceptedSafe, this, &QDialog::accept);

    connect(ui->attrTable, &QTableWidget::cellChanged, this, &ClassDialog::AttrCellChanged);
    connect(ui->methTable, &QTableWidget::cellChanged, this, &ClassDialog::MethCellChanged);
}

void ClassDialog::InitContent(){
    ui->className->setText(QString::fromStdString(_class->GetName()));
    for(auto attr : _class->GetAttributes()){
        _AddAttrRow(attr.second);
    }
    for(auto meth : _class->GetMethods()){
        _AddMethRow(meth.second);
    }
}

ClassDialog::~ClassDialog(){
    delete(ui);
}

std::shared_ptr<MetaClass> ClassDialog::GetClassPtr(){
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

void ClassDialog::InitButtons(){
    connect(ui->attrButtAdd, 	&QToolButton::clicked, 	this, 	&ClassDialog::AddAttrRow);
    connect(ui->attrButtRemove, &QToolButton::clicked, 	this, 	&ClassDialog::RemoveAttrRow);
    connect(ui->methButtAdd, 	&QToolButton::clicked, 	this, 	&ClassDialog::AddMethRow);
    connect(ui->methButtRemove, &QToolButton::clicked, 	this, 	&ClassDialog::RemoveMethRow);

    connect(this, &ClassDialog::SigRemoveAttrRow, ui->attrTable, &QTableWidget::removeRow);
    connect(this, &ClassDialog::SigRemoveMethRow, ui->methTable, &QTableWidget::removeRow);
}

void ClassDialog::AddAttrRow(){

    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int rowCount = ui->attrTable->rowCount();
    ui->attrTable->setRowCount(rowCount+1);

    ui->attrTable->setCellWidget(rowCount, 0, perms);
}

void ClassDialog::_AddAttrRow(std::shared_ptr<MetaClassAttribute> attr){

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

void ClassDialog::RemoveAttrRow(){
    QModelIndexList sel_indexes = ui->attrTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        int sel_row = index.row();
        emit SigRemoveAttrRow(sel_row);
    }
}

void ClassDialog::AddMethRow(){

    QComboBox* perms = new QComboBox(this);
    perms->addItem(tr("Public"), 	QChar('+'));
    perms->addItem(tr("Private"), 	QChar('-'));
    perms->addItem(tr("Protected"), QChar('#'));
    perms->addItem(tr("Package"), 	QChar('~'));

    int rowCount = ui->methTable->rowCount();
    ui->methTable->setRowCount(rowCount+1);

    ui->methTable->setCellWidget(rowCount, 0, perms);
}

void ClassDialog::_AddMethRow(std::shared_ptr<MetaClassMethod> meth){
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

void ClassDialog::RemoveMethRow(){
    QModelIndexList sel_indexes = ui->methTable->selectionModel()->selectedIndexes();
    for(auto index : sel_indexes){
        int sel_row = index.row();
        emit SigRemoveMethRow(sel_row);
    }
}

bool ClassDialog::isValid(){
    if(ui->className->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Critical,
                   tr("Error"),
                   tr("Class name is not set"),
                   QMessageBox::Ok);
        msgBox.exec();
        return false;
    }
    QTableWidgetItem* q_dtype;
    QTableWidgetItem* q_name;
    QTableWidgetItem* q_params;
    int rowCount = ui->attrTable->rowCount();
    for(int row=0; row < rowCount; row++){
        q_dtype = ui->attrTable->item(row, A_DATA_TYPE);
        q_name =  ui->attrTable->item(row, A_NAME);

        // Is name empty
        if((q_name && q_name->text().isEmpty()) || !q_name){
            QString str;
            str.append(tr("Attribute name is missing on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append('.');
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;

        }
        // Is name duplicated
        if(q_name && q_name->foreground().color() == Qt::red){
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       tr("Attribute table contains duplicated names."),
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        // Is name alpanumeric
        if(!std::regex_match(q_name->text().toStdString(), _nameRegex)){
            QString str;
            str.append(tr("Attribute name on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append(tr(" can only contain alphanumeric characters."));
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        // Is type empty
        if((q_dtype && q_dtype->text().isEmpty()) || !q_dtype){
            QString str;
            str.append(tr("Data type of attribute on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append(" is missing.");
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
    }

    rowCount = ui->methTable->rowCount();
    for(int row=0; row < rowCount; row++){
        q_dtype = 	ui->methTable->item(row, M_RETURN_TYPE);
        q_name =  	ui->methTable->item(row, M_NAME);
        q_params =	ui->methTable->item(row, M_PARAMS);

        // Is name empty
        if((q_name && q_name->text().isEmpty()) || !q_name){
            QString str;
            str.append(tr("Method name is missing on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append('.');
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        // Is name duplicated
        if(q_name && q_name->foreground().color() == Qt::red){
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       tr("Method table contains duplicated names."),
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        // Is name alphanumeric
        if(!std::regex_match(q_name->text().toStdString(), _nameRegex)){
            QString str;
            str.append(tr("Method name on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append(tr(" can only contain alphanumeric characters."));
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        // Is type empty
        if((q_dtype && q_dtype->text().isEmpty()) || !q_dtype){
            QString str;
            str.append(tr("Return type of method on row "));
            str.append(QString::fromStdString(std::to_string(row+1)));
            str.append(" is missing.");
            QMessageBox msgBox(QMessageBox::Critical,
                       tr("Error"),
                       str,
                       QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
    }
    return true;
}

void ClassDialog::AttrCellChanged(int, int column){
    if(column == A_NAME){
        int rowCount = ui->attrTable->rowCount();
        for(int rf=0; rf < rowCount; rf++){
            auto qf_name = ui->attrTable->item(rf, A_NAME);
            for(int rs=0; rs < rowCount; rs++){
                auto qs_name = ui->attrTable->item(rs, A_NAME);
                if(qf_name && qs_name && qf_name != qs_name){
                    if(qf_name->text() == qs_name->text()){
                        ui->attrTable->blockSignals(true);
                        qf_name->setForeground(Qt::red);
                        qf_name->setToolTip(tr("Attribute with this name already exists."));
                        ui->attrTable->blockSignals(false);
                        break;
                    }else{
                        ui->attrTable->blockSignals(true);
                        qf_name->setForeground(Qt::black);
                        qf_name->setToolTip(tr(""));
                        ui->attrTable->blockSignals(false);
                    }
                }
            }
        }
    }
}

void ClassDialog::MethCellChanged(int, int column){
    if(column == M_NAME){
        int rowCount = ui->methTable->rowCount();
        for(int rf=0; rf < rowCount; rf++){
            auto qf_name = ui->methTable->item(rf, M_NAME);
            for(int rs=0; rs < rowCount; rs++){
                auto qs_name = ui->methTable->item(rs, M_NAME);
                if(qf_name && qs_name && qf_name != qs_name){
                    if(qf_name->text() == qs_name->text()){
                        ui->methTable->blockSignals(true);
                        qf_name->setForeground(Qt::red);
                        qf_name->setToolTip(tr("Attribute with this name already exists."));
                        ui->methTable->blockSignals(false);
                        break;
                    }else{
                        ui->methTable->blockSignals(true);
                        qf_name->setForeground(Qt::black);
                        qf_name->setToolTip(tr(""));
                        ui->methTable->blockSignals(false);
                    }
                }
            }
        }
    }
}
