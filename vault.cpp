#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QMap>
#include <QString>
#include <QVector>
#include <QLineEdit>

#include <stdexcept>

#include "vault.h"

Vault::Vault(QObject *parent)
    : QObject{parent}
    , _masterModel(new QStringListModel(this))
    //, _detailedModel(new QStringListModel(this))
    , summiters({})
{
}

Vault::~Vault()
{
    for(Summiter*& el : summiters)
        delete el;

}

void Vault::loadFile(QString& filename)
{
    _filename = filename;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))/////////////make separate signal
    {
        QMessageBox msg;
        msg.setText("File not open");
        msg.exec();
    }
    QTextStream ts(&file);

    bool isFirstLine(true);
    while(!ts.atEnd())
    {
        QString line = ts.readLine();

        if(!line.isNull() && !isFirstLine)
        {
            QStringList splitLine = line.split(QLatin1Char(','));

            if(splitLine.size() == 12)
                summiters.insert(splitLine[2], new Summiter(splitLine));
        }
        else
            isFirstLine = false;
    }

    file.close();

    if(!summiters.isEmpty())
        emit contentsLoaded();

    _masterModel->setStringList(summiters.keys());


}


void Vault::updateModel(const QString &name, bool isAfterEdit)
{
    Summiter* sample = summiters[name];

    if(!sample)
        throw std::invalid_argument("Non-existing element");

    if(isAfterEdit)
    {
        QStringList data = getContentsFromView();
        sample->setNewData(data); // model receives data from edited fields first
    }

    updateDetailedView(name);

}

bool Vault::nullFileName() const
{
    return _filename == nullptr;
}

void Vault::saveToFile(const QString& filename) const
{
    _filename = filename; // can change field because it is 'mutable'

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw std::runtime_error("Cannot open a file");


    QTextStream ofstream(&file);

    for(Summiter* person : summiters)
    {
        QString line;
        for(QString& word : person->contents)
        {
            line.append(word);
            line.append(',');
        }
        line.chop(1); // deletes last comma
        ofstream << line << '\n';
    }

    file.close();
}

QString Vault::addSummiter(Summiter *summiter)
{
    summiters.insert(summiter->getName(), summiter);
    return summiter->getName();
}

void Vault::clearFields() const
{
    for(QLineEdit*& field : detailedModelFields())
        field->clear();
}

void Vault::deleteSummiter(QString& name)
{
    summiters.remove(name);
}

void Vault::addRow(QString &name)
{
    // magic line insertion from StackOverflow
    getMasterModel()->insertRow(getMasterModel()->rowCount());
    QModelIndex index = getMasterModel()->index(getMasterModel()->rowCount()-1);
    getMasterModel()->setData(index, name);
}


void Vault::setDetailedModelFields(QVector<QLineEdit *> fields)
{
    _detailedModelFields = fields;
}

// model is updated, the only thing needed is to update detailed view
void Vault::updateDetailedView(const QString& name)
{
    if(_detailedModelFields.size() != summiters[name]->contents.size())
        throw std::range_error("Number of fields in model and in model element do not match");

    size_t i = 0;
    for(QLineEdit*& field : _detailedModelFields)
    {
        field->setText(summiters[name]->contents[i]);
        ++i;
    }


}

// gets contents from detailed view
QStringList Vault::getContentsFromView()
{
    QStringList result;
    for(QLineEdit*& field : _detailedModelFields)
        result.push_back(field->text());

    return result;
}




















