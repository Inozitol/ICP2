#pragma once

#include <utility>
#include <memory>

#include "metaclass.h"

class Relation
{
public:
    Relation(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
    char relation_type;
protected:
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> _relation;
};
