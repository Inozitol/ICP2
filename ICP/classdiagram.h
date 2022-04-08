#pragma once

#include "metaclass.h"
#include "relation.h"

class ClassDiagram
{
public:
    using MetaClassMap = std::map<MetaClass::Name, std::shared_ptr<MetaClass>>;
    using RelationMap = std::map<int, std::shared_ptr<Relation>>;

    ClassDiagram();

    void InsertClass(std::shared_ptr<MetaClass>);
    void EraseClass(MetaClass::Name);
    MetaClassMap GetClasses();
    void ClearClasses();
    std::shared_ptr<MetaClass> GetClass(MetaClass::Name);

    int InsertRelation(std::shared_ptr<Relation>);
    void EraseRelation(int);
    RelationMap GetRelations();
    void ClearRelations();

    void Clear();

private:
    MetaClassMap _classes;
    RelationMap _relations;
};

