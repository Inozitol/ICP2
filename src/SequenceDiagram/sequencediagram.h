#pragma once

#include <memory>
#include <vector>

#include "sequencelifeline.h"
#include "sequenceevent.h"
#include "sequenceactivation.h"
#include "sequencedeactivation.h"
#include "sequencemessage.h"
#include "../ClassDiagram/metaclass.h"

///
/// \brief Class for the sequence diagram.
///
/// Class maintains all lifelines and events between them.
///
class SequenceDiagram
{
public:
    /// \brief Map, which binds the shared pointer of a lifeline to its name.
    using LifelineVector = std::map<SequenceLifeline::Name, std::shared_ptr<SequenceLifeline>>;
    /// \brief Vector of events in the sequence diagram.
    using Timeline = std::vector<std::shared_ptr<SequenceEvent>>;

    /// \brief Class constructor.
    SequenceDiagram();

    /// \brief Method for inserting a lifeline into the sequence diagram.
    /// \param name name of the lifeline, which is to be inserted.
    /// \param metaclass shared pointer to the meta class of the lifeline.
    void InsertLifeline(SequenceLifeline::Name name, std::shared_ptr<MetaClass> metaclass);
    /// \brief Method for inserting a lifeline into the sequence diagram.
    /// \param lifeline shared pointer to the lifeline, which is to be inserted.
    void InsertLifeline(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for removing a lifeline from the sequence diagram.
    /// \param name name of the lifeline, which is to be removed.
    void EraseLifeline(SequenceLifeline::Name name);
    /// \brief Method for obtaining the shared pointer to a lifeline, by its name.
    /// \param name name of the lifeline.
    /// \return shared pointer to the lifeline.
    std::shared_ptr<SequenceLifeline> GetLifeline(SequenceLifeline::Name name);
    /// \brief Method for obtaining a map of all lifelines.
    /// \return a map of all lifelines.
    LifelineVector GetLifelines();

    /// \brief Method for pushing an event onto the event stack.
    /// \param event shared pointer to the event.
    void EventPush(std::shared_ptr<SequenceEvent> event);
    /// \brief Method for popping an event from the event stack.
    void EventPop();
    /// \brief Method for moving an event earlier into the timeline by one.
    /// \param index index of the event.
    void EventMoveUp(int index);
    /// \brief Method for moving an event later into the timeline by one.
    /// \param index index of the event.
    void EventMoveDown(int index);
    /// \brief Method for removing an event from the timeline.
    /// \param index index of the event.
    void RemoveEvent(int index);
    /// \brief Method for obtaining the event on the top of the event stack.
    /// \return shared pointer to the event on the top of the stack.
    std::shared_ptr<SequenceEvent> GetEventTop();
    /// \brief Method for obtaining the event on the index in the event stack.
    /// \param index index of the event.
    /// \return shared pointer to the event on the index.
    std::shared_ptr<SequenceEvent> GetEvent(int index);
    /// \brief Method for obtaining all of the events in the sequence diagram.
    /// \return a vector of all the events.
    Timeline GetTimeline();
    /// \brief Method for clearing the timeline and all lifelines in the diagram.
    void Clear();
    /// \brief Method for safely renaming a lifeline
    /// \param from Old name
    /// \param to New name
    void RenameLifeline(SequenceLifeline::Name from, SequenceLifeline::Name to);

private:
    /// \brief Map of all lifelines in the sequence diagram.
    LifelineVector _lifelines;
    /// \brief Vector of all events in the sequence diagram.
    Timeline _timeline;
};
