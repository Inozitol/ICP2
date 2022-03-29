#include "sequenceactivation.h"

SequenceActivation::SequenceActivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Activation),
      _lifeline(lifeline){}
