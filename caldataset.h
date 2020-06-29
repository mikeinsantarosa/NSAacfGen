#ifndef CALDATASET_H
#define CALDATASET_H

#include <QDebug>

class CalDataSet
{
public:
    CalDataSet();

    void setModel(QString model);
    void setSerial(QString serial);
    void setCalDate(QString calDate);

private:
    QString _model;
    QString _serial;
    QString _calDate;

};

#endif // CALDATASET_H
