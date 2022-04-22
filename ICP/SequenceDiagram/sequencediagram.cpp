#include <stdexcept>

#include "sequencediagram.h"

SequenceDiagram::SequenceDiagram(){}

void SequenceDiagram::InsertLifeline(SequenceLifeline::Name name, std::shared_ptr<MetaClass> metaclass){
    _lifelines.insert(std::make_pair(name,std::make_shared<SequenceLifeline>(name, metaclass)));
}

void SequenceDiagram::InsertLifeline(std::shared_ptr<SequenceLifeline> lifeline){
    _lifelines.insert(std::make_pair(lifeline->GetName(),lifeline));
}

void SequenceDiagram::EraseLifeline(SequenceLifeline::Name name){
    _lifelines.erase(name);
}

std::shared_ptr<SequenceLifeline> SequenceDiagram::GetLifeline(SequenceLifeline::Name name){
    return _lifelines.at(name);
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

void SequenceDiagram::EventMoveUp(int index){
    auto item = _timeline.at(index);
    _timeline.erase(_timeline.begin()+index);
    _timeline.insert(_timeline.begin()+(index-1), item);
}

void SequenceDiagram::EventMoveDown(int index){
    auto item = _timeline.at(index);
    _timeline.erase(_timeline.begin()+index);
    _timeline.insert(_timeline.begin()+(index+1), item);
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
