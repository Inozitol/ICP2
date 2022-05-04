#pragma once

#include "metaclass.h"
#include "relation.h"

///
/// \brief Class for the class diagram.
///
///  Class maintains all meta classes and relations between them.
///
class ClassDiagram
{
public:
    using MetaClassMap = std::map<MetaClass::Name, std::shared_ptr<MetaClass>>;
    using RelationMap = std::map<int, std::shared_ptr<Relation>>;

    /// \brief Class diagram class constructor.
    ClassDiagram();

    /// \brief Method for inserting a class into the class diagram.
    /// \param metaclass shared pointer to the meta class.
    void InsertClass(std::shared_ptr<MetaClass>);
    /// \brief Method for erasing a class from the class diagram.
    /// \param name name of the class which is to be removed.
    void EraseClass(MetaClass::Name);
    /// \brief Method for obtaining all classes within the class diagram.
    MetaClassMap GetClasses();
    /// \brief Method for clearing all classes within the class diagram.
    void ClearClasses();
    /// \brief Method for getting a shared pointer to a class by name.
    /// \param name name of the class.
    std::shared_ptr<MetaClass> GetClass(MetaClass::Name);

    /// \brief Method for getting a shared pointer to a class by name.
    /// \param name name of the class.
    int InsertRelation(std::shared_ptr<Relation>);
    void EraseRelation(int);
    RelationMap GetRelations();
    void ClearRelations();

    void Clear();

private:
    MetaClassMap _classes;
    RelationMap _relations;
};

