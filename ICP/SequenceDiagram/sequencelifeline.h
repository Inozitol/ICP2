#pragma once

#include <string>
#include <memory>

#include "../ClassDiagram/metaclass.h"

class SequenceLifeline
{
public:
    using Name = std::string;

    SequenceLifeline(Name, std::shared_ptr<MetaClass>);

    void ChangeName(Name);
    Name GetName();
    void ChangeClass(std::shared_ptr<MetaClass>);
    std::shared_ptr<MetaClass> GetClass();
private:
    Name _name;
    std::shared_ptr<MetaClass> _class;
};
