#pragma once

#include "relation.h"
#include "metaclass.h"

///
/// \brief Association relation between two Classes
///
class Association : public Relation
{
public:
    /// \brief Class constructor.
    /// \param class1 origin of relation.
    /// \param class2 destination of relation.
    Association(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2);
};

