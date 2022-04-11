#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "metaclassmethod.h"
#include "metaclassattribute.h"

class MetaClass{
public:
    using Name = std::string;
    using MethodMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassMethod>>;
    using AttributeMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassAttribute>>;

    MetaClass(Name);

    void AddMethod(std::shared_ptr<MetaClassMethod>);
    void RemoveMethod(MetaClassObject::Name);
    void AddAttribute(std::shared_ptr<MetaClassAttribute>);
    void RemoveAttribute(MetaClassObject::Name);

    MethodMap GetMethods();
    AttributeMap GetAttributes();

    Name GetName();

protected:
    Name _name;
    MethodMap _methods;
    AttributeMap _attributes;
};
