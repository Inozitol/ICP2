#include "relation.h"

Relation::Relation(Type type, std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    :_type(type){
    _relation.first = class1;
    _relation.second = class2;
}

Relation::Type Relation::GetType(){
    return _type;
}
