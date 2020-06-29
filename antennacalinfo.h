#ifndef ANTENNACALINFO_H
#define ANTENNACALINFO_H

#include <QDebug>
#include <QStringList>
#include "acfstatus.h"
#include <QString>
/* File     : antennacalinfo.h
 * Author   : Mike Purtell
 * Date     : Dec 06, 2017
 *
 * Purpose  :
 *
 * Header file to control
 * to sort out the antenna Calibration
 * information
 *
 * Implements singleton pattern.
 *
 * TODO:
 *
 * */

#include <QObject>
#include <QVector>
#include "acfstatus.h"

class AntennaCalInfo : public QObject
{
    Q_OBJECT
public:



    static AntennaCalInfo* Instance();

    bool AssignStatusItem(ACFStatus * item);

    QVector <ACFStatus> get3mAntennaSet();
    QVector <ACFStatus> get5mAntennaSet();


    bool get3MeterListComplete();

    bool get5MeterListComplete();


private:

    int HIGH_ANTENNA_POSITION = 0;
    int LOW_ANTENNA_POSITION = 1;

    AntennaCalInfo();

    static AntennaCalInfo* _instance;

    // variables

    QVector <ACFStatus> _3meterAntennaSet;
    QVector <ACFStatus> _5meterAntennaSet;

    bool _3MeterLowValid = false;
    bool _3MeterHighValid = false;
    bool _5MeterLowValid = false;
    bool _5MeterHighValid = false;



    // methods
    void init();

};

#endif // ANTENNACALINFO_H
