#pragma once

#include "relation.h"
#include "metaclass.h"

class Generalization : public Relation
{
public:
    Generalization(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
