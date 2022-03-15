#include <utility>

#include "environment.h"

Environment* Environment::_environment = nullptr;

Environment::Environment(){}

Environment* Environment::GetEnvironment(){
    if(_environment==nullptr) _environment = new Environment();

    return _environment;
}

Environment::~Environment(){
    if(_environment!=nullptr) delete(_environment);
}

void Environment::InsertClass(MetaClass* metaclass){
    _classes.insert(std::pair<MetaClass::Name, MetaClass*>(metaclass->GetName(),metaclass));
}

void Environment::EraseClass(MetaClass::Name name){
    _classes.erase(name);
}

int Environment::InsertRelation(Relation* relation){
    _relations.insert(std::pair<int, Relation*>(_relations.rbegin()->first,relation));
    return _relations.rbegin()->first;
}

void Environment::EraseRelation(int relation_reference){
    _relations.erase(relation_reference);
}

