/* File     : basefilelists.h
 * Author   : Mike Purtell
 * Date     : Nove 21, 2017
 *
 * Purpose  :
 *
 * Header file for a
 * 4 auxiliary files
 *
 *
 * */

#ifndef BASEFILELISTS_H
#define BASEFILELISTS_H

#include <QDebug>
#include <QStringList>
#include <QString>


class baseFileLists
{
public:
    baseFileLists();


    //methods
    QStringList get3MeterFileList();
    QStringList get5MeterFileList();

    QString get3mFilesListName();
    QString get5mFilesListName();

    QString get3mAntennasFileName();
    QString get5mAntennasFileName();

private:
    QStringList _5mList;
    QStringList _3mList;

    QString _3mFilesListName;
    QString _5mFilesListName;

    QString _3mAntennasFileName;
    QString _5mAntennasFileName;

    QString _3mLowTxModel;
    QString _3mLowRxModel;
    QString _3mLowTxSerial;
    QString _3mLowRxSerial;
    QString _3mLowTxCalDate;
    QString _3mLowRxCalDate;

    QString _5mLowTxModel;
    QString _5mLowRxModel;
    QString _5mLowTxSerial;
    QString _5mLowRxSerial;
    QString _5mLowTxCalDate;
    QString _5mLowRxCalDate;




    void init3mFileList();
    void init5mFileList();

    void initFilesListNames();


};

#endif // BASEFILELISTS_H
