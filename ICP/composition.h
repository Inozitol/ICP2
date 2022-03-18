#pragma once

#include "relation.h"
#include "metaclass.h"

class Composition : public Relation
{
public:
    Composition(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
