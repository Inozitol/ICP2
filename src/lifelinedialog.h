#pragma once

#include <memory>

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "environment.h"
#include "SequenceDiagram/sequencelifeline.h"

#include "utils.h"

namespace Ui {
    class LifelineDialog;
}

///
/// \brief Class representing dialogs for creating lifelines.
///
class LifelineDialog : public QDialog
{
    Q_OBJECT

public:
    /// \brief Class constructor.
    /// \param parent pointer to the parent widget.
    explicit LifelineDialog(QWidget *parent = nullptr);
    /// \brief Class destructor.
    ~LifelineDialog();

    /// \brief Method for obtaining the shared pointer to the new lifeline.
    /// \return shared pointer to the lifeline.
    std::shared_ptr<SequenceLifeline> GetLifeline();

private:
    /// \brief Initializing values of the combobox in the lifeline creation dialog.
    void InitComboBox();
    /// \brief UI of the entire dialog.
    Ui::LifelineDialog *ui;
    /// \brief Singleton environment variable.
    Environment* _environment;

private slots:
    /// \brief Checks if the contents of the dialog are valid and emits acceptedSafe if yes.
    void acceptCondition();

signals:
    /// \brief Signal for determining if values in the dialog are valid.
    void acceptedSafe();
};
