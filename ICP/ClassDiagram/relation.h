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
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> GetPair();
    std::shared_ptr<MetaClass> GetSource();
    std::shared_ptr<MetaClass> GetDestination();
protected:
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> _relation;
    Type _type;
};
