#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Generalization relation between two Classes
///
class Generalization : public Relation
{
public:
    /// \brief Class constructor.
    /// \param class1 origin of relation.
    /// \param class2 destination of relation.
    Generalization(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2);
};
