#include "metaclassobject.h"

MetaClassObject::MetaClassObject(Name name, Permission perm)
    : _name(name), _perm(perm){}

MetaClassObject::Name MetaClassObject::GetName(){
    return _name;
}

MetaClassObject::Permission MetaClassObject::GetPermission(){
    return _perm;
}

void MetaClassObject::ChangePerms(Permission perm){
    _perm = perm;
}
