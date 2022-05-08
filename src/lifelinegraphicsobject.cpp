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
#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
        _width = fm.width(_lifelineName);
#else
        _width = fm.horizontalAdvance(_lifelineName);
#endif
    }

    _className = QString(QString::fromStdString(_lifeline->GetClass()->GetName())).prepend('<').append('>');
    if(willOverflow(_className)){
#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
        _width = fm.width(_className);
#else
        _width = fm.horizontalAdvance(_className);
#endif
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

#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
    return fm.width(str) > _width;
#else
    return fm.horizontalAdvance(str) > _width;
#endif
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

#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
    int xPos = (_width - fm.width(_lifelineName)) / 2;
#else
    int xPos = (_width - fm.horizontalAdvance(_lifelineName)) / 2;
#endif
    int yPos = V_MARGIN + round(fm.height());
    painter->drawText(xPos, yPos, _lifelineName);

#if QT_VERSION < QT_VERSION_CHECK(5, 11, 0)
    xPos = (_width - fm.width(_className)) / 2;
#else
    xPos = (_width - fm.horizontalAdvance(_className)) / 2;
#endif
    yPos = 2*V_MARGIN + 2*round(fm.height());
    painter->drawText(xPos, yPos, _className);
}

void LifelineGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_editLifeline);
    menu.addAction(_deleteLifeline);
    menu.exec(event->screenPos());
    event->accept();
}

void LifelineGraphicsObject::InitActions(){
    _deleteLifeline = new QAction("Delete lifeline");
    connect(_deleteLifeline, &QAction::triggered, this, [this](){if(deleteWarn()){ emit killSelf(this); }});
    _editLifeline = new QAction("Edit lifeline");
    connect(_editLifeline, &QAction::triggered, this, [this](){emit edit(this);});
}

bool LifelineGraphicsObject::deleteWarn(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Erasing lifeline will erase all its events!");
    msgBox.setInformativeText("Are you sure you want that?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    switch(msgBox.exec()){
        case QMessageBox::Yes:
            return true;
        break;

        case QMessageBox::No:
            return false;
        break;
    }

    return false;
}

qreal LifelineGraphicsObject::middle(){
    return x() + _width/2.0;
}

SequenceLifeline::Name LifelineGraphicsObject::GetName(){
    return _lifeline->GetName();
}

std::shared_ptr<SequenceLifeline> LifelineGraphicsObject::GetLifeline(){
    return _lifeline;
}
