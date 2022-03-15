#pragma once

#include <utility>

#include "metaclass.h"

class Relation
{
public:
    Relation();
protected:
    std::pair<MetaClass*, MetaClass*> _relation;
};
