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

private:
    Type _type;
};
