#pragma once

#include <string>
#include <vector>
#include <set>

#include "metaclassobject.h"
#include "metaclassattribute.h"

class MetaClassMethod : public MetaClassObject
{
public:

    MetaClassMethod(Name, Permission);

    void AddParameter(DataType);
    void RemoveParameter(DataType);
    void ChangeReturnType(DataType);

    DataType GetReturnType();

    std::set<DataType> GetParameters();

protected:
    DataType _return_type;
    std::set<DataType> _parameters;
};
