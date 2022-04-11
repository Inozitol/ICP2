#include "sequencelifeline.h"

SequenceLifeline::SequenceLifeline(Name name, std::shared_ptr<MetaClass> metaclass)
    :_name(name), _class(metaclass){}

void SequenceLifeline::ChangeName(Name name){
    _name = name;
}

SequenceLifeline::Name SequenceLifeline::GetName(){
    return _name;
}

void SequenceLifeline::ChangeClass(std::shared_ptr<MetaClass> metaclass){
    _class = metaclass;
}

std::shared_ptr<MetaClass> SequenceLifeline::GetClass(){
    return _class;
}
