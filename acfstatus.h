#ifndef ACFSTATUS_H
#define ACFSTATUS_H

#include <QObject>
#include <QDebug>
#include "correctionset.h"
#include "mushor.h"

class ACFStatus
{

public:
    explicit ACFStatus();

    QString getCalDate();
    void setCalDate(QString date);


    QString getBand();
    void setBand(QString band);


    QString getModel();
    void setModel(QString model);


    QString getSerial();
    QString getRXSerial();
    QString getTXSerial();
    void setSerial(QString serial);


     QString getPath();
    void setPath(QString path);


    QString getFilename();
    void setFilename(QString fname);


    QString getDistance();
    void setDistance(QString distance);


    QString getPolarity();
    void setPolarity(QString pol);


    QString getElevation();
    void setElevation(QString elevation);

    QString getRxFilename();
    void setRxFilename(QString fname);


    QString getTxFilename();
    void setTxFilename(QString fname);


    QString getKey();
    void setKey(QString key);

    int getReportListcount();
    void setReportListCount(int count);

    bool getUniqueSerialsAvailable();


    QString getTxMessage();
    QString getRxMessage();




private:
    QString _calDate;
    QString _band;
    QString _model;
    QString _serial;
    QString _path;
    QString _filename;
    QString _distance;
    QString _polarity;
    QString _elevation;
    QString _rxFileName;
    QString _txFileName;
    QString _rxSerial;
    QString _txSerial;
    QString _key;


    int _reportListCount;

    bool _uniqueSerialsAvailable;




signals:

public slots:

};

#endif // ACFSTATUS_H
