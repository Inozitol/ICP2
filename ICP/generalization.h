#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Generalization relation between two Classes
///
class Generalization : public Relation
{
public:
    Generalization(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
