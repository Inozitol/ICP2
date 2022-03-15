#include "metaclassobject.h"

MetaClassObject::MetaClassObject(MetaClassObject::Name name) : _name(name){}

MetaClassObject::Name MetaClassObject::GetName(){
    return _name;
}
