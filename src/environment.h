#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>

#include "ClassDiagram/classdiagram.h"
#include "SequenceDiagram/sequencediagram.h"
#include "ClassDiagram/relation.h"
#include "ClassDiagram/metaclass.h"
#include "ClassDiagram/association.h"
#include "ClassDiagram/aggregation.h"
#include "ClassDiagram/composition.h"
#include "ClassDiagram/generalization.h"

class invalid_file : public std::exception{
public:
    invalid_file(const std::string& msg) : _msg(msg){}
    ~invalid_file(){}

    const std::string& get_msg() const {return _msg;}
private:
    const std::string _msg;
};

///
/// \brief Singleton class holding all of backend datastructures.
///
class Environment
{
public:
    /// \brief Class instance provider (singleton constructor).
    /// \return an instance of the environment.
    static Environment* GetEnvironment();

    /// \brief Method for obtaining the shared pointer to the class diagram.
    /// \return shared pointer to the class diagram.
    std::shared_ptr<ClassDiagram> GetClassDiagram();
    /// \brief Method for obtaining the shared pointer to the sequence diagram.
    /// \return shared pointer to the sequence diagram.
    std::shared_ptr<SequenceDiagram> GetSequenceDiagram();

    /// \brief Method for serializing, saving and exporting the opened environment.
    /// \param file_name name of the file, into which the environment will be saved.
    void ExportEnvironment(std::string file_name);
    /// \brief Method for deserializing, loading and importing an environment.
    /// \param file_name name of the file, from which the environment will be loaded.
    void ImportEnvironment(std::string file_name);
    /// \brief Method for checking the semantics of events in the sequence diagram.
    void CheckSequenceEvents();

private:
    /// \brief Shared pointer to the class diagram.
    std::shared_ptr<ClassDiagram> _class_diag;
    /// \brief Shared pointer to the sequence diagram.
    std::shared_ptr<SequenceDiagram> _sequence_diag;

    /// \brief Class constructor.
    Environment();
    /// \brief Singleton environment variable.
    static Environment* _environment;
};
