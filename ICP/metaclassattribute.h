#pragma once

#include "metaclassobject.h"

class MetaClassAttribute : public MetaClassObject
{
public:

    MetaClassAttribute(MetaClassObject::Name, Permission, DataType);
    DataType GetDataType();
protected:
    DataType _type;
};
