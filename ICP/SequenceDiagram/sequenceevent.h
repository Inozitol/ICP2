#pragma once

class SequenceEvent
{
public:
    enum Type{
        Activation,
        Deactivation,
        Message,
        Nop,
        Return
    };

    SequenceEvent(Type);
    Type GetType();

    bool GetStatus();
    void SetStatus(bool stat);
private:
    Type _type;
    bool _status = true;
};
