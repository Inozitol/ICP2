#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Aggregation relation between two Classes
///
class Aggregation : public Relation
{
public:
    Aggregation(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};
