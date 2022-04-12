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

#include "ClassDiagram/metaclass.h"

class ClassGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    ClassGraphicsObject(std::shared_ptr<MetaClass>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    const int DEF_WIDTH = 200;
    const int V_MARGIN = 2;
    const int H_MARGIN = 2;
private:
    void CalcHeight();
    void InitActions();

    QFont _font;
    std::shared_ptr<MetaClass> _class;
    int _totalHeight;
    int _titleHeight;
    int _attrHeight;
    int _methHeight;

    QAction* _deleteClass;
};
