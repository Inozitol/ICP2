#include "sequenceactivation.h"

SequenceActivation::SequenceActivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Activation),
      _lifeline(lifeline){}

SequenceActivation::SequenceActivation()
    :SequenceEvent(Activation){}


std::shared_ptr<SequenceLifeline> SequenceActivation::GetLifeline(){
    return _lifeline;
}

void SequenceActivation::SetLifeline(std::shared_ptr<SequenceLifeline> lifeline){
    _lifeline = lifeline;
}
