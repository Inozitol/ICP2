#pragma once

#include <memory>
#include <string>
#include <sstream>

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QToolButton>
#include <QAction>
#include <QDebug>

#include "environment.h"
#include "ClassDiagram/metaclass.h"
#include "ClassDiagram/metaclassattribute.h"
#include "ClassDiagram/metaclassmethod.h"

#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NewClassForm; }
QT_END_NAMESPACE

///
/// \brief Class representing dialogs for creating/editing classes.
///
class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    /// \brief Class constructor.
    /// \param parent pointer to the parent widget.
    ClassEditDialog(QWidget* parent = nullptr);
    /// \brief Class constructor.
    /// \param metaclass shared pointer to the class, which will be edited.
    /// \param parent pointer to the parent widget.
    ClassEditDialog(std::shared_ptr<MetaClass> metaclass, QWidget* parent = nullptr);
    /// \brief Class destructor.
    ~ClassEditDialog();
    /// \brief Method for obtaining the shared pointer to the meta class.
    /// \return shared pointer to the meta class.
    std::shared_ptr<MetaClass> GetClassPtr();

private:
    /// \brief Method for initializing utility buttons in the class creation dialog.
    void InitButtons();
    /// \brief Method for filling in existing data when editing a class.
    void InitContent();
    /// \brief Method for adding an existing attribute into the class creation dialog.
    /// \param attr shared pointer to the attribute.
    void _AddAttrRow(std::shared_ptr<MetaClassAttribute> attr);
    /// \brief Method for adding an existing method into the class creation dialog.
    /// \param meth shared pointer to the method.
    void _AddMethRow(std::shared_ptr<MetaClassMethod> meth);

    /// \brief UI of the new class dialog.
    Ui::NewClassForm* ui;
    /// \brief Singleton environment variable.
    Environment* _environment;

    /// \brief Enumeration for the attributes table collumns.
    enum AttrCol{
        A_PERM = 0,
        A_DATA_TYPE,
        A_NAME
    };

    /// \brief Enumeration for the methods table collumns.
    enum MethCol{
        M_PERM = 0,
        M_RETURN_TYPE,
        M_NAME,
        M_PARAMS
    };

    /// \brief Shared pointer to the new/edited meta class.
    std::shared_ptr<MetaClass> _class;

private slots:
    /// \brief Slot for adding an attribute row into the class creation dialog.
    void AddAttrRow();
    /// \brief Slot for removing an attribute row from the class creation dialog.
    void RemoveAttrRow();
    /// \brief Slot for adding a method row into the class creation dialog.
    void AddMethRow();
    /// \brief Slot for removing a method row from the class creation dialog.
    void RemoveMethRow();

signals:
    /// \brief Signal for removing an attribute row from the class creation dialog.
    void SigRemoveAttrRow(int);
    /// \brief Signal for removing a method row from the class creation dialog.
    void SigRemoveMethRow(int);
};
