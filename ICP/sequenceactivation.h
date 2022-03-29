#pragma once

#include <memory>

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceActivation : public SequenceEvent
{
public:
    SequenceActivation(std::shared_ptr<SequenceLifeline>);

private:
    std::shared_ptr<SequenceLifeline> _lifeline;
};
