#include "metaclassattribute.h"

MetaClassAttribute::MetaClassAttribute(MetaClassObject::Name name, Permission perm) : MetaClassObject(name){
    _perm = perm;
}

void MetaClassAttribute::ChangePerms(Permission perm){
    _perm = perm;
}
