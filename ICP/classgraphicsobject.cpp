﻿#include "classgraphicsobject.h"
#include "ClassDiagram/relation.h"

ClassGraphicsObject::ClassGraphicsObject(std::shared_ptr<MetaClass> metaclass)
    :_font(FONT), _class(metaclass), _width(DEF_WIDTH)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    CalcHeight();
    InitStrings();
    InitActions();
}

void ClassGraphicsObject::InitActions(){
    _deleteClass = new QAction(tr("Delete class"));
    connect(_deleteClass, &QAction::triggered, this, [this](){emit killSelf(this);});
    _editClass = new QAction(tr("Edit class"));
    connect(_editClass, &QAction::triggered, this, &ClassGraphicsObject::editSelf);
}

void ClassGraphicsObject::CalcHeight(){
    QFontMetrics fm(_font);

    int attr_cnt = _class->AttributesCount();
    int meth_cnt = _class->MethodCount();

    _titleHeight = 2*V_MARGIN + fm.height();
    _attrHeight  = 2*V_MARGIN + (attr_cnt-1)*V_MARGIN + attr_cnt*fm.height();
    _methHeight =  2*V_MARGIN + (meth_cnt-1)*V_MARGIN + meth_cnt*fm.height();

    _totalHeight = _titleHeight + _attrHeight + _methHeight + 4; // 4 for borders
}

void ClassGraphicsObject::InitStrings(){
    auto fm = QFontMetrics(_font);

    _attrStr.clear();
    _methStr.clear();

    _titleStr = QString(QString::fromStdString(_class->GetName()));
    if(willOverflow(_titleStr)){
        _width = fm.horizontalAdvance(_titleStr);
    }

    for(auto [name, attr]: _class->GetAttributes()){
        QString str;
        str.append(QChar(attr->GetPermission()));
        str.append(' ');
        str.append(attr->GetDataType().data());
        str.append(' ');
        str.append(name.data());

        _attrStr.push_back(str);
        if(willOverflow(str)){
            _width = fm.horizontalAdvance(str);
        }
    }

    for(auto [name, meth]: _class->GetMethods()){

        QString str;
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

        _methStr.push_back(str);
        if(willOverflow(str)){
            _width = fm.horizontalAdvance(str);
        }
    }

}

[[nodiscard]] QRectF ClassGraphicsObject::boundingRect() const{
    return {0, 0, double(_width), double(_totalHeight)};
}

void ClassGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QMenu menu;
    menu.addAction(_deleteClass);
    menu.addAction(_editClass);
    menu.exec(event->screenPos());
    event->accept();
}

bool ClassGraphicsObject::willOverflow(QString str){
    auto fm = QFontMetrics(_font);

    return fm.horizontalAdvance(str) > _width;
}

void ClassGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(isSelected()){
        painter->setPen({Qt::red, 1});
    }else{
        painter->setPen({Qt::black, 1});
    }
    painter->setFont(_font);
    QFontMetrics fm = painter->fontMetrics();

    QPainterPath classbox;
    classbox.setFillRule(Qt::WindingFill);
    painter->setBrush({WHOLEBOX_CLR});
    classbox.addRect(0, 0,  _width, _totalHeight);
    painter->drawPath(classbox);

    QPainterPath titlebox;
    titlebox.setFillRule(Qt::WindingFill);
    painter->setBrush({TITLEBOX_CLR});
    titlebox.addRect(0, 0, _width, _titleHeight+2);
    painter->drawPath(titlebox);

    painter->setPen({Qt::black, 1});

    QString str = _titleStr;

    int xPos = (_width - fm.horizontalAdvance(str)) / 2;
    int yPos = (_titleHeight/2)+round(fm.height()/2.0);

    painter->drawText(xPos, yPos, str);

    xPos = H_MARGIN;

    int attr_cnt = _class->AttributesCount();
    int divider = _attrHeight / (attr_cnt+1);

    int index = 1;
    for(auto [name, attr]: _class->GetAttributes()){

        str = _attrStr[index-1];

        yPos = _titleHeight + divider*index + round(fm.height()/2.0);
        painter->drawText(xPos, yPos, str);

        index++;
    }

    yPos = _titleHeight+_attrHeight;
    painter->drawLine(0, yPos, _width, yPos);

    int meth_cnt = _class->MethodCount();
    divider = _methHeight/(meth_cnt+1);

    index = 1;
    for(auto [name, meth]: _class->GetMethods()){

        str = _methStr[index-1];

        yPos = _titleHeight+_attrHeight+divider*index+round(fm.height()/2.0);
        painter->drawText(xPos, yPos, str);
        index++;
    }
}

MetaClass::Name ClassGraphicsObject::GetClassName(){
    return _class->GetName();
}

QPointF ClassGraphicsObject::GetItemCenter(){
    return { pos().x() + (_width/2) , pos().y() + (_totalHeight/2) };
}

void ClassGraphicsObject::editSelf(){
    ClassEditDialog dialog(_class);
    if(dialog.exec()){
        dialog.GetClassPtr();
        CalcHeight();
        InitStrings();
        prepareGeometryChange();
    }
}


