// Autor: xhorac19

#pragma once

#include "metaclassobject.h"

///
/// \brief Class for representing an attribute within a meta class.
///
class MetaClassAttribute : public MetaClassObject
{
public:
    /// \brief Class constructor.
    /// \param name name of the attribute.
    /// \param perm permissions of the attribute.
    /// \param attribute data type.
    MetaClassAttribute(MetaClassObject::Name name, Permission perm, DataType type);

    /// \brief Method for obtaining the data type of an attribute.
    /// \return the data type of the attribute.
    DataType GetDataType();
protected:
    /// \brief Data type of the attribute.
    DataType _type;
};
