#include "sequencereturn.h"

SequenceReturn::SequenceReturn(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg, DataType return_type)
    :SequenceEvent(Return),
     _origin(orig), _destination(dest), _msg(msg), _return_type(return_type){}

std::shared_ptr<SequenceLifeline> SequenceReturn::GetOrigin(){
    return _origin;
}

std::shared_ptr<SequenceLifeline> SequenceReturn::GetDestination(){
    return _destination;
}

std::string SequenceReturn::GetMessage(){
    return _msg;
}

SequenceReturn::DataType SequenceReturn::GetReturnType(){
    return _return_type;
}
