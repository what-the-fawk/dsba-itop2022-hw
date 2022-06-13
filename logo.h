#ifndef LOGO_H
#define LOGO_H

#include <QObject>
#include <QWidget>

class Logo : public QWidget
{
    Q_OBJECT
public:
    explicit Logo(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

signals:


};

#endif // LOGO_H
