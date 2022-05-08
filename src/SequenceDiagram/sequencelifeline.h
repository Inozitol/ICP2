// Autor: xhorac19

#pragma once

#include <string>
#include <memory>

#include "../ClassDiagram/metaclass.h"

///
/// \brief Class for representing a lifeline in the sequence diagram.
///
/// Class maintains all lifeline information.
///
class SequenceLifeline
{
public:
    /// \brief Name of the lifeline.
    using Name = std::string;

    /// \brief Class constructor.
    /// \param name name of the lifeline.
    /// \param metaclass shared pointer to the meta class of the lifeline.
    SequenceLifeline(Name name, std::shared_ptr<MetaClass> metaclass);

    /// \brief Method for changing the name of the lifeline.
    /// \param name new name of the lifeline.
    void ChangeName(Name name);
    /// \brief Method for obtaining the name of the lifeline.
    /// \return the name of the lifeline.
    Name GetName();
    /// \brief Method for changing the meta class of the lifeline.
    /// \param metaclass new meta class of the lifeline.
    void ChangeClass(std::shared_ptr<MetaClass> metaclass);
    /// \brief Method for obtaining the meta class of the lifeline.
    /// \return shared pointer to the meta class of the lifeline.
    std::shared_ptr<MetaClass> GetClass();
private:
    /// \brief Name of the lifeline.
    Name _name;
    /// \brief Meta class of the lifeline.
    std::shared_ptr<MetaClass> _class;
};
