#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

#include <memory>

class SequenceMessage : public SequenceEvent
{
public:
    SequenceMessage(std::shared_ptr<SequenceLifeline>, std::shared_ptr<SequenceLifeline>, std::string);
    SequenceMessage();

    std::shared_ptr<SequenceLifeline> GetOrigin();
    std::shared_ptr<SequenceLifeline> GetDestination();
    std::string GetMessage();

    void SetOrigin(std::shared_ptr<SequenceLifeline>);
    void SetDestination(std::shared_ptr<SequenceLifeline>);
    void SetMessage(std::string);
private:
    std::shared_ptr<SequenceLifeline> _origin;
    std::shared_ptr<SequenceLifeline> _destination;
    std::string _msg;
};
