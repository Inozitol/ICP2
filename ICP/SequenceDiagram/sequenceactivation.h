#pragma once

#include <memory>

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceActivation : public SequenceEvent
{
public:
    SequenceActivation();
    SequenceActivation(std::shared_ptr<SequenceLifeline>);

    std::shared_ptr<SequenceLifeline> GetLifeline();
    void SetLifeline(std::shared_ptr<SequenceLifeline>);
private:
    std::shared_ptr<SequenceLifeline> _lifeline;
};
