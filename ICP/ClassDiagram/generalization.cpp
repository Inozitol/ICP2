#include "generalization.h"

Generalization::Generalization(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    : Relation(Gener, class1, class2)
{

}
