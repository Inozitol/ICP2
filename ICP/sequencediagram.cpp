#include <stdexcept>

#include "sequencediagram.h"

SequenceDiagram::SequenceDiagram()
{

}

void SequenceDiagram::TimelinePush(){
    EventVector empty_vector;
    _timeline.push_back(empty_vector);
}

void SequenceDiagram::TimelinePush(EventVector event_vector){
    _timeline.push_back(event_vector);
}

void SequenceDiagram::TimelinePop(){
    _timeline.pop_back();
}

void SequenceDiagram::EventPush(std::shared_ptr<SequenceEvent> event){
    _timeline.back().push_back(event);
}

void SequenceDiagram::EventPop(){
    _timeline.back().pop_back();
}

SequenceDiagram::EventVector SequenceDiagram::GetTimelineTop(){
    return _timeline.back();
}

std::shared_ptr<SequenceEvent> SequenceDiagram::GetEventTop(){
    return _timeline.back().back();
}

// Will return out_of_range exception if out of range!
SequenceDiagram::EventVector SequenceDiagram::GetTimelineIndex(int index){
    return _timeline.at(index);
}

// Will return out_of_range exception if out of range!
std::shared_ptr<SequenceEvent> SequenceDiagram::GetEventIndex(int index){
    return _timeline.back().at(index);
}
