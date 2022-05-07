#pragma once

#include <string>

///
/// \brief Class for representing a generic meta class object.
///
class MetaClassObject
{
public:
    /// \brief Name of the meta class object.
    using Name = std::string;
    /// \brief Data type of the meta class object.
    using DataType = std::string;
    /// \brief Permissions of the meta class object.
    using Permission = unsigned char;

    /// \brief Class constructir.
    /// \param name name of the object.
    /// \param perm permissions of the object.
    MetaClassObject(Name name, Permission perm);

    /// \brief Method for changing permissions of the object.
    /// \param perm new object permissions.
    void ChangePerms(Permission perm);

    /// \brief Method for obtaining the permissions of the object.
    /// \return the permissions of the object.
    Permission GetPermission();
    /// \brief Method for obtaining the name of the object.
    /// \return the name of the object.
    Name GetName();

protected:
    /// \brief Name of the object.
    Name _name;
    /// \brief Permissions of the object.
    Permission _perm;
};
