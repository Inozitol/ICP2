#pragma once

#include <vector>
#include <map>
#include <memory>

#include "relation.h"
#include "metaclass.h"

class Environment
{
public:
    static Environment* GetEnvironment();

    void InsertClass(std::shared_ptr<MetaClass>);
    void EraseClass(MetaClass::Name);
    int InsertRelation(std::shared_ptr<Relation>);
    void EraseRelation(int);

    void ExportEnvironment(std::string);

protected:
    std::map<MetaClass::Name, std::shared_ptr<MetaClass>> _classes;
    std::map<int, std::shared_ptr<Relation>> _relations;

private:
    Environment();
    static Environment* _environment;
};
