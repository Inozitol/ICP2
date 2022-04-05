#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Composition relation between two classes
///
class Composition : public Relation
{
public:
    Composition(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
