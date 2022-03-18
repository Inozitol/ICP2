#pragma once

#include "relation.h"
#include "metaclass.h"

class Aggregation : public Relation
{
public:
    Aggregation(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
