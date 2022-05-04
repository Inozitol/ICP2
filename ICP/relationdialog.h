#pragma once

#include <QDialog>

#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"
#include "ClassDiagram/association.h"
#include "ClassDiagram/aggregation.h"
#include "ClassDiagram/composition.h"
#include "ClassDiagram/generalization.h"

namespace Ui {
class RelationDialog;
}

class RelationDialog : public QDialog
{
    Q_OBJECT

public:
    RelationDialog(std::pair<ClassGraphicsObject*, ClassGraphicsObject*>, QWidget* parent = nullptr);
    ~RelationDialog();
    std::shared_ptr<Relation> GetRelation();

private:
    void InitNames();
    void InitCombo();

    Ui::RelationDialog *ui;
    std::pair<ClassGraphicsObject*, ClassGraphicsObject*> _pair;
    std::shared_ptr<Relation> _relation;
    QList<QPair<Relation::Type,QString>> _comboText = {
        {Relation::Assoc, "Association"},
        {Relation::Aggre, "Aggregation"},
        {Relation::Compo, "Composition"},
        {Relation::Gener, "Generalization"}
    };
};
