#include "association.h"

Association::Association(std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2)
    : Relation(Assoc, class1, class2)
{

}

void Association::SetMessage(std::string msg){
    _msg = msg;
}

std::string Association::GetMessage(){
    return _msg;
}
