#include "relation.h"

const std::unordered_map<Relation::Type, std::string> Relation::type2symb = {
        {Relation::Aggre, ".<>"},
        {Relation::Assoc, "--"},
        {Relation::Compo, "-<>"},
        {Relation::Gener, "-->"}
};

Relation::Relation(Type type, std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    :_type(type){
    _relation.first = class1;
    _relation.second = class2;
}

Relation::Type Relation::GetType(){
    return _type;
}

std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> Relation::GetPair(){
    return _relation;
}

std::shared_ptr<MetaClass> Relation::GetSource(){
    return _relation.first;
}

std::shared_ptr<MetaClass> Relation::GetDestination(){
    return _relation.second;
}

Relation::Cardinality Relation::GetSrcCardinality(){
    return _srcCardinality;
}

Relation::Cardinality Relation::GetDesCardinality(){
    return _dstCardinality;
}

void Relation::SetSrcCardinality(Cardinality crd){
    _srcCardinality = crd;
}

void Relation::SetDstCardinality(Cardinality crd){
    _dstCardinality = crd;
}

void Relation::SetIndex(int index){
    _index = index;
}
int Relation::GetIndex(){
    return _index;
}
