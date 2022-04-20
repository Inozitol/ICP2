#include "relation.h"

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
