#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceReturn : public SequenceEvent
{
public:
    SequenceReturn(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg);
    std::shared_ptr<SequenceLifeline> GetOrigin();
    std::shared_ptr<SequenceLifeline> GetDestination();
    std::string GetMessage();

private:
    std::shared_ptr<SequenceLifeline> _origin;
    std::shared_ptr<SequenceLifeline> _destination;
    std::string _msg;
};
