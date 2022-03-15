#pragma once

#include <string>

class MetaClassObject
{
public:
    using Name = std::string;

    MetaClassObject(Name);
    Name GetName();

protected:
    Name _name;
};
