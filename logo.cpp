#include "logo.h"

#include <QPainter>

Logo::Logo(QWidget *parent)
    : QWidget{parent}
{

}

void Logo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);

    QBrush backGr(Qt::GlobalColor::cyan);

    painter.setBrush(backGr);

    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    painter.drawRect(5, 5, 5, 5);

    QPen pen(Qt::red, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush bacGr(Qt::GlobalColor::darkGreen);

    painter.setPen(pen);

    painter.drawEllipse(10, 10, width() - 20, height() - 20);
    painter.drawArc(0, 0, 10, 10, 25, 30);
}


