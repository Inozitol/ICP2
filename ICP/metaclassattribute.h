#pragma once

#include "metaclassobject.h"

class MetaClassAttribute : public MetaClassObject
{
public:
    using Permission = unsigned char;

    MetaClassAttribute(MetaClassObject::Name, Permission);

    void ChangePerms(Permission);
protected:
    Permission _perm;
};
