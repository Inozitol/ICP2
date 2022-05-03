#pragma once

#include <memory>
#include <vector>

#include "sequencelifeline.h"
#include "sequenceevent.h"
#include "sequenceactivation.h"
#include "sequencedeactivation.h"
#include "sequencemessage.h"
#include "../ClassDiagram/metaclass.h"

class SequenceDiagram
{
public:
    using LifelineVector = std::map<SequenceLifeline::Name, std::shared_ptr<SequenceLifeline>>;
    using Timeline = std::vector<std::shared_ptr<SequenceEvent>>;

    SequenceDiagram();

    void InsertLifeline(SequenceLifeline::Name, std::shared_ptr<MetaClass>);
    void InsertLifeline(std::shared_ptr<SequenceLifeline>);
    void EraseLifeline(SequenceLifeline::Name);
    std::shared_ptr<SequenceLifeline> GetLifeline(SequenceLifeline::Name);
    LifelineVector GetLifelines();

    void EventPush(std::shared_ptr<SequenceEvent>);
    void EventPop();
    void EventMoveUp(int);
    void EventMoveDown(int);
    void RemoveEvent(int);

    std::shared_ptr<SequenceEvent> GetEventTop();
    std::shared_ptr<SequenceEvent> GetEvent(int);

    Timeline GetTimeline();

    void Clear();

private:

    LifelineVector _lifelines;
    Timeline _timeline;
};
