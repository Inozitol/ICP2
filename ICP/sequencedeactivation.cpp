#include "sequencedeactivation.h"

SequenceDeactivation::SequenceDeactivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Deactivation),
      _lifeline(lifeline){}

std::shared_ptr<SequenceLifeline> SequenceDeactivation::GetLifeline(){
    return _lifeline;
}
