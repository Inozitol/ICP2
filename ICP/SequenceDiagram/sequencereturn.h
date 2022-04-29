#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

class SequenceReturn : public SequenceEvent
{
public:
    using DataType = std::string;

    SequenceReturn(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg, DataType type);
    std::shared_ptr<SequenceLifeline> GetOrigin();
    std::shared_ptr<SequenceLifeline> GetDestination();
    std::string GetMessage();
    DataType GetReturnType();

private:
    std::shared_ptr<SequenceLifeline> _origin;
    std::shared_ptr<SequenceLifeline> _destination;
    std::string _msg;
    DataType _return_type;
};
