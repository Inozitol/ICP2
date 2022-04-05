#pragma once

#include <vector>
#include <map>
#include <memory>

#include "relation.h"
#include "metaclass.h"
#include "sequencediagram.h"

///
/// \brief Singleton class holding all of back-end datastructures
///
class Environment
{
public:
    static Environment* GetEnvironment();

    void InsertClass(std::shared_ptr<MetaClass>);
    void EraseClass(MetaClass::Name);
    int InsertRelation(std::shared_ptr<Relation>);
    void EraseRelation(int);
    void InsertSequence(std::shared_ptr<SequenceDiagram>);
    void EraseSequence();

    void ExportEnvironment(std::string);
    void ImportEnvironment(std::string);

    std::shared_ptr<MetaClass> GetClass(MetaClass::Name);

protected:
    std::map<MetaClass::Name, std::shared_ptr<MetaClass>> _classes;
    std::map<int, std::shared_ptr<Relation>> _relations;
    std::shared_ptr<SequenceDiagram> _sequence;

private:
    Environment();
    static Environment* _environment;
};
