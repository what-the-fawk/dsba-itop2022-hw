#include "adderdialog.h"
#include "ui_adderdialog.h"

#include <QStringList>
#include <QIntValidator>
#include <QMessageBox>

AdderDialog::AdderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdderDialog),
    fields(new QStringList())
{
    ui->setupUi(this);

    // set up components

    ui->lineAge->setValidator(new QIntValidator(0, 99, this));
}

AdderDialog::~AdderDialog()
{
    delete ui;
}

void AdderDialog::on_btnSave_clicked()
{
    addData(ui->linePeakID);
    addData(ui->linePeakName);
    addData(ui->lineName);
    addData(ui->lineYearSeason);
    addData(ui->lineDate);
    addData(ui->lineTime);
    addData(ui->lineCitizenship);
    addData(ui->lineGender);
    addData(ui->lineAge);
    addData(ui->lineO2Usage);
    addData(ui->lineSummiter);
    addData(ui->lineCauseOfDeath);

    if(ui->lineName->text().isEmpty())
    {
        raiseMsgBox("Name cannot be empty");
        return;
    }

    close();
}

void AdderDialog::on_btnCancel_clicked()
{
    delete fields;
    close();
}

void AdderDialog::raiseMsgBox(const QString &text) const
{
    QMessageBox msg;
    msg.setWindowTitle("Incorect input");
    msg.setText(text);
    msg.exec();
}

void AdderDialog::addData(QLineEdit *field)
{
    fields->push_back(field->text());
}
