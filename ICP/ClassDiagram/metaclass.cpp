#include <memory>

#include "metaclass.h"

MetaClass::MetaClass(Name name) : _name(name){}

void MetaClass::AddMethod(std::shared_ptr<MetaClassMethod> method){
    _methods.insert(std::make_pair(method->GetName(),method));
}

void MetaClass::RemoveMethod(MetaClassObject::Name name){
    _methods.erase(name);
}

void MetaClass::AddAttribute(std::shared_ptr<MetaClassAttribute> attribute){
    _attributes.insert(std::make_pair(attribute->GetName(),attribute));
}

void MetaClass::RemoveAttribute(MetaClassObject::Name name){
    _attributes.erase(name);
}

MetaClass::Name MetaClass::GetName(){
    return _name;
}

MetaClass::MethodMap MetaClass::GetMethods(){
    return _methods;
}

MetaClass::AttributeMap MetaClass::GetAttributes(){
    return _attributes;
}

int MetaClass::MethodCount(){
    return _methods.size();
}

int MetaClass::AttributesCount(){
    return _attributes.size();
}

void MetaClass::SetName(Name name){
    _name = name;
}

void MetaClass::Clear(){
    _name = "";
    _methods.clear();
    _attributes.clear();
}
