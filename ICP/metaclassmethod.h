#pragma once

#include <string>
#include <vector>
#include <set>

#include "metaclassobject.h"
#include "metaclassattribute.h"

class MetaClassMethod : public MetaClassObject
{
public:
    using Parameter = std::string;
    using DataType = std::string;

    MetaClassMethod(Name);

    void AddParameter(Parameter);
    void RemoveParameter(Parameter);
    void AddReturnType(DataType);
    void RemoveReturnType();

protected:
    DataType _return_type;
    std::set<Parameter> _parameters;
};
