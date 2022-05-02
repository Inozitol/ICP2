#pragma once
#include <QObject>

class SequenceEvent
{
public:
    enum Type{
        Activation = 0,
        Deactivation,
        Message,
        Return,
        Nop
    };

    SequenceEvent(Type);
    Type GetType();

    bool GetStatus();
    void SetStatus(bool stat);
private:
    Type _type;
    bool _status = true;
};


Q_DECLARE_METATYPE(std::shared_ptr<SequenceEvent>);
