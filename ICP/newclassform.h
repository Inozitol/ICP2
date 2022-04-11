#pragma once

#include "metaclass.h"
#include "metaclassattribute.h"
#include "metaclassmethod.h"

#include <memory>
#include <string>
#include <sstream>

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QToolButton>
#include <QAction>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class NewClassForm; }
QT_END_NAMESPACE

class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    ClassEditDialog(QWidget* parent = nullptr);
    ~ClassEditDialog();
    std::shared_ptr<MetaClass> GetClassPtr();

private:
    void InitButtons();

    Ui::NewClassForm* ui;

    enum AttrCol{
        A_PERM = 0,
        A_DATA_TYPE,
        A_NAME
    };

    enum MethCol{
        M_PERM = 0,
        M_RETURN_TYPE,
        M_NAME,
        M_PARAMS
    };
    std::shared_ptr<MetaClass> _class;

private slots:

    void AddAttrRow();
    void RemoveAttrRow();

    void AddMethRow();
    void RemoveMethRow();

signals:
    void SigRemoveAttrRow(int);
    void SigRemoveMethRow(int);
};
