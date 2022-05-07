#pragma once

#include <QDialog>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QAbstractButton>
#include <QMessageBox>

#include "environment.h"
#include "SequenceDiagram/sequenceevent.h"
#include "SequenceDiagram/sequencereturn.h"
#include "SequenceDiagram/sequencespacer.h"

#include "utils.h"

namespace Ui {
    class EventDialog;
    class EventActivation;
    class EventDeactivation;
    class EventMessage;
    class EventReturn;
    class EventSpacer;
}

///
/// \brief Class representing dialogs for creating/editing sequence diagram events.
///
class EventDialog : public QDialog
{
    Q_OBJECT

public:
    /// \brief Class constructor (creating mode).
    /// \param parent pointer to the parent widget.
    EventDialog(QWidget *parent = nullptr);
    /// \brief Class constructor (editing mode).
    /// \param event shared pointer to the event, which will be edited.
    /// \param parent pointer to the parent widget.
    EventDialog(std::shared_ptr<SequenceEvent> event, QWidget* parent= nullptr);
    /// \brief Class destructor.
    ~EventDialog();

    /// \brief Method for obtaining the shared pointer to the event.
    /// \return shared pointer to the event.
    std::shared_ptr<SequenceEvent> GetEvent();

private:
    /// \brief Initializing options within the event dialog menu.
    void InitLayouts();
    /// \brief Connecting signals within the dialog menu to various slots.
    void InitConnects();
    /// \brief Method for switching the type of the event.
    /// \param type selected event type.
    void switchEvent(SequenceEvent::Type type);
    /// \brief Method for checking whether given values in the event menu are valid and raising an error message if not.
    /// \return bool, determining if they are valid.
    bool isValid();

    /// \brief UI of the entire dialog.
    Ui::EventDialog *ui;
    /// \brief UI of the activation event type.
    Ui::EventActivation *uiAct;
    /// \brief UI of the deactivation event type.
    Ui::EventDeactivation *uiDea;
    /// \brief UI of the message event type.
    Ui::EventMessage *uiMsg;
    /// \brief UI of the return event type.
    Ui::EventReturn *uiRet;
    /// \brief UI of the spacer event type.
    Ui::EventSpacer *uiSpa;

    /// \brief Activation event type widget.
    QWidget* _actWidget;
    /// \brief Deactivation event type widget.
    QWidget* _deaWidget;
    /// \brief Message event type widget.
    QWidget* _msgWidget;
    /// \brief Return event type widget.
    QWidget* _retWidget;
    /// \brief Spacer event type widget.
    QWidget* _spaWidget;
    /// \brief Singleton environment variable.
    Environment* _environment;
    /// \brief Current selected event type.
    SequenceEvent::Type _currType;
    /// \brief Shared pointer to the selected event.
    std::shared_ptr<SequenceEvent> _event;

signals:
    /// \brief Signal for accepting dialog with valid values.
    void acceptedSafe();
};
