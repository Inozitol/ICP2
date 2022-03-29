#include "sequenceevent.h"

SequenceEvent::SequenceEvent(Type type)
    :_type(type){}

SequenceEvent::Type SequenceEvent::GetType(){
    return _type;
}
