/* File     : basefilelists.cpp
 * Author   : Mike Purtell
 * Date     : Nove 21, 2017
 *
 * Purpose  :
 *
 *
 * 4 auxiliary files
 * creator .
 *
 *
 * 3mAcf.txt (first pass is fixed)
 * 3mAntennas.txt  (first pass is dynamic)
 * 5mAcf.txt (first pass is fixed)
 * 5mAntennas.txt (first pass is dynamic)
 *
 * */



#include "basefilelists.h"

baseFileLists::baseFileLists()
{
    init3mFileList();
    init5mFileList();
    initFilesListNames();

}

QStringList baseFileLists::get3MeterFileList()
{
    return _3mList;
}

QStringList baseFileLists::get5MeterFileList()
{
    return _5mList;
}

QString baseFileLists::get3mFilesListName()
{
    return _3mFilesListName;
}

QString baseFileLists::get5mFilesListName()
{
    return _5mFilesListName;
}

QString baseFileLists::get3mAntennasFileName()
{
    return _3mAntennasFileName;
}

QString baseFileLists::get5mAntennasFileName()
{
    return _5mAntennasFileName;
}

void baseFileLists::init3mFileList()
{
    _3mList.clear();


    _3mList.append(QString("Tx Ant. Low-Band 3 m. sep. - Horiz 1.0 m. elev.,txLow3Horiz10.csv"));
    _3mList.append(QString("Tx Ant. Low-Band 3 m. sep. - Vert 1.0 m. elev.,txLow3Vert10.csv"));
    _3mList.append(QString("Tx Ant. Hi-Band 3 m. sep. - Horiz 1.0 m. elev.,txHi3Horiz10.csv"));
    _3mList.append(QString("Tx Ant. Hi-Band 3 m. sep. - Vert 1.0 m. elev.,txHi3Vert10.csv"));
    _3mList.append(QString("Tx Ant. Low-Band 3 m. sep. - Horiz 2.0 m. elev.,txLow3Horiz20.csv"));
    _3mList.append(QString("Tx Ant. Low-Band 3 m. sep. - Vert 1.5 m. elev.,txLow3Vert15.csv"));
    _3mList.append(QString("Tx Ant. Hi-Band 3 m. sep. - Horiz 2.0 m. elev.,txHi3Horiz20.csv"));
    _3mList.append(QString("Tx Ant. Hi-Band 3 m. sep. - Vert 1.5 m. elev.,txHi3Vert15.csv"));
    _3mList.append(QString("Rx Ant. Low-Band 3 m. sep. - Horiz 1.0 m. elev.,rxLow3Horiz10.csv"));
    _3mList.append(QString("Rx Ant. Low-Band 3 m. sep. - Vert 1.0 m. elev.,rxLow3Vert10.csv"));
    _3mList.append(QString("Rx Ant. Hi-Band 3 m. sep. - Horiz 1.0 m. elev.,rxHi3Horiz10.csv"));
    _3mList.append(QString("Rx Ant. Hi-Band 3 m. sep. - Vert 1.0 m. elev.,rxHi3Vert10.csv"));
    _3mList.append(QString("Rx Ant. Low-Band 3 m. sep. - Horiz 2.0 m. elev.,rxLow3Horiz20.csv"));
    _3mList.append(QString("Rx Ant. Low-Band 3 m. sep. - Vert 1.5 m. elev.,rxLow3Vert15.csv"));
    _3mList.append(QString("Rx Ant. Hi-Band 3 m. sep. - Horiz 2.0 m. elev.,rxHi3Horiz20.csv"));
    _3mList.append(QString("Rx Ant. Hi-Band 3 m. sep. - Vert 1.5 m. elev.,rxHi3Vert15.csv"));

}

void baseFileLists::init5mFileList()
{
    _5mList.clear();

    _5mList.append(QString("Tx Ant. Low-Band 5 m. sep. - Horiz 1.0 m. elev.,txLow5Horiz10.csv"));
    _5mList.append(QString("Tx Ant. Low-Band 5 m. sep. - Vert 1.0 m. elev.,txLow5Vert10.csv"));
    _5mList.append(QString("Tx Ant. Hi-Band 5 m. sep. - Horiz 1.0 m. elev.,txHi5Horiz10.csv"));
    _5mList.append(QString("Tx Ant. Hi-Band 5 m. sep. - Vert 1.0 m. elev.,txHi5Vert10.csv"));
    _5mList.append(QString("Tx Ant. Low-Band 5 m. sep. - Horiz 2.0 m. elev.,txLow5Horiz20.csv"));
    _5mList.append(QString("Tx Ant. Low-Band 5 m. sep. - Vert 1.5 m. elev.,txLow5Vert15.csv"));
    _5mList.append(QString("Tx Ant. Hi-Band 5 m. sep. - Horiz 2.0 m. elev.,txHi5Horiz20.csv"));
    _5mList.append(QString("Tx Ant. Hi-Band 5 m. sep. - Vert 1.5 m. elev.,txHi5Vert15.csv"));
    _5mList.append(QString("Rx Ant. Low-Band 5 m. sep. - Horiz 1.0 m. elev.,rxLow5Horiz10.csv"));
    _5mList.append(QString("Rx Ant. Low-Band 5 m. sep. - Vert 1.0 m. elev.,rxLow5Vert10.csv"));
    _5mList.append(QString("Rx Ant. Hi-Band 5 m. sep. - Horiz 1.0 m. elev.,rxHi5Horiz10.csv"));
    _5mList.append(QString("Rx Ant. Hi-Band 5 m. sep. - Vert 1.0 m. elev.,rxHi5Vert10.csv"));
    _5mList.append(QString("Rx Ant. Low-Band 5 m. sep. - Horiz 2.0 m. elev.,rxLow5Horiz20.csv"));
    _5mList.append(QString("Rx Ant. Low-Band 5 m. sep. - Vert 1.5 m. elev.,rxLow5Vert15.csv"));
    _5mList.append(QString("Rx Ant. Hi-Band 5 m. sep. - Horiz 2.0 m. elev.,rxHi5Horiz20.csv"));
    _5mList.append(QString("Rx Ant. Hi-Band 5 m. sep. - Vert 1.5 m. elev.,rxHi5Vert15.csv"));

}

void baseFileLists::initFilesListNames()
{
    _3mFilesListName = "3mAcf.txt";
    _5mFilesListName = "5mAcf.txt";
    _3mAntennasFileName = "3mAntennas.txt";
    _5mAntennasFileName = "5mAntennas.txt";
}
