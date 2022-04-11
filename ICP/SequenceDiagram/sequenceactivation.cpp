#include "sequenceactivation.h"

SequenceActivation::SequenceActivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Activation),
      _lifeline(lifeline){}

std::shared_ptr<SequenceLifeline> SequenceActivation::GetLifeline(){
    return _lifeline;
}
