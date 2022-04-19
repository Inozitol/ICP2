#include <stdexcept>

#include "sequencediagram.h"

SequenceDiagram::SequenceDiagram(){}

void SequenceDiagram::InsertLifeline(SequenceLifeline::Name name, std::shared_ptr<MetaClass> metaclass){
    _lifelines.push_back(std::make_shared<SequenceLifeline>(name, metaclass));
}

void SequenceDiagram::InsertLifeline(std::shared_ptr<SequenceLifeline> lifeline){
    _lifelines.push_back(lifeline);
}

void SequenceDiagram::EraseLifeline(int index){
    _lifelines.erase(_lifelines.begin() + index);
}

std::shared_ptr<SequenceLifeline> SequenceDiagram::GetLifeline(int index){
    return _lifelines.at(index);
}

SequenceDiagram::LifelineVector SequenceDiagram::GetLifelines(){
    return _lifelines;
}

SequenceDiagram::Timeline SequenceDiagram::GetTimeline(){
    return _timeline;
}

void SequenceDiagram::EventPush(std::shared_ptr<SequenceEvent> event){
    _timeline.push_back(event);
}

void SequenceDiagram::EventPop(){
    _timeline.pop_back();
}

std::shared_ptr<SequenceEvent> SequenceDiagram::GetEventTop(){
    return _timeline.back();
}

// Will return out_of_range exception if out of range!
std::shared_ptr<SequenceEvent> SequenceDiagram::GetEventIndex(int index){
    return _timeline.at(index);
}

void SequenceDiagram::Clear(){
    _lifelines.clear();
    _timeline.clear();
}
