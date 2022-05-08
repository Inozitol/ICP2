// Autor: xmurga01

#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Aggregation relation between two Classes
///
class Aggregation : public Relation
{
public:
    /// \brief Class constructor.
    /// \param class1 origin of relation.
    /// \param class2 destination of relation.
    Aggregation(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2);
};
