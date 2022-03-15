#pragma once

#include <vector>
#include <map>

#include "relation.h"
#include "metaclass.h"

class Environment
{
public:
    Environment* GetEnvironment();
    ~Environment();

    void InsertClass(MetaClass*);
    void EraseClass(MetaClass::Name);
    int InsertRelation(Relation*);
    void EraseRelation(int);

protected:
    std::map<MetaClass::Name, MetaClass*> _classes;
    std::map<int, Relation*> _relations;

private:
    Environment();
    static Environment* _environment;
};
