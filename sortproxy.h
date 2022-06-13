#ifndef SORTPROXY_H
#define SORTPROXY_H

#include <QSortFilterProxyModel>
#include <QObject>

#include "vault.h"


class SortProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum SortCriterion {PeakID, PeakName, Name, YearSeason, Date, Time, Citizenship,
                        Gender, Age,}; // every field except O2 usage and causeOfDeath and Summiter

    enum SortOrder {Ascending, Descending};

public:
    SortProxy(QObject* parent = nullptr);
    SortProxy(QObject* parent, const QMap<QString, Summiter*>* summiters);

    void setSummiters(const QMap<QString, Summiter*>* contents) {_summiters = contents; }

    void setSortField(SortCriterion sortField) { field = sortField; }
    void setSortOrder(SortOrder sortOrder) { order = sortOrder; }


protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    QString getField(const QString& name) const;

private:
    const QMap<QString, Summiter*>* _summiters;




protected:
    SortCriterion field;
    SortOrder order;


};

#endif // SORTPROXY_H
