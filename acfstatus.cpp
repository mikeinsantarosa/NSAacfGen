#include "acfstatus.h"



ACFStatus::ACFStatus()

{
    _uniqueSerialsAvailable = false;
}


QString ACFStatus::getCalDate()
{
    return _calDate.trimmed();
}

void ACFStatus::setCalDate(QString date)
{
    _calDate = date;
}

void ACFStatus::setModel(QString model)
{
    _model = model;
}

QString ACFStatus::getModel()
{
    return _model;
}

QString ACFStatus::getSerial()
{
    return _serial;
}

QString ACFStatus::getRXSerial()
{
   return _rxSerial;
}

QString ACFStatus::getTXSerial()
{
    return _txSerial;
}

void ACFStatus::setSerial(QString serial)
{
    QStringList list = serial.split(";");
    if (list.count() > 1)
    {
        _txSerial = list[0].trimmed();
        _rxSerial = list[1].trimmed();
        _uniqueSerialsAvailable = true;
    }
    else
    {
        _txSerial = serial;
        _rxSerial = serial;
    }
    _serial = serial;

}

QString ACFStatus::getPath()
{
    return _path;
}

void ACFStatus::setPath(QString path)
{
    _path = path;
}

QString ACFStatus::getFilename()
{
    return _filename;
}

void ACFStatus::setFilename(QString fname)
{
    _filename = fname;
}

QString ACFStatus::getDistance()
{
    return _distance;
}

void ACFStatus::setDistance(QString distance)
{
    _distance = distance;
}

QString ACFStatus::getBand()
{
    return _band;
}

void ACFStatus::setBand(QString band)
{
    _band = band;
}




QString ACFStatus::getPolarity()
{
    return _polarity;
}

void ACFStatus::setPolarity(QString pol)
{
    _polarity = pol;
}

QString ACFStatus::getElevation()
{
    return _elevation;
}

void ACFStatus::setElevation(QString elevation)
{
    _elevation = elevation;
}

QString ACFStatus::getRxFilename()
{
    return _rxFileName;
}

void ACFStatus::setRxFilename(QString fname)
{
    qDebug() << "setting filename in ACFStatus::setRxFilename";
    _rxFileName = fname;
}

QString ACFStatus::getTxFilename()
{
    return _txFileName;
}

void ACFStatus::setTxFilename(QString fname)
{
    _txFileName = fname;
}

QString ACFStatus::getKey()
{
    return _key;
}

void ACFStatus::setKey(QString key)
{
    _key = key;
}

int ACFStatus::getReportListcount()
{
    return _reportListCount;
}

void ACFStatus::setReportListCount(int count)
{
    _reportListCount = count;
}

bool ACFStatus::getUniqueSerialsAvailable()
{
    return _uniqueSerialsAvailable;
}

QString ACFStatus::getTxMessage()
{
    QString result = "";
    QString dollars = "$";

    result.append("TX-");
    result.append(this->getBand());
    result.append(dollars);
    result.append(this->getModel());
    result.append(dollars);

    if (this->getUniqueSerialsAvailable())
    {
        result.append(this->getTXSerial());
    }
    else
    {
        result.append(this->getSerial());
    }

    result.append(dollars);
    result.append(this->getCalDate());

    return result;
}

QString ACFStatus::getRxMessage()
{
    QString result = "";
    QString dollars = "$";

    result.append("RX-");
    result.append(this->getBand());
    result.append(dollars);
    result.append(this->getModel());
    result.append(dollars);

    if (this->getUniqueSerialsAvailable())
    {
        result.append(this->getRXSerial());
    }
    else
    {
        result.append(this->getSerial());
    }

    result.append(this->getRXSerial());
    result.append(dollars);
    result.append(this->getCalDate());

    return result;
}
