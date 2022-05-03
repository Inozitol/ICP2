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

namespace Ui {
    class EventDialog;
    class EventActivation;
    class EventDeactivation;
    class EventMessage;
    class EventReturn;
    class EventSpacer;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    EventDialog(QWidget *parent = nullptr);
    EventDialog(std::shared_ptr<SequenceEvent>, QWidget* parent= nullptr);
    ~EventDialog();

    std::shared_ptr<SequenceEvent> GetEvent();

private:
    void InitLayouts();
    void InitConnects();

    void switchEvent(SequenceEvent::Type);
    bool isValid();

    Ui::EventDialog *ui;
    Ui::EventActivation *uiAct;
    Ui::EventDeactivation *uiDea;
    Ui::EventMessage *uiMsg;
    Ui::EventReturn *uiRet;
    Ui::EventSpacer *uiSpa;

    QWidget* _actWidget;
    QWidget* _deaWidget;
    QWidget* _msgWidget;
    QWidget* _retWidget;
    QWidget* _spaWidget;

    Environment* _environment;

    SequenceEvent::Type _currType;

    std::shared_ptr<SequenceEvent> _event;

signals:
    void acceptedSafe();
};
