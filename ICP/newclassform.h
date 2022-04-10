#pragma once

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

private:
    void InitButtons();

    Ui::NewClassForm* ui;
    QStringList _perms_list= {
        "+ Public",
        "- Private",
        "# Protected",
        "~ Package"
    };


private slots:

    void AddAttrRow();
    void RemoveAttrRow();

    void AddMethRow();
    void RemoveMethRow();

signals:
    void SigRemoveAttrRow(int);
    void SigRemoveMethRow(int);
};
