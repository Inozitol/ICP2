#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "metaclassmethod.h"
#include "metaclassattribute.h"

///
/// \brief Class for representing a meta class.
///
/// Class maintains all meta class information.
///
class MetaClass{
public:
    /// \brief Name of the meta class.
    using Name = std::string;
    /// \brief Map, which binds the shared pointer of a method to its meta class method name.
    using MethodMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassMethod>>;
    /// \brief Map, which binds the shared pointer of an attribute to its meta class attribute name.
    using AttributeMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassAttribute>>;

    /// \brief Class constructor.
    /// \param name name of the meta class.
    MetaClass(Name name);

    /// \brief Method for setting the name of the meta class.
    /// \param name new name of the meta class.
    void SetName(Name name);

    /// \brief Method for adding a method to the meta class.
    /// \param method shared pointer to the new method.
    void AddMethod(std::shared_ptr<MetaClassMethod> method);
    /// \brief Method for removing a method from the meta class.
    /// \param name name of the method, which is to be removed.
    void RemoveMethod(MetaClassObject::Name name);
    /// \brief Method for adding an attribute to the meta class.
    /// \param attribute shared pointer to the new attribute.
    void AddAttribute(std::shared_ptr<MetaClassAttribute> attribute);
    /// \brief Method for removing an attribute from the meta class.
    /// \param name name of the attribute, which is to be removed.
    void RemoveAttribute(MetaClassObject::Name name);

    /// \brief Method for obtaining all methods within the meta class.
    /// \return a map of all methods.
    MethodMap GetMethods();
    /// \brief Method for obtaining all attributes within the meta class.
    /// \return a map of all attributes.
    AttributeMap GetAttributes();

    /// \brief Method for obtaining the name of the meta class.
    /// \return the name of the meta class.
    Name GetName();

    /// \brief Method for obtaining the amount of methods in the meta class.
    /// \return the amount of methods.
    int MethodCount();
    /// \brief Method for obtaining the amount of attributes in the meta class.
    /// \return the amount of attributes.
    int AttributesCount();

    /// \brief Method for clearing all data in the meta class.
    void Clear();

protected:
    /// \brief Name of the meta class.
    Name _name;
    /// \brief Map of all the methods.
    MethodMap _methods;
    /// \brief Map of all the attributes.
    AttributeMap _attributes;
};
