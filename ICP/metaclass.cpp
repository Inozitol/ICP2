#include "metaclass.h"

MetaClass::MetaClass(std::string name) : _name(name){}

void MetaClass::AddMethod(MetaClassMethod method){
    _methods.insert(std::pair<MetaClassObject::Name,MetaClassMethod>(method.GetName(),method));
}

void MetaClass::RemoveMethod(MetaClassObject::Name name){
    _methods.erase(name);
}

void MetaClass::AddAttribute(MetaClassAttribute attribute){
    _attributes.insert(std::pair<MetaClassObject::Name,MetaClassAttribute>(attribute.GetName(),attribute));
}

void MetaClass::RemoveAttribute(MetaClassObject::Name name){
    _attributes.erase(name);
}
