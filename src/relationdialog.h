#pragma once

#include <QDialog>
#include <QComboBox>

#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"
#include "ClassDiagram/association.h"
#include "ClassDiagram/aggregation.h"
#include "ClassDiagram/composition.h"
#include "ClassDiagram/generalization.h"

#include "utils.h"

namespace Ui {
class RelationDialog;
}

///
/// \brief Class representing dialogs for creating relations.
///
class RelationDialog : public QDialog
{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param pair Pair of two graphic objects, which is to be linked.
    /// \param parent pointer to the parent widget.
    RelationDialog(std::pair<ClassGraphicsObject* , ClassGraphicsObject*> pair, QWidget* parent = nullptr);
    /// \brief Class destructor.
    ~RelationDialog();
    /// \brief Method for obtaining the shared pointer to the relation.
    /// \return shared pointer to the relation.
    std::shared_ptr<Relation> GetRelation();

private:
    /// \brief Method for initializing object names in the relation creation dialog.
    void InitNames();
    /// \brief Method for initializing options in the combobox in the relation creation dialog.
    void InitCombo();

    /// \brief UI of the relation creation dialog.
    Ui::RelationDialog *ui;
    /// \brief Pair of linked graphic objects.
    std::pair<ClassGraphicsObject*, ClassGraphicsObject*> _pair;
    /// \brief Shared pointer to the relation.
    std::shared_ptr<Relation> _relation;
    /// \brief Qt list of comboxbox options.
    QList<QPair<Relation::Type,QString>> _comboText = {
        {Relation::Assoc, "Association"},
        {Relation::Aggre, "Aggregation"},
        {Relation::Compo, "Composition"},
        {Relation::Gener, "Generalization"}
    };
private slots:
    /// \brief Slot for combo box being changed
    /// \param ID of currently active type
    void comboBoxChanged(int type);
};
