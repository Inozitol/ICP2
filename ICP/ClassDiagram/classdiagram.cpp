#include "classdiagram.h"


ClassDiagram::ClassDiagram(){}

void ClassDiagram::InsertClass(std::shared_ptr<MetaClass> metaclass){
    _classes.insert(std::make_pair(metaclass->GetName(),metaclass));
}

void ClassDiagram::EraseClass(MetaClass::Name name){
    _classes.erase(name);
}

ClassDiagram::MetaClassMap ClassDiagram::GetClasses(){
    return _classes;
}

void ClassDiagram::ClearClasses(){
    _classes.clear();
}

std::shared_ptr<MetaClass> ClassDiagram::GetClass(MetaClass::Name name){
    return _classes.at(name);
}

void ClassDiagram::InsertRelation(std::shared_ptr<Relation> relation){
    if(_relations.empty()){
        _relations[0] = relation;
    } else {
        _relations.insert(std::make_pair(_relations.rbegin()->first,relation));
    }
    relation->SetIndex(_relations.rbegin()->first);
}

void ClassDiagram::EraseRelation(int relation_reference){
    _relations.erase(relation_reference);
}

ClassDiagram::RelationMap ClassDiagram::GetRelations(){
    return _relations;
}

void ClassDiagram::ClearRelations(){
    _relations.clear();
}

void ClassDiagram::Clear(){
    ClearClasses();
    ClearRelations();
}
