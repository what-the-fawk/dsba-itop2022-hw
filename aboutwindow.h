#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

#include "logo.h"

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QDialog *parent = nullptr);
    ~AboutWindow();

protected:
    void drawLogo();

protected:
    Logo* _logo;

private slots:
    void on_btnBack_clicked();

private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
