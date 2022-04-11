#pragma once

#include <QGraphicsObject>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>

#include "ClassDiagram/metaclass.h"

class ClassGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    ClassGraphicsObject(std::shared_ptr<MetaClass>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    const int DEF_WIDTH = 200;
    const int V_MARGIN = 2;
    const int H_MARGIN = 2;
private:
    int CalcHeight();

    QFont _font;
    std::shared_ptr<MetaClass> _class;
    int _height;
};
