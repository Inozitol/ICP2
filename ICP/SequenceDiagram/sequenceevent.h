#pragma once
#import <iostream>

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
    bool GetErrorMsg();
    void SetErrorMsg(std::string msg);
private:
    Type _type;
    bool _status = true;
    std::string _errorMsg = "";
};
