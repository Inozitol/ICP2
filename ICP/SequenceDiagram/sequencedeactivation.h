#pragma once

#include <memory>

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceDeactivation : public SequenceEvent
{
public:
    SequenceDeactivation(std::shared_ptr<SequenceLifeline>);
    SequenceDeactivation();

    std::shared_ptr<SequenceLifeline> GetLifeline();
    void SetLifeline(std::shared_ptr<SequenceLifeline>);
private:
    std::shared_ptr<SequenceLifeline> _lifeline;
};

