#include "lifelinegraphicsobject.h"

LifelineGraphicsObject::LifelineGraphicsObject(std::shared_ptr<SequenceLifeline> lifeline)
    :_lifeline(lifeline), _font(FONT), _width(DEF_WIDTH)
{
    InitStrings();
    CalcHeight();
}

void LifelineGraphicsObject::InitStrings(){
    auto fm = QFontMetrics(_font);

    _lifelineName = QString(QString::fromStdString(_lifeline->GetName()));
    if(willOverflow(_lifelineName)){
        _width = fm.horizontalAdvance(_lifelineName);
    }

    _className = QString(QString::fromStdString(_lifeline->GetClass()->GetName())).prepend('<').append('>');
    if(willOverflow(_className)){
        _width = fm.horizontalAdvance(_className);
    }
}

void LifelineGraphicsObject::CalcHeight(){
    auto fm = QFontMetrics(_font);

    _height = 3*V_MARGIN + 2*fm.height() + 2;	// 2 for borders
}

qreal LifelineGraphicsObject::height(){
    auto fm = QFontMetrics(QFont(FONT));
    return 3*V_MARGIN + 2*fm.height() + 2;
}

bool LifelineGraphicsObject::willOverflow(QString str){
    auto fm = QFontMetrics(_font);

    return fm.horizontalAdvance(str) > _width;
}

[[nodiscard]] QRectF LifelineGraphicsObject::boundingRect() const{
    return {0, 0, double(_width), double(_height)};
}

void LifelineGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    painter->setFont(_font);
    QFontMetrics fm = painter->fontMetrics();

    QPainterPath lifelinebox;
    lifelinebox.setFillRule(Qt::WindingFill);
    painter->setBrush({WHOLEBOX_CLR});
    lifelinebox.addRect(0, 0,  _width, _height);
    painter->drawPath(lifelinebox);

    int xPos = (_width - fm.horizontalAdvance(_lifelineName)) / 2;
    int yPos = V_MARGIN + round(fm.height());
    painter->drawText(xPos, yPos, _lifelineName);

    xPos = (_width - fm.horizontalAdvance(_className)) / 2;
    yPos = 2*V_MARGIN + 2*round(fm.height());
    painter->drawText(xPos, yPos, _className);
}

qreal LifelineGraphicsObject::middle(){
    return x() + _width/2.0;
}
