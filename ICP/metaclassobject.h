#pragma once

#include <string>

class MetaClassObject
{
public:
    using Name = std::string;
    using DataType = std::string;
    using Permission = unsigned char;

    MetaClassObject(Name, Permission);
    void ChangePerms(Permission);

    Permission GetPermission();
    Name GetName();

protected:
    Name _name;
    Permission _perm;
};
