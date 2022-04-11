#pragma once

#include <vector>
#include <map>
#include <memory>

#include "ClassDiagram/classdiagram.h"
#include "SequenceDiagram/sequencediagram.h"
#include "ClassDiagram/relation.h"
#include "ClassDiagram/metaclass.h"

///
/// \brief Singleton class holding all of back-end datastructures
///
class Environment
{
public:
    static Environment* GetEnvironment();

    void InsertClass(std::shared_ptr<ClassDiagram>);
    void EraseClass();
    std::shared_ptr<ClassDiagram> GetClass();

    void InsertSequence(std::shared_ptr<SequenceDiagram>);
    void EraseSequence();
    std::shared_ptr<SequenceDiagram> GetSequence();

    void ExportEnvironment(std::string);
    void ImportEnvironment(std::string);

private:
    std::shared_ptr<ClassDiagram> _class_diag;
    std::shared_ptr<SequenceDiagram> _sequence_diag;

    Environment();
    static Environment* _environment;
};
