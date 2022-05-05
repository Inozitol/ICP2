#pragma once

#include "metaclass.h"
#include "relation.h"

///
/// \brief Class for the class diagram.
///
/// Class maintains all meta classes and relations between them.
///
class ClassDiagram
{
public:
    /// \brief Map, which binds the shared pointer of a class to its name.
    using MetaClassMap = std::map<MetaClass::Name, std::shared_ptr<MetaClass>>;
    /// \brief Map, which binds the shared pointer of a relation to an identification number.
    using RelationMap = std::map<int, std::shared_ptr<Relation>>;

    /// \brief Class constructor.
    ClassDiagram();

    /// \brief Method for inserting a class into the class diagram.
    /// \param metaclass shared pointer to the meta class.
    void InsertClass(std::shared_ptr<MetaClass> metaclass);
    /// \brief Method for erasing a class from the class diagram.
    /// \param name name of the class which is to be removed.
    void EraseClass(MetaClass::Name name);
    /// \brief Method for obtaining all classes within the class diagram.
    /// \return a map of all existing meta classes.
    MetaClassMap GetClasses();
    /// \brief Method for clearing all classes within the class diagram.
    void ClearClasses();
    /// \brief Method for getting a shared pointer to a class by its name.
    /// \param name name of the class.
    /// \return a shared pointer to the requested class.
    std::shared_ptr<MetaClass> GetClass(MetaClass::Name name);
    /// \brief Method for inserting a relation into the class diagram.
    /// \param relation shared pointer to the relation.
    void InsertRelation(std::shared_ptr<Relation> relation);
    /// \brief Method for removing a relation from the relation diagram.
    /// \param relation_reference identification number of the relation.
    void EraseRelation(int relation_reference);
    /// \brief Method for obtaining all relations within the class diagram.
    /// \return a map of all existing relations.
    RelationMap GetRelations();
    /// \brief Method for clearing all relations within the class diagram.
    void ClearRelations();
    /// \brief Method for clearing all relations and meta classes in the diagram.
    void Clear();
    /// \brief Will rename class inside environment
    /// \param from Rename from
    /// \param to Rename to
    void RenameClass(MetaClass::Name from, MetaClass::Name to);

private:
    /// \brief Map for meta classes.
    MetaClassMap _classes;
    /// \brief Map for relations.
    RelationMap _relations;
};

