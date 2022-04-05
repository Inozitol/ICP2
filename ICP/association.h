#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Association relation between two Classes
///
class Association : public Relation
{
public:
    Association(std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);
};

