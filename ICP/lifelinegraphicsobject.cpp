#include "lifelinegraphicsobject.h"

LifelineGraphicsObject::LifelineGraphicsObject(std::shared_ptr<SequenceLifeline> lifeline)
    :_lifeline(lifeline), _font(FONT), _width(DEF_WIDTH)
{
    InitStrings();
    InitActions();
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

void LifelineGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_deleteLifeline);
    menu.exec(event->screenPos());
    event->accept();
}

void LifelineGraphicsObject::InitActions(){
    _deleteLifeline = new QAction("Delete lifeline");
    connect(_deleteLifeline, &QAction::triggered, this, &LifelineGraphicsObject::killSelfSlot);
}

void LifelineGraphicsObject::killSelfSlot(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Erasing lifeline will erase all its events!");
    msgBox.setInformativeText("Are you sure you want that?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    switch(msgBox.exec()){
        case QMessageBox::Yes:
            emit killSelf(this);
        break;

        case QMessageBox::No:
        break;
    }
}

qreal LifelineGraphicsObject::middle(){
    return x() + _width/2.0;
}

SequenceLifeline::Name LifelineGraphicsObject::GetName(){
    return _lifeline->GetName();
}
