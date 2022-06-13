#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPixmap>

#include <stdexcept>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "adderdialog.h"
#include "sortproxy.h"
#include "aboutwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _vault(new Vault(this))
    , _proxyModel(new SortProxy(this))
{
    ui->setupUi(this);
    changeMode(Mode::MainWindowMode);

    // additional object set-up
    _vault->setDetailedModelFields(getDetailedModelFields());
    _proxyModel->setSummiters(_vault->getSummiters());
    _proxyModel->setSourceModel(_vault->getMasterModel());

    ui->MasterView->setModel(_proxyModel);

    ui->profilePic->setVisible(true);

    // signal-slot connections
    QDialog::connect(_vault, &Vault::contentsLoaded, this, &MainWindow::onContentsLoaded); // sets model visible


    // set-up components programmatically
    ui->widButtons->setVisible(false);
    ui->DetailedView->setVisible(false); ////////////////////////////

    ui->btnDelete->setEnabled(false);
    ui->MasterView->setEditTriggers(ui->MasterView->NoEditTriggers);


    //ui->MasterView->setEnabled(false);



    //ui->btnDelete->isEnabled(); // checker


}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QLineEdit*> MainWindow::getDetailedModelFields()
{
    QVector<QLineEdit*> fields;

    //loading fields in the same order as they are listed in dataset
    fields.push_back(ui->linePeakID);
    fields.push_back(ui->linePeakName);
    fields.push_back(ui->lineName);
    fields.push_back(ui->lineYearSeason);
    fields.push_back(ui->lineDate);
    fields.push_back(ui->lineTime);
    fields.push_back(ui->lineCitizenship);
    fields.push_back(ui->lineGender);
    fields.push_back(ui->lineAge);
    fields.push_back(ui->lineO2Usage);
    fields.push_back(ui->lineSummiter);
    fields.push_back(ui->lineCauseOfDeath);

    return fields;
}




// buttons
void MainWindow::on_btnAdd_clicked()/////////////////////////////////////
{
    AdderDialog* adder = new AdderDialog();
    adder->setModal(true);
    adder->exec();

    QStringList contents = adder->getFields(); // somehow get user input
    QString name = _vault->addSummiter(new Summiter(contents));

    _vault->addRow(name); // implemented some kind of decomposition here

    if(!(ui->btnDelete->isEnabled()))
        ui->btnDelete->setEnabled(true);
}


void MainWindow::on_btnDelete_clicked()
{

    QModelIndex index = ui->MasterView->selectionModel()->currentIndex();
    QString name = ui->MasterView->currentIndex().data().toString();
    _vault->deleteSummiter(name);
    ui->MasterView->model()->removeRow(index.row());

    _vault->clearFields();
}

// edit button functionality
void MainWindow::on_btnEditModeActivator_clicked()
{
    if(ui->btnEditModeActivator->text() == QString("Edit"))
    {
        makeModelEditable(true);
        ui->btnEditModeActivator->setText(QString("Finish Editing"));
    }
    else
    {
        makeModelEditable(false);
        ui->btnEditModeActivator->setText(QString("Edit"));
        _vault->updateModel(ui->MasterView->currentIndex().data().toString(), true); // first arg is just name
    }
}

// menubar action
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                 "Open data file",
                                 "",
                                 "Comma Separated Values (*.csv);;Text files (*.txt);;All Files (*.*)");

    if(filename.isNull())
        return;

    if(filename.isEmpty())
    {
        emit raiseMsgBox("File name is empty");
        return;
    }

    _vault->loadFile(filename);
    ui->btnDelete->setEnabled(true);

}



void MainWindow::on_actionSave_triggered()
{
    if(_vault->nullFileName()) // if user has not loaded a file yet, programmm forces him to create a new one
        emit on_actionSaveAs_triggered();


    _vault->saveToFile(_vault->getFileName());
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(nullptr,
                                                    "Save file",
                                                    "",
                                                    "Comma separated values(*.csv);;All Files(*.*)"
                                                    );

    if(filename.isEmpty() || filename.isNull())
        return;

    _vault->saveToFile(filename);

}


void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_MasterView_clicked(const QModelIndex &index)/////////////
{
    QString summiterName = index.data().toString();
    _vault->updateModel(summiterName, false);
}

// helper func that just raises msg box if necessary
void MainWindow::raiseMsgBox(QString text)
{
    QMessageBox msg;
    msg.setText(text);
    msg.exec();
}

// my own signal-slot connection
void MainWindow::onContentsLoaded()
{
    ui->DetailedView->setVisible(true);
    ui->widButtons->setVisible(true);

    ui->lblDetailedView->setText("Detailed view");
}

// helper method which sets editability of DetailedView
void MainWindow::makeModelEditable(bool setter)
{
    for(QLineEdit*& field : _vault->detailedModelFields())
        field->setReadOnly(!setter);

}

// changes mode of the main window
void MainWindow::changeMode(int mode)
{
    switch(mode)
    {
    case Mode::MainWindowMode:
        setCentralWidget(ui->mainUI);
        break;

    case Mode::AboutMode:
        AboutWindow about(nullptr);
        about.exec();
        break;
    }
}


void MainWindow::on_combSortField_activated(int index)
{
    switch (index)
    {
    case 0:
    _proxyModel->setSortField(SortProxy::Name);
    break;

    case 1:
    _proxyModel->setSortField(SortProxy::PeakID);
    break;

    case 2:
    _proxyModel->setSortField(SortProxy::PeakName);
    break;

    case 3:
    _proxyModel->setSortField(SortProxy::YearSeason);
    break;

    case 4:
    _proxyModel->setSortField(SortProxy::Date);
    break;

    case 5:
    _proxyModel->setSortField(SortProxy::Time);
    break;

    case 6:
    _proxyModel->setSortField(SortProxy::Citizenship);
    break;

    case 7:
    _proxyModel->setSortField(SortProxy::Gender);
    break;

    case 8:
    _proxyModel->setSortField(SortProxy::Age);
    break;

    default:
        throw std::invalid_argument("Incorrect sorting criterion");
        break;
    }
}


void MainWindow::on_btnSort_clicked()
{
    int i = ui->combSortOrder->currentIndex();

    switch(i)
    {
    case 0:
        _proxyModel->sort(0, Qt::AscendingOrder);
        break;

    case 1:
        _proxyModel->sort(0, Qt::DescendingOrder);
        break;

    default:
        throw std::invalid_argument("Incorrect sort order");
        break;
    }
}


void MainWindow::on_actionAbout_triggered()
{
    changeMode(Mode::AboutMode);
}

