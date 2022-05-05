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

///
/// \brief Singleton class holding all of back-end datastructures
///
class Environment
{
public:
    static Environment* GetEnvironment();

    void InsertClassDiagram(std::shared_ptr<ClassDiagram>);
    void EraseClassDiagram();
    std::shared_ptr<ClassDiagram> GetClassDiagram();

    void InsertSequenceDiagram(std::shared_ptr<SequenceDiagram>);
    void EraseSequenceDiagram();
    std::shared_ptr<SequenceDiagram> GetSequenceDiagram();

    void ExportEnvironment(std::string);
    void ImportEnvironment(std::string);

    void CheckSequenceEvents();

private:
    std::shared_ptr<ClassDiagram> _class_diag;
    std::shared_ptr<SequenceDiagram> _sequence_diag;

    Environment();
    static Environment* _environment;
};
