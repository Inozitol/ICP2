#pragma once

#include <utility>
#include <memory>
#include <unordered_map>

#include "metaclass.h"

///
/// \brief Class for representing a relation between meta classes.
///
/// Class maintains origin, destination, cardinality and type of a relation.
///
class Relation
{
public:
    /// \brief Representation of the cardinality of a relation.
    using Cardinality = std::string;
    /// \brief Enumeration for the different types of relations.
    enum Type{
        Aggre,
        Assoc,
        Compo,
        Gener
    };

    /// \brief Class constructor.
    /// \param type type of relation.
    /// \param class1 origin of the relation.
    /// \param class2 destination of the relation.
    Relation(Type type, std::shared_ptr<MetaClass> class1, std::shared_ptr<MetaClass> class2);

    /// \brief Method for obtaining the type of a relation.
    /// \return type of relation.
    Type GetType();
    /// \brief Method for obtaining the origin and the destination of the relation.
    /// \return a pair of meta classes.
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> GetPair();
    /// \brief Method for obtaining the source of the relation.
    /// \return the metaclass, which is the origin of the relation.
    std::shared_ptr<MetaClass> GetSource();
    /// \brief Method for obtaining the destination of the relation.
    /// \return the metaclass, which is the destination of the relation.
    std::shared_ptr<MetaClass> GetDestination();
    /// \brief Method for obtaining source cardinality.
    /// \return the cardinality on the source side of the relation.
    Cardinality GetSrcCardinality();
    /// \brief Method for obtaining destination cardinality.
    /// \return the cardinality on the destination side of the relation.
    Cardinality GetDstCardinality();
    /// \brief Method for setting the cardinality on the source side of the relation
    /// \param crd Source side cardinality.
    void SetSrcCardinality(Cardinality crd);
    /// \brief Method for setting the cardinality on the destination side of the relation
    /// \param crd Destination side cardinality.
    void SetDstCardinality(Cardinality crd);
    /// \brief Method for setting the index of the relation.
    /// \param index The new index.
    void SetIndex(int index);
    /// \brief Method for obtaining the index of the relation.
    /// \return the index of the relation.
    int GetIndex();

    /// \brief Map for translating relation symbols into relation types.
    static const std::unordered_map<Type, std::string> type2symb;

protected:
    /// \brief Meta class pair, consisting of the origin and destination.
    std::pair<std::shared_ptr<MetaClass>, std::shared_ptr<MetaClass>> _relation;
    /// \brief Type of the relation.
    Type _type;
private:
    /// \brief Source side cardinality.
    Cardinality _srcCardinality;
    /// \brief Destination side cardinality.
    Cardinality _dstCardinality;
    /// \brief Index of the relation
    int _index;
};
