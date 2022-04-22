#include "sequencereturn.h"

SequenceReturn::SequenceReturn(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg)
    :SequenceEvent(Return),
     _origin(orig), _destination(dest), _msg(msg){}

std::shared_ptr<SequenceLifeline> SequenceReturn::GetOrigin(){
    return _origin;
}

std::shared_ptr<SequenceLifeline> SequenceReturn::GetDestination(){
    return _destination;
}

std::string SequenceReturn::GetMessage(){
    return _msg;
}
