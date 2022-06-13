#ifndef VAULT_H
#define VAULT_H

#include <QObject>
#include <QString>
#include <QStringListModel>
#include <QMap>
#include <QVector>
#include <QLineEdit>

struct Summiter
{
public:
    QStringList contents;

public:
    explicit Summiter(QStringList lst) // constructor (does not set a pic)
        : contents(lst)
    {
    }

    explicit Summiter() // default constructor
    {
        contents.reserve(13);
    }

public:
    // getters
    QString getPeakID() const { return contents[0]; }
    QString getPeakName() const { return contents[1]; }
    QString getName() const { return contents[2]; }
    QString getYearSeason() const { return contents[3]; }
    QString getDate() const { return contents[4]; }
    QString getTime() const { return contents[5]; }
    QString getCitizenship() const { return contents[6]; }
    QString getGender() const { return contents[7]; }
    QString getAge() const { return contents[8]; }
    QString getO2Usage() const { return contents[9]; }
    QString getSummitership() const { return contents[10]; }
    QString getCauseOfDeath() const { return contents[11]; }

    //setter
    void setNewData(const QStringList& data) { contents = data; }

};



class Vault : public QObject
{
    Q_OBJECT
    friend class SortProxy;
public:
    explicit Vault(QObject *parent);
    ~Vault();

    QStringListModel* getMasterModel() const { return _masterModel; }

public:
    void loadFile(QString& filename);
    void updateModel(const QString& name, bool isAfterEdit);
    bool nullFileName() const ; // checks nullity of filename
    void saveToFile(const QString& filename) const;
    void addSummiter(QString name) { summiters.insert(name, new Summiter()); }
    QString addSummiter(Summiter* summiter);
    void clearFields() const;
    void deleteSummiter(QString& name);
    void addRow(QString& name);

    QVector<QLineEdit*> detailedModelFields() const { return _detailedModelFields; }
    void setDetailedModelFields(QVector<QLineEdit*> fields);

    QStringList getContentsFromView();

    const QMap<QString, Summiter*>* getSummiters() const { return &summiters; }


protected:
    void updateDetailedView(const QString& name);

public:
    QString getFileName() const { return _filename; }

signals:
    void contentsLoaded();

protected:
    QStringListModel* _masterModel;
    mutable QString _filename; // kinda want to change filename in const methods if nessesary (in saveToFile() for example)
    QMap<QString, Summiter*> summiters; // <name, contents>
    QVector<QLineEdit*> _detailedModelFields;


};

#endif // VAULT_H
