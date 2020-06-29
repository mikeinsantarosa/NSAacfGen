/* File     : antennacalinfo.cpp
 * Author   : Mike Purtell
 * Date     : Dec 06, 2017
 *
 * Purpose  :
 *
 * Singleton object to control
 * to sort out the antenna Calibration
 * information
  *
 *
 *
 * TODO:
 * Change the 3 & 5 meter lists to
 * vectors of type ACFStatus
 *
 * */

#include "antennacalinfo.h"


AntennaCalInfo* AntennaCalInfo::_instance = 0;

AntennaCalInfo* AntennaCalInfo::Instance()
{
    if (_instance == 0)
    {
        _instance = new AntennaCalInfo;
        _instance->init();

    }


    return _instance;
}

bool AntennaCalInfo::AssignStatusItem(ACFStatus *item)
{
    bool result = false;
    QString txMsg = "";
    QString rxMsg = "";
    QString dollars = "$";

    QString band = item->getBand().trimmed();
    int dist = item->getDistance().toInt();

    if (item->getBand().toUpper()=="HIGH")
    {

        if (dist == 3) // 3 meter data
        {

           _3meterAntennaSet.replace(HIGH_ANTENNA_POSITION, *item);

            _3MeterHighValid = true;
            result = true;

        }
        else // this is 5 meter data
        {

            _5meterAntennaSet.replace(HIGH_ANTENNA_POSITION, *item);

            _5MeterHighValid = true;
            result = true;

        }
    }
    else // this is a Low
    {


        if (dist == 3) // 3 meter data
        {

            _3meterAntennaSet.replace(LOW_ANTENNA_POSITION, *item);

            _3MeterLowValid = true;
            result = true;


        }
        else // this is 5 meter data
        {
            // assign 5 meter low tx/rx lines

            _5meterAntennaSet.replace(LOW_ANTENNA_POSITION, *item);

            _5MeterLowValid = true;
            result = true;

        }

    }


    return result;
}


QVector<ACFStatus> AntennaCalInfo::get3mAntennaSet()
{
    qDebug() << "inside get3mAntennaSet()";
    return _3meterAntennaSet;
}

QVector<ACFStatus> AntennaCalInfo::get5mAntennaSet()
{
    return _5meterAntennaSet;
}

bool AntennaCalInfo::get3MeterListComplete()
{
    bool result = false;
    if ((_3MeterLowValid == true) && (_3MeterHighValid == true))
    {
        result = true;
    }

    return result;

}

bool AntennaCalInfo::get5MeterListComplete()
{
    bool result = false;
    if ((_5MeterLowValid == true) && (_5MeterHighValid == true))
    {
        result = true;
    }

    return result;
}

AntennaCalInfo::AntennaCalInfo()
{
    // empty implementation
    // qDebug() << "Opening PRIVATE constructor";
}

void AntennaCalInfo::init()
{

    // Init the 3 meter vector list

    _3meterAntennaSet.clear();

    for (int i = 0; i < 2; i++)
    {
       ACFStatus  *acf = new ACFStatus;
       _3meterAntennaSet.append(*acf);
    }

    // init the 5 meter vector list
    _5meterAntennaSet.clear();

    for (int i = 0; i < 2; i++)
    {
       ACFStatus  *acf = new ACFStatus;
       _5meterAntennaSet.append(*acf);
    }

  }

