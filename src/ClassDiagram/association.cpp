#include "association.h"

Association::Association(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    : Relation(Assoc, class1, class2)
{

}
