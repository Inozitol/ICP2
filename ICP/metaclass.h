#pragma once

#include <string>
#include <vector>
#include <map>

#include "metaclassmethod.h"
#include "metaclassattribute.h"

class MetaClass{
public:
    MetaClass(std::string);

    void AddMethod(MetaClassMethod);
    void RemoveMethod(MetaClassObject::Name);
    void AddAttribute(MetaClassAttribute);
    void RemoveAttribute(MetaClassObject::Name);

protected:
    std::string _name;
    std::map<MetaClassObject::Name, MetaClassMethod> _methods;
    std::map<MetaClassObject::Name, MetaClassAttribute> _attributes;
};
