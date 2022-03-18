#include "metaclassattribute.h"

MetaClassAttribute::MetaClassAttribute(MetaClassObject::Name name, Permission perm, DataType type)
    : MetaClassObject(name, perm), _type(type){}

MetaClassObject::DataType MetaClassAttribute::GetDataType(){
    return _type;
}
