#pragma once

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

private:
    Type _type;
};
