#pragma once

#include <memory>
#include <vector>

#include "sequencelifeline.h"
#include "sequenceevent.h"

class SequenceDiagram
{
public:
    using LifelineVector = std::vector<std::shared_ptr<SequenceLifeline>>;
    using EventVector = std::vector<std::shared_ptr<SequenceEvent>>;
    using Timeline = std::vector<EventVector>;

    SequenceDiagram();

    void TimelinePush();
    void TimelinePush(EventVector);
    void TimelinePop();

    void EventPush(std::shared_ptr<SequenceEvent>);
    void EventPop();

    EventVector GetTimelineTop();
    std::shared_ptr<SequenceEvent> GetEventTop();

    EventVector GetTimelineIndex(int);
    std::shared_ptr<SequenceEvent> GetEventIndex(int);

private:
    LifelineVector _lifelines;
    Timeline _timeline;
};
