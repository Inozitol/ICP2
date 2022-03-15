#pragma once

#include <utility>

#include "metaclass.h"

class Relation
{
public:
    Relation();
    void CreateRelation(MetaClass*, MetaClass*);

protected:
    std::pair<MetaClass*, MetaClass*> _relation;
};
