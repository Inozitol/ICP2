#include "classgraphicsobject.h"

ClassGraphicsObject::ClassGraphicsObject(std::shared_ptr<MetaClass> metaclass)
    :_font(FONT), _class(metaclass)
{
    CalcHeight();
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void ClassGraphicsObject::InitActions(){
    _deleteClass = new QAction(tr("Delete class"));
}

void ClassGraphicsObject::CalcHeight(){
    QFontMetrics fm(_font);

    int attr_cnt = _class->AttributesCount();
    int meth_cnt = _class->MethodCount();

    _titleHeight = 2*V_MARGIN + fm.height();
    _attrHeight  = 2*V_MARGIN + (attr_cnt-1)*V_MARGIN + attr_cnt*fm.height();
    _methHeight =  2*V_MARGIN + (meth_cnt-1)*V_MARGIN + meth_cnt*fm.height();

    _totalHeight = _titleHeight + _attrHeight + _methHeight + 4; // 4 for borders

    qDebug() << "Height: " << _totalHeight;
}

[[nodiscard]] QRectF ClassGraphicsObject::boundingRect() const{
    return {0, 0, double(DEF_WIDTH), double(_totalHeight)};
}

// TODO working context menu for items
void ClassGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_deleteClass);
    menu.exec(event->screenPos());
    event->accept();

}

void ClassGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    painter->setPen({Qt::black, 1});
    painter->setFont(_font);
    QFontMetrics fm = painter->fontMetrics();

    QPainterPath classbox;
    classbox.setFillRule(Qt::WindingFill);
    painter->setBrush({WHOLEBOX_CLR});
    classbox.addRect(0, 0,  DEF_WIDTH, _totalHeight);
    painter->drawPath(classbox);

    QPainterPath titlebox;
    titlebox.setFillRule(Qt::WindingFill);
    painter->setBrush({TITLEBOX_CLR});
    titlebox.addRect(0, 0, DEF_WIDTH, _titleHeight+2);
    painter->drawPath(titlebox);

    QString str = QString::fromStdString(_class->GetName());

    int xPos = (DEF_WIDTH - fm.horizontalAdvance(str)) / 2;
    int yPos = (_titleHeight/2)+round(fm.height()/2.0);

    painter->drawText(xPos, yPos, str);

    xPos = H_MARGIN;

    int attr_cnt = _class->AttributesCount();
    int divider = _attrHeight / (attr_cnt+1);

    int index = 1;
    for(auto [name, attr]: _class->GetAttributes()){

        str = QString();
        str.append(QChar(attr->GetPermission()));
        str.append(' ');
        str.append(attr->GetDataType().data());
        str.append(' ');
        str.append(name.data());

        yPos = _titleHeight + divider*index + round(fm.height()/2.0);
        painter->drawText(xPos, yPos, str);

        index++;
    }

    yPos = _titleHeight+_attrHeight;
    painter->drawLine(0, yPos, DEF_WIDTH, yPos);

    int meth_cnt = _class->MethodCount();
    divider = _methHeight/ (meth_cnt+1);

    index = 1;

    for(auto [name, meth]: _class->GetMethods()){

        str = QString();
        str.append(QChar(meth->GetPermission()));
        str.append(' ');
        str.append(meth->GetReturnType().data());
        str.append(' ');
        str.append(name.data());
        str.append('(');
        auto params = meth->GetParameters();
        std::set<MetaClassMethod::DataType>::iterator it;
        for(it = params.begin(); it != params.end(); it++){
            str.append((*it).data());
            if(it != std::prev(params.cend())){
                str.append(',');
            }
        }
        str.append(')');

        yPos = _titleHeight+_attrHeight+divider*index+round(fm.height()/2.0);
        painter->drawText(xPos, yPos, str);
        index++;
    }
}
