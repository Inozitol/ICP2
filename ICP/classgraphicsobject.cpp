#include "classgraphicsobject.h"

ClassGraphicsObject::ClassGraphicsObject(std::shared_ptr<MetaClass> metaclass)
    :_font("Courier New"), _class(metaclass), _height(CalcHeight())
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

int ClassGraphicsObject::CalcHeight(){
    int height = 0;
    QFontMetrics fm(_font);
    height += V_MARGIN;
    height += fm.height();						// Title
    height += V_MARGIN;
    for(auto attr : _class->GetAttributes()){
        height += fm.height();					// Attributes
        height += V_MARGIN;
        qDebug() << "Attribute: " << attr.first.data();
    }
    for(auto meth : _class->GetMethods()){
        height += fm.height();					// Methods
        height += V_MARGIN;
        qDebug() << "Method: " << meth.first.data();
    }
    qDebug() << height;
    return height;
}

[[nodiscard]] QRectF ClassGraphicsObject::boundingRect() const{
    return {0, 0, double(DEF_WIDTH), double(_height)};
}

void ClassGraphicsObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget){
    QPainterPath title;
    title.setFillRule(Qt::WindingFill);
    painter->setBrush({"#E0E0E0"});
    title.addRect(0, 0,  DEF_WIDTH, _height);
    painter->drawPath(title);

    painter->setFont(_font);
    QFontMetrics fm = painter->fontMetrics();
    QString str = QString::fromStdString(_class->GetName());
    int xPos = (DEF_WIDTH - fm.horizontalAdvance(str)) / 2;
    int yPos = V_MARGIN;
    painter->drawText(xPos, yPos, fm.horizontalAdvance(str), fm.height(), Qt::AlignCenter, str);
    xPos = H_MARGIN;
    for(auto [name, attr]: _class->GetAttributes()){
        yPos += fm.height();
        yPos += V_MARGIN;

        str = QString();
        str.append(QChar(attr->GetPermission()));
        str.append(' ');
        str.append(attr->GetDataType().data());
        str.append(' ');
        str.append(name.data());

        painter->drawText(xPos, yPos, fm.horizontalAdvance(str), fm.height(), Qt::AlignLeft, str);
    }

    for(auto [name, meth]: _class->GetMethods()){
        yPos += fm.height();
        yPos += V_MARGIN;

        str = QString();
        str.append(QChar(meth->GetPermission()));
        str.append(' ');
        str.append(meth->GetReturnType().data());
        str.append(' ');
        str.append(name.data());
        str.append(" (");
        auto params = meth->GetParameters();
        std::set<MetaClassMethod::DataType>::iterator it;
        for(it = params.begin(); it != params.cbegin(); ++it){
            str.append(*it->data());
            if(it != std::prev(params.cend())){
                str.append(",");
            }
        }
        str.append(')');
        painter->drawText(xPos, yPos, fm.horizontalAdvance(str), fm.height(), Qt::AlignLeft, str);
    }
}
