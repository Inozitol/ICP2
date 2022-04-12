#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

#include <memory>

class SequenceMessage : public SequenceEvent
{
public:
    SequenceMessage(std::shared_ptr<SequenceLifeline>, std::shared_ptr<SequenceLifeline>, std::string);

    std::shared_ptr<SequenceLifeline> GetOrigin();
    std::shared_ptr<SequenceLifeline> GetDestination();
    std::string GetMessage();
private:
    std::shared_ptr<SequenceLifeline> _origin;
    std::shared_ptr<SequenceLifeline> _destination;
    std::string _msg;
};