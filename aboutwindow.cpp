#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "logo.h"

AboutWindow::AboutWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow),
    _logo(new Logo(this))
{
    ui->setupUi(this);

    drawLogo();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::drawLogo()
{
    _logo->setMinimumSize(100, 100);
    ui->layoutLogo->addWidget(_logo);
}

void AboutWindow::on_btnBack_clicked()
{
    close();
}

