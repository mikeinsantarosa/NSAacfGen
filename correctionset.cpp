/* File     : correctionset.cpp
 * Author   : Mike Purtell
 * Date     : Nove 18, 2017
 *
 * Purpose  :
 *
 * Responsible for opening an ACF
 * data file and converting it into
 * a format the NSA verification
 * program can consume.
 *
 *
 * */

#include "correctionset.h"

//CorrectionSet::CorrectionSet(QObject *parent) :
//   QObject(parent)
//{

//}



CorrectionSet::CorrectionSet(const QString &path, QObject *parent) :
       QObject(parent)
{



    _dataLoaded = false;

    _pointList.clear();
    _masterList.clear();
    _resizedList.clear();

    _fistDataRow=-1;

    dateSearchString = "Date of Calibration"; //:
    modelSearchString = "Antenna Model"; //:
    serialSearchString = "Antenna Serial"; //:
    distanceSearchString = "Measurement Distance in Meters"; // =
    polaritySearchString = "Antenna Polarization"; // =
    elevationSearchString = "CF valid for"; // space

    _calDate = "";
    _model = "";
    _serial = "";
    _distance = "";
    _polarity = "";
    _elevation = "";
    _path = "";
    _filename = "";

    OutputFileExtenstion = ".csv";
    txMarker = "tx";
    rxMarker = "rx";
    lowBandMarker = "Low";
    highBandMarker = "High";
    horizMarker = "Horiz";
    vertMarker = "Vert";
    oneMeterMarker = "10";
    onept5MeterMarker = "15";
    twoMeterMarker = "20";

    threeMeterMarker = "3";
    fiveMeterMarker = "5";


    NotFoundMarker = "NotFound";


    init(path);
}

void CorrectionSet::init(QString fileToLoad)
{
    _masterList = loadListfromFile(fileToLoad);
    setWorkingPath(fileToLoad);
    setWorkingFilename(fileToLoad);
    _calDate = findValue(_masterList,dateSearchString, ":");
    _model = findValue(_masterList, modelSearchString, ":");
    _serial = findValue(_masterList, serialSearchString, ":");
    _distance = findValue(_masterList, distanceSearchString, "=");
    _polarity = findValue(_masterList, polaritySearchString, "=");
    _elevation = findElevation(_masterList, elevationSearchString, " ");
    _band = getBand(_masterList);

    // this really should be the vector
    _resizedList = resizeListForRange(_masterList);


    int numPoints = setPointList();

    //if (numPoints){};

    int numFiles = setFileNames();
    //if (numFiles){};

    // we want to use this for ID when we add
    // corrections to a vector manager
    // ----------------------------------------
    int keyHasBeenSet = setkey();

}

void CorrectionSet::setWorkingPath(QString path)
{
    if(!path.isEmpty())
    {
        QFileInfo fileinfo(path);
        _path = fileinfo.path();
    }
}

void CorrectionSet::setWorkingFilename(QString path)
{
    if(!path.isEmpty())
    {
        QFileInfo fileinfo(path);
        _filename = fileinfo.fileName();
    }
}

QVector<ACFDataPoint> CorrectionSet::getPoints()
{
    return _pointList;
}

QString CorrectionSet::getCalDate()
{
    _calDate.replace(".","").trimmed();
    return _calDate;
}

QString CorrectionSet::getBand()
{

    _band = _band.trimmed();
    return _band;
}

QString CorrectionSet::getFNameBand()
{
    QString result = "Low";
    qDebug() << "band coming in == " << _band;
    if (_band == "High")
    {
        result = "Hi";
    }
    return result;
}

QString CorrectionSet::getModel()
{

    _model = _model.trimmed();
    return _model;
}

QString CorrectionSet::getSerial()
{
    _serial = _serial.trimmed();
    return _serial;
}

QString CorrectionSet::getPath()
{
    return _path;
}

QString CorrectionSet::getFilename()
{
    return _filename;
}

QString CorrectionSet::getDistance()
{
    _distance = _distance.trimmed();
    return _distance;
}

QString CorrectionSet::getPolarity()
{
    _polarity = _polarity.trimmed();
    return _polarity;
}

QString CorrectionSet::getElevation()
{
    _elevation = _elevation.trimmed();
    return _elevation;
}

QString CorrectionSet::getRxFilename()
{
    return _rxFileName;
}

QString CorrectionSet::getTxFilename()
{
    return _txFileName;
}

QString CorrectionSet::getKey()
{
    return _key;
}

bool CorrectionSet::dataLoaded()
{
    return _dataLoaded;
}



int CorrectionSet::getFirstDataRow(QStringList list)
{
    QStringList group;
    int startIDX = -1;
    bool foundStartIDX = false;

    for (int fileRow = 0; fileRow < list.count(); fileRow++)
    {
            QString current = list[fileRow];
            group = current.split("\t");

            // we need to find 2 items
            // in a row that are numeric
            // if so, this row is correction
            // data.
            // -----------------------------
            int numFinds = 0;

            for (int i = 0; i < group.count(); i++)
            {
                QString gritItem = group[i];
                gritItem = gritItem.trimmed();
                bool isNumber = false;

                if (gritItem.toDouble(&isNumber))
                {

                    if (foundStartIDX == false)
                    {
                        numFinds = numFinds + 1;

                        if (numFinds > 1)
                        {

                            foundStartIDX = true;
                            startIDX = fileRow;

                        }
                    }
                }

            }

           if (foundStartIDX==true)
               break;
    }

    return startIDX;
}




QStringList CorrectionSet::loadListfromFile(QString fileName)
{

    QFile file(fileName);
    QStringList strings;
    strings.clear();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            strings += in.readLine();
        }
            file.close();
        }

    return strings;

}

void CorrectionSet::listLines(QStringList list)
{
    for (int fileRow = 0; fileRow < list.count(); fileRow++)
    {
        QString current = list[fileRow];
        qDebug() << "line " << fileRow << " is " << current;
    }

}

QString CorrectionSet::findValue(QStringList list, QString match, QString splitChar)
{
    QStringList group;
    QString result = "Not Found";

    bool foundMatch = false;

    for (int fileRow = 0; fileRow < list.count(); fileRow++)
    {
            QString current = list[fileRow];

            if (current.contains(match))
            {
                group = current.split(splitChar);
                result = group[1];
                foundMatch = true;
            }
    if (foundMatch==true)
        break;

    }

    return result;
}

QString CorrectionSet::findElevation(QStringList list, QString match, QString splitChar)
{
    QStringList group;
    QString result = "Not Found";

    bool foundMatch = false;

    for (int fileRow = 0; fileRow < list.count(); fileRow++)
    {
            QString current = list[fileRow];

            // qDebug() << "checking for - " << match <<" - in - " << current;

            if (current.contains(match))
            {
                group = current.split(splitChar);
//                for (int j=0; j < group.count(); j++)
//                {
//                    qDebug() << "group item - " << j << " is " << group[j];
//                }

                result = group[15];
                foundMatch = true;
            }
    if (foundMatch==true)
        break;

    }

    return result;
}

QString CorrectionSet::getBand(QStringList list)
{
    QStringList group;
    QString result = highBandMarker;
    double freq;


    QString current = list[list.count()-1];

//    qDebug() << "checking last row - " << current;

    group = current.split("\t");
    freq = group[0].toDouble();
    if (freq < 1000)
    {
        result = lowBandMarker;
    }

    return result;
}

QStringList CorrectionSet::resizeListForRange(QStringList list)
{
    int firstF = getFirstDataRow(list);
    int lastF = list.count();
    QStringList resizedList;
    QStringList currentRecord;
    QString current;
    QString newItem;
    QString firstACF;
    QString lastACF;
    QString firstLine;
    QString lastLine;
    QString newFirst;
    QString newLast;

    // if band is HIGH or LOW
    // change startIDX -1 to 20 and whatever the acf is
    // and add one to the end
    // 1100 and whatever he acf is
    // ----------------------------


    // get the start rows acf
    firstLine = list[firstF];
    QStringList firstRecord = firstLine.split("\t");
    firstACF = QString(firstRecord[1]).trimmed();

    lastLine = list[lastF - 1];
    QStringList lastRecord = lastLine.split("\t");
    lastACF = QString(lastRecord[1]).trimmed();


    newFirst = "20.0000\t" + firstACF;
    newLast = "1100.0000\t" + lastACF;


    // create a record to start the new list with
    resizedList.append(newFirst);
    for (int i = firstF; i < lastF; i++)
    {
        current = list[i];
        currentRecord = current.split("\t");
        newItem = currentRecord[0].trimmed() + "\t" + currentRecord[1].trimmed();
        resizedList.append(newItem);
    }

    resizedList.append(newLast);


    return resizedList;
}

int CorrectionSet::setkey()
{
    // clear existing;
    _key.clear();


    int result = -1;

    if (_dataLoaded == true)
    {

        // gatband
        _key.append(getBand());


        // get distance
        _key.append(getDistanceMarker());


        // get polarity
        _key.append(getPolarityMarker());


        // get elevation
        _key.append(getElevationMarker());

    }

    // check for a choke
    if (!_key.contains(NotFoundMarker))
    {
         result = 1;
    }

    return result;
}

QString CorrectionSet::getPolarityMarker()
{
    QString result = NotFoundMarker;

    if(getPolarity().contains("H"))
    {
        result = horizMarker;
    }
    if(getPolarity().contains("V"))
    {
        result = vertMarker;
    }

    return result;
}

QString CorrectionSet::getDistanceMarker()
{
    QString result = NotFoundMarker;

    if (getDistance().toInt() == 3)
    {
        result = threeMeterMarker;
    }
    if (getDistance().toInt() == 5)
    {
        result = fiveMeterMarker;
    }

    return result;

}

QString CorrectionSet::getElevationMarker()
{
    QString result = NotFoundMarker;

    if (getElevation().toDouble() == 1)
    {
        result = oneMeterMarker;
    }

    if (getElevation().toDouble() == 1.5)
    {
        result =  onept5MeterMarker;
    }

    if (getElevation().toDouble() == 2)
    {
        result = twoMeterMarker;
    }

    return result;
}


//const QString OutputFileExtenstion = ".csv";
//const QString txMarker = "tx";
//const QString rxMarker = "rx";
//const QString lowBandMarker = "Low";
//const QString highBandMarker = "Hi";
//const QString horizMarker = "Horiz";
//const QString vertMarker = "Vert";
//const QString oneMeterMarker = "10";
//const QString onept5MeterMarker = "15";
//const QString twoMeterMarker = "20";

// RX File name -  "rxLow3Vert15.csv"
// TX File name -  "txLow3Vert15.csv"

//  rxHi3Vert10

//  File name pattern to follow:
//
//  tx|rx Hi|Low  3|5 Horiz|Vert  10|15|20    .csv



int CorrectionSet::setFileNames()
{
    // clear existing;
    _rxFileName.clear();
    _txFileName.clear();

    int result = -1;

    if (_dataLoaded == true)
    {
        //get tx/rx
        _rxFileName = rxMarker;
        _txFileName = txMarker;

        // gatband
        _rxFileName.append(getFNameBand());
        _txFileName.append(getFNameBand());

        // get distance
        _rxFileName.append(getDistanceMarker());
        _txFileName.append(getDistanceMarker());

        // get polarity
        _rxFileName.append(getPolarityMarker());
        _txFileName.append(getPolarityMarker());

        // get elevation
        _rxFileName.append(getElevationMarker());
        _txFileName.append(getElevationMarker());

        // tack on the file extension
        _rxFileName.append(OutputFileExtenstion);
        _txFileName.append(OutputFileExtenstion);

    }

    // check for a choke
    if ((!_rxFileName.contains(NotFoundMarker) && (!_txFileName.contains(NotFoundMarker))))
    {
         result = 2;
    }

//    qDebug() << "RX File name - " << _rxFileName;
//    qDebug() << "TX File name - " << _txFileName;

    return result;
}

int CorrectionSet::setPointList()
{

    int result = -1;
    double freq = -1;
    double level = -1;
    QStringList group;

    for (int i = 0; i < _resizedList.count(); i++)
    {
        group = _resizedList[i].split("\t");
        freq = group[0].toDouble();
        level = group[1].toDouble();

        // not sure if this should be a pointer
        // -------------------------------------
        ACFDataPoint *apoint = new ACFDataPoint(freq, level);
        _pointList.append(*apoint);

    }
    result = _pointList.count();

    // qDebug() << "there were " << _resizedList.count() << " points to translate";

    _dataLoaded = true;

    return result;

}


