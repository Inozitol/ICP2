#include "sequencemessage.h"

SequenceMessage::SequenceMessage(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg)
    :SequenceEvent(Message),
     _origin(orig), _destination(dest), _msg(msg){}

std::shared_ptr<SequenceLifeline> SequenceMessage::GetOrigin(){
    return _origin;
}

std::shared_ptr<SequenceLifeline> SequenceMessage::GetDestination(){
    return _destination;
}

std::string SequenceMessage::GetMessage(){
    return _msg;
}
