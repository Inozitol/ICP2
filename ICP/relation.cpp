#include "relation.h"

Relation::Relation(){}

void Relation::CreateRelation(MetaClass* class1, MetaClass* class2){
    _relation.first = class1;
    _relation.second = class2;
}
