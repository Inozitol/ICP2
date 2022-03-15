#include "relation.h"

Relation::Relation(MetaClass* class1, MetaClass* class2){
    _relation.first = class1;
    _relation.second = class2;
}

