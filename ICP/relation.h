#pragma once

#include <utility>

#include "metaclass.h"

class Relation
{
public:
    Relation(MetaClass*, MetaClass*);

protected:
    std::pair<MetaClass*, MetaClass*> _relation;
};
