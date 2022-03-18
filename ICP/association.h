#pragma once

#include "relation.h"
#include "metaclass.h"

class Association : public Relation
{
public:
    Association(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};

