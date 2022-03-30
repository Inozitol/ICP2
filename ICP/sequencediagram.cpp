#include <stdexcept>

#include "sequencediagram.h"

SequenceDiagram::SequenceDiagram(){}

void SequenceDiagram::InsertLifeline(SequenceLifeline::Name name, std::shared_ptr<MetaClass> metaclass){
    _lifelines.push_back(std::make_shared<SequenceLifeline>(name, metaclass));
}

void SequenceDiagram::EraseLifeline(int index){
    _lifelines.erase(_lifelines.begin() + index);
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
