#include "sequencedeactivation.h"

SequenceDeactivation::SequenceDeactivation(std::shared_ptr<SequenceLifeline> lifeline)
    :SequenceEvent(Deactivation),
      _lifeline(lifeline){}
