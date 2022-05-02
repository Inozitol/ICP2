#pragma once

#include <QObject>
#include <iostream>

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
    std::string GetErrorMsg();
    void SetErrorMsg(std::string msg);
private:
    Type _type;
    bool _status = true;
    std::string _errorMsg = "";
};


Q_DECLARE_METATYPE(std::shared_ptr<SequenceEvent>);
