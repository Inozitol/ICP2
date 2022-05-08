// Autor: xhorac19

#pragma once

#include <string>
#include <vector>
#include <set>

#include "metaclassobject.h"
#include "metaclassattribute.h"

///
/// \brief Class for representing a method within a meta class.
///
class MetaClassMethod : public MetaClassObject
{
public:
    /// \brief Class constructor without return type specification.
    /// \param name name of the method.
    /// \param perm permissions of the method.
    MetaClassMethod(Name name, Permission perm);
    /// \brief Class constructor with return type specification.
    /// \param name name of the method.
    /// \param perm permissions of the method.
    /// \param return_type return type of the method.
    MetaClassMethod(Name name, Permission perm, DataType return_type);

    /// \brief Method for adding a new parameter to a method.
    /// \param param name of the new parameter.
    void AddParameter(DataType param);
    /// \brief Method for removing a parameter from a method.
    /// \param param name of the parameter, which is to be removed.
    void RemoveParameter(DataType param);
    /// \brief Method for changing the return type of a method.
    /// \param type new return type of the method.
    void ChangeReturnType(DataType type);
    /// \brief Method for obtaining the return type of a method.
    /// \return the return type of the method.
    DataType GetReturnType();
    /// \brief Method for obtaining all parameters of a method.
    /// \return a set of all parameters.
    std::set<DataType> GetParameters();

protected:
    /// \brief Return type of the method.
    DataType _return_type;
    /// \brief Set of method parameters.
    std::set<DataType> _parameters;
};
