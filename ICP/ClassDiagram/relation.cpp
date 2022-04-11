#include "relation.h"

Relation::Relation(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2){
    _relation.first = class1;
    _relation.second = class2;
}

