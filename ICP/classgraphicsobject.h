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

#include "ClassDiagram/metaclass.h"
#include "newclassform.h"

class ClassGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    ClassGraphicsObject(std::shared_ptr<MetaClass>);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    MetaClass::Name GetClassName();
    QPointF GetItemCenter();

private:
    const int DEF_WIDTH = 200;
    const int V_MARGIN = 2;
    const int H_MARGIN = 2;

    void CalcHeight();
    void InitStrings();
    void InitActions();
    inline bool willOverflow(QString);

    QFont _font;
    std::shared_ptr<MetaClass> _class;
    int _totalHeight;
    int _titleHeight;
    int _attrHeight;
    int _methHeight;
    int _width;
    QString _titleStr;
    std::vector<QString> _attrStr;
    std::vector<QString> _methStr;

    QAction* _deleteClass;
    QAction* _editClass;

private slots:
    void editSelf();

signals:
    void killSelf(ClassGraphicsObject*);
};
