#include "sequencedeactivation.h"

SequenceDeactivation::SequenceDeactivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Deactivation),
      _lifeline(lifeline){}

SequenceDeactivation::SequenceDeactivation()
    :SequenceEvent(Deactivation){}

std::shared_ptr<SequenceLifeline> SequenceDeactivation::GetLifeline(){
    return _lifeline;
}

void SequenceDeactivation::SetLifeline(std::shared_ptr<SequenceLifeline> lifeline){
    _lifeline = lifeline;
}
