#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLineEdit>

#include "vault.h"
#include "sortproxy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QVector<QLineEdit*> getDetailedModelFields();
    void makeModelEditable(bool setter);
    void raiseMsgBox(QString text);
    void changeMode(int mode);

protected:
    enum Mode {MainWindowMode, AboutMode};

private:
    Ui::MainWindow *ui;

protected:
    Vault* _vault;
    SortProxy* _proxyModel;


private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionQuit_triggered();
    void on_MasterView_clicked(const QModelIndex &index);
    void onContentsLoaded();
    void on_btnEditModeActivator_clicked();


    void on_combSortField_activated(int index);
    void on_btnSort_clicked();
    void on_actionAbout_triggered();
};
#endif // MAINWINDOW_H
