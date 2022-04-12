#pragma once

#include <utility>
#include <memory>

#include "metaclass.h"

class Relation
{
public:
    enum Type{
        Aggre,
        Assoc,
        Compo,
        Gener
    };

    Relation(Type,std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>);

    Type GetType();
protected:
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> _relation;
    Type _type;
};
