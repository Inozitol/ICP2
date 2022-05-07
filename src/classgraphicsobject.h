#pragma once

#define WHOLEBOX_CLR "#BFBFBF"
#define TITLEBOX_CLR "#DFC6AE"
#define FONT "Arial"

#include <QGraphicsObject>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QtGlobal>

#include <cmath>

#include "ClassDiagram/metaclass.h"
#include "newclassform.h"

///
/// \brief Class representing the class graphic object.
///
class ClassGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param metaclass shared pointer to the meta class of the graphic object.
    ClassGraphicsObject(std::shared_ptr<MetaClass> metaclass);
    /// \brief Redefined method for obtaining a rectangle within which the graphic object is.
    /// \return the rectangle.
    [[nodiscard]] QRectF boundingRect() const override;
    /// \brief Redefined Qt method for painting graphic objects onto the scene.
    /// \param painter Qt painter.
    /// \param option Qt paint options - not used.
    /// \param widget Qt paint widget - not used.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    /// \brief Redefined method defining context menu event behaviour.
    /// \param event event for the context menu in the graphic object.
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    /// \brief Method for obtaining the name of the class graphic object.
    /// \return name of the class.
    MetaClass::Name GetClassName();
    /// \brief Method for obtaining the coordinates of the center of the graphic object.
    /// \return coordinates of the center.
    QPointF GetItemCenter();
    /// \brief Method for obtaining the shared pointer to the class of the object.
    /// \return shared pointer to the class.
    std::shared_ptr<MetaClass> GetClass();

private:
    /// \brief Default class graphic object width.
    const int DEF_WIDTH = 200;
    /// \brief Class graphic object vertical margin.
    const int V_MARGIN = 2;
    /// \brief Class graphic object horizontal margin.
    const int H_MARGIN = 2;

    /// \brief method for calculating heights of graphic objects.
    void CalcHeight();
    /// \brief Method for initializing strings within the class graphic objects and overwriting default width.
    void InitStrings();
    /// \brief Method for initializing actions within the class graphic object.
    void InitActions();
    /// \brief Method for determining whether text on the graphic object will flow over the current width.
    /// \return bool, determining overflow.
    inline bool willOverflow(QString);

    /// \brief Font of the text in the graphic objects.
    QFont _font;
    /// \brief Shared pointer to the meta class.
    std::shared_ptr<MetaClass> _class;
    /// \brief Total height of the graphic object.
    int _totalHeight;
    /// \brief Total height of the title in the graphic object.
    int _titleHeight;
    /// \brief Total height of the attribute part of the graphic object.
    int _attrHeight;
    /// \brief Total height of the method part of the graphic object.
    int _methHeight;
    /// \brief Total width of the graphic object.
    int _width;
    /// \brief The title of the graphic object.
    QString _titleStr;
    /// \brief Vector of attributes.
    std::vector<QString> _attrStr;
    /// \brief Vector of methods.
    std::vector<QString> _methStr;

    /// \brief Action for deleting a class.
    QAction* _deleteClass;
    /// \brief Action for editing a class.
    QAction* _editClass;
    /// \brief Action for initializing a relation creation process.
    QAction* _createRelation;
public slots:
    /// \brief Slot for synchronizing positions of classes within the scene with backend.
    void SyncClassPos();

private slots:
    /// \brief Slot for starting a dialog for class editing.
    void editSelf();

signals:
    /// \brief Signal for making a graphic object delete itself.
    void killSelf(ClassGraphicsObject* item);
    /// \brief Signal for initializing a relation.
    void initRelation(ClassGraphicsObject* item);
    /// \brief Signaled called when class got changed.
    void changed();
};
