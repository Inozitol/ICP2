#pragma once

#define WHOLEBOX_CLR "#BFBFBF"
#define TITLEBOX_CLR "#DFC6AE"
#define FONT "Arial"

#include <QGraphicsObject>
#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>

#include <cmath>

#include "SequenceDiagram/sequencelifeline.h"

///
/// \brief Class representing the graphic objects for lifelines.
///
class LifelineGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    /// \brief Class constructor.
    /// \param lifeline shared pointer to the lifeline.
    LifelineGraphicsObject(std::shared_ptr<SequenceLifeline> lifeline);
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
    /// \brief Method for obtaining the x-axis middle of the object.
    /// \return x coordinate of the middle.
    qreal middle();
    /// \brief Method for initializing actions within the class graphic object.
    void InitActions();
    /// \brief Method for obtaining the name of the lifeline.
    /// \return the name of the lifeline.
    SequenceLifeline::Name GetName();
    /// \brief Method for obtaining the height of the graphic object.
    /// \return the height.
    static qreal height();
    /// \brief Method for getting pointer to the lifeline
    std::shared_ptr<SequenceLifeline> GetLifeline();

private:
    /// \brief Default class graphic object width.
    static const int DEF_WIDTH = 75;
    /// \brief Class graphic object vertical margin.
    static const int V_MARGIN = 2;
    /// \brief Class graphic object horizontal margin.
    static const int H_MARGIN = 2;

    /// \brief Method for initializing strings within the lifeline graphic objects and overwriting default width.
    void InitStrings();
    /// \brief method for calculating heights of graphic objects.
    void CalcHeight();
    /// \brief Method for determining whether text on the graphic object will flow over the current width.
    /// \return bool, determining overflow.
    inline bool willOverflow(QString);
    /// \brief Method for displaying a warning when deleting a lifeline.
    /// \return confirmation.
    bool deleteWarn();

    /// \brief Shared pointer to the lifeline, displayed in the graphic object.
    std::shared_ptr<SequenceLifeline> _lifeline;

    /// \brief Font of the text in the graphic objects.
    QFont _font;
    /// \brief Action for deleting a lifeline.
    QAction* _deleteLifeline;
    /// \brief Action for editing a lifeline.
    QAction* _editLifeline;

    /// \brief Lifeline name.
    QString _lifelineName;
    /// \brief Lifeline class name.
    QString _className;
    /// \brief Graphic object total width.
    int _width;
    /// \brief Graphic object total height.
    int _height;

signals:
    /// \brief Signal for making a graphic object delete itself.
    void killSelf(LifelineGraphicsObject*);

    /// \brief Signal for starting an editing proces for lifeline.
    void edit(LifelineGraphicsObject*);
};
