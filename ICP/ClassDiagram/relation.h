#pragma once

#include <utility>
#include <memory>
#include <unordered_map>

#include "metaclass.h"

class Relation
{
public:
    using Cardinality = std::string;
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
    Cardinality GetSrcCardinality();
    Cardinality GetDesCardinality();
    void SetSrcCardinality(Cardinality);
    void SetDstCardinality(Cardinality);
    void SetIndex(int index);
    int GetIndex();

    static const std::unordered_map<Type, std::string> type2symb;

protected:
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> _relation;
    Type _type;
private:
    Cardinality _srcCardinality;
    Cardinality _dstCardinality;

    int _index;
};
