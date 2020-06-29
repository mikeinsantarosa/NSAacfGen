/* File     : correctionset.h
 * Author   : Mike Purtell
 * Date     : Nove 18, 2017
 *
 * Purpose  :
 *
 * Header file for the acf data set
 * object
 *
 * */

#ifndef CORRECTIONSET_H
#define CORRECTIONSET_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include "acfdatapoint.h"
#include <QString>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QFileInfo>

class CorrectionSet : public QObject
{
    Q_OBJECT
public:


//    explicit CorrectionSet(QObject *parent = 0);
    explicit CorrectionSet(const QString &path, QObject *parent = 0);

    // variables

    int numPoints;


    //methods

    QVector <ACFDataPoint> getPoints();

    QString getCalDate();
    QString getBand();
    QString getFNameBand();
    QString getModel();
    QString getSerial();
    QString getPath();
    QString getFilename();
    QString getDistance();
    QString getPolarity();
    QString getElevation();
    QString getRxFilename();
    QString getTxFilename();
    QString getKey();

    bool dataLoaded();



private:
    // output filename constants
    // ----------------------------------
    QString OutputFileExtenstion;
    QString txMarker;
    QString rxMarker;
    QString lowBandMarker;
    QString highBandMarker;
    QString horizMarker;
    QString vertMarker;
    QString oneMeterMarker;
    QString onept5MeterMarker;
    QString twoMeterMarker;
    QString threeMeterMarker;
    QString fiveMeterMarker;
    QString _key;

    QString NotFoundMarker;






    // variables
    QVector <ACFDataPoint> _pointList;
    QStringList _masterList;

    // this should be the vector
    QStringList _resizedList;

    int _fistDataRow;

    bool _dataLoaded;

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

    QString dateSearchString;
    QString modelSearchString;
    QString serialSearchString;
    QString distanceSearchString;
    QString polaritySearchString;
    QString elevationSearchString;

    // methods
    void init(QString fileToLoad);
    void setWorkingPath(QString path);
    void setWorkingFilename(QString path);
    int getFirstDataRow(QStringList list);
    int setPointList();
    QStringList loadListfromFile(QString fileName);
    void listLines(QStringList list);
    QString findValue(QStringList list, QString match, QString splitChar);
    QString findElevation(QStringList list, QString match, QString splitChar);
    QString getBand(QStringList list);
    QStringList resizeListForRange(QStringList list);

    int setkey();



    QString getPolarityMarker();
    QString getDistanceMarker();
    QString getElevationMarker();

    // return number of filenames that were able to be set
    // ---------------------------------------------------
    int setFileNames();

signals:

public slots:

};

#endif // CORRECTIONSET_H
