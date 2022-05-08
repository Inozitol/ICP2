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
    /// \brief Class constructor for creating.
    /// \param parent pointer to the parent widget.
    LifelineDialog(QWidget *parent = nullptr);
    /// \brief Class constructor for editing.
    /// \param sequence Pointer to lifeline to edit.
    /// \param parent Pointer to the parent widget.
    LifelineDialog(std::shared_ptr<SequenceLifeline> lifeline,QWidget *parent = nullptr);
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
    /// \brief Lifeline to be edited/created
    std::shared_ptr<SequenceLifeline> _lifeline;

private slots:
    /// \brief Checks if the contents of the dialog are valid and emits acceptedSafe if yes.
    void acceptCondition();

signals:
    /// \brief Signal for determining if values in the dialog are valid.
    void acceptedSafe();
};
