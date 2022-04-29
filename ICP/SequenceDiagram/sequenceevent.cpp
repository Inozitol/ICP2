#include "sequenceevent.h"

SequenceEvent::SequenceEvent(Type type)
    :_type(type){}

SequenceEvent::Type SequenceEvent::GetType(){
    return _type;
}

bool SequenceEvent::GetStatus(){
    return _status;
}

void SequenceEvent::SetStatus(bool stat){
    this->_status = stat;
}

std::string SequenceEvent::GetErrorMsg(){
    return _errorMsg;
}

void SequenceEvent::SetErrorMsg(std::string msg){
    this->_errorMsg = msg;
}
