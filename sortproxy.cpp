#include "sortproxy.h"


SortProxy::SortProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
    , field(Name)
    , order(Ascending)
    , _summiters(nullptr)
{
}

SortProxy::SortProxy(QObject *parent, const QMap<QString, Summiter *>* summiters)
    : QSortFilterProxyModel(this)
    , field(Name)
    , order(Ascending)
    , _summiters(summiters)
{
}

bool SortProxy::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QString lhs = source_left.data().toString();
    QString rhs = source_right.data().toString();

    return getField(lhs) < getField(rhs);
}

QString SortProxy::getField(const QString& name) const
{
    switch(field)
    {
    case Name:
        return name;
        break;

    case PeakID:
        return (*_summiters)[name]->getPeakID();
        break;

    case PeakName:
        return (*_summiters)[name]->getPeakName();
        break;

    case YearSeason:
        return (*_summiters)[name]->getYearSeason();
        break;

    case Date:
        return (*_summiters)[name]->getDate();
        break;

    case Time:
        return (*_summiters)[name]->getTime();
        break;

    case Citizenship:
        return (*_summiters)[name]->getCitizenship();
        break;

    case Gender:
        return (*_summiters)[name]->getGender();
        break;

    case Age:
        return (*_summiters)[name]->getAge();
        break;

    }
}










