#pragma once

#include <QPointF>

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "metaclassmethod.h"
#include "metaclassattribute.h"

class MetaClass{
public:
    using Name = std::string;
    using MethodMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassMethod>>;
    using AttributeMap = std::map<MetaClassObject::Name, std::shared_ptr<MetaClassAttribute>>;

    MetaClass(Name);

    void SetName(Name);

    void AddMethod(std::shared_ptr<MetaClassMethod>);
    void RemoveMethod(MetaClassObject::Name);
    void AddAttribute(std::shared_ptr<MetaClassAttribute>);
    void RemoveAttribute(MetaClassObject::Name);

    MethodMap GetMethods();
    AttributeMap GetAttributes();

    int MethodCount();
    int AttributesCount();

    Name GetName();

    void Clear();

    /// \brief Get position of Class in scene
    /// \return Position
    QPoint GetPos();
    /// \brief Set position for drawing later
    /// \param pos Position
    void SetPos(QPoint pos);

protected:
    Name _name;
    MethodMap _methods;
    AttributeMap _attributes;

    /// \brief Position of the class in scene
    QPoint _pos;
};
