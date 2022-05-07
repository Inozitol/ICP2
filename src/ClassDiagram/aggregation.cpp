#include "aggregation.h"

Aggregation::Aggregation(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    : Relation(Aggre, class1, class2)
{

}
