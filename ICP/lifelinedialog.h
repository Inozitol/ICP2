#pragma once

#include <memory>

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "environment.h"
#include "SequenceDiagram/sequencelifeline.h"

namespace Ui {
    class LifelineDialog;
}

class LifelineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LifelineDialog(QWidget *parent = nullptr);
    ~LifelineDialog();

    std::shared_ptr<SequenceLifeline> GetLifeline();

private:
    void InitComboBox();

    Ui::LifelineDialog *ui;
    Environment* _environment;

private slots:
    void acceptCondition();

signals:
    void acceptedSafe();
};
