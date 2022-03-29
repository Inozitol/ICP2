#pragma once

#include <memory>

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceDeactivation : public SequenceEvent
{
public:
    SequenceDeactivation(std::shared_ptr<SequenceLifeline>);

private:
    std::shared_ptr<SequenceLifeline> _lifeline;
};

