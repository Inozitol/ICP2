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
    for (auto it = _timeline.begin(); it != _timeline.end(); it++){
        switch((*it)->GetType()){
            case SequenceEvent::Activation:
            {
                auto activation = std::static_pointer_cast<SequenceActivation>(*it);
                if(activation->GetLifeline()->GetName() == name){
                    _timeline.erase(it--);
                }
            }
            break;

            case SequenceEvent::Deactivation:
            {
                auto deactivation = std::static_pointer_cast<SequenceDeactivation>(*it);
                if(deactivation->GetLifeline()->GetName() == name){
                    _timeline.erase(it--);
                }
            }
            break;

            case SequenceEvent::Return:
            case SequenceEvent::Message:
            {
                auto message = std::static_pointer_cast<SequenceMessage>(*it);
                auto src_name = message->GetOrigin()->GetName();
                auto dst_name = message->GetDestination()->GetName();
                if(src_name == name || dst_name == name){
                    _timeline.erase(it--);
                }
            }
            break;

            case SequenceEvent::Nop:
            // Sip a cup of coffee
            break;
        }
    }
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
std::shared_ptr<SequenceEvent> SequenceDiagram::GetEvent(int index){
    return _timeline.at(index);
}

void SequenceDiagram::Clear(){
    _lifelines.clear();
    _timeline.clear();
}

void SequenceDiagram::RemoveEvent(int index){
    _timeline.erase(_timeline.begin()+index);
}

void SequenceDiagram::RenameLifeline(SequenceLifeline::Name from, SequenceLifeline::Name to){
    if(from != to){
        _lifelines[to] = _lifelines.at(from);
        _lifelines.erase(from);
    }
}
