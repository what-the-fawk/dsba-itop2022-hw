#ifndef ADDERDIALOG_H
#define ADDERDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QLineEdit>

namespace Ui {
class AdderDialog;
}

class AdderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdderDialog(QWidget *parent = nullptr);
    ~AdderDialog();
    QStringList getFields() const { return *fields; }

public:
    QStringList* fields;

private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();

    void raiseMsgBox(const QString& text) const;

protected:
    void addData(QLineEdit* field); // adds data from our QLineEdits to 'fields'




private:
    Ui::AdderDialog *ui;
};

#endif // ADDERDIALOG_H
