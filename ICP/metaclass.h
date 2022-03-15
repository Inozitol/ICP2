#pragma once

#include <string>
#include <vector>
#include <map>

#include "metaclassmethod.h"
#include "metaclassattribute.h"

class MetaClass{
public:
    using Name = std::string;

    MetaClass(Name);

    void AddMethod(MetaClassMethod);
    void RemoveMethod(MetaClassObject::Name);
    void AddAttribute(MetaClassAttribute);
    void RemoveAttribute(MetaClassObject::Name);

    Name GetName();

protected:
    Name _name;
    std::map<MetaClassObject::Name, MetaClassMethod> _methods;
    std::map<MetaClassObject::Name, MetaClassAttribute> _attributes;
};
