#include "sequencemessage.h"

SequenceMessage::SequenceMessage(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest)
    :SequenceEvent(Message),
     _origin(orig), _destination(dest){}

std::shared_ptr<SequenceLifeline> SequenceMessage::GetOrigin(){
    return _origin;
}

std::shared_ptr<SequenceLifeline> SequenceMessage::GetDestination(){
    return _destination;
}
