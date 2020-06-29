/* File     : nsaacfgen.h
 * Author   : Mike Purtell
 * Date     : Nov 18, 2017
 *
 * Purpose  :
 *
 * header file for the
 * main object.
 *
 * */

#ifndef NSAACFGEN_H
#define NSAACFGEN_H

#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QTextStream>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include "correctionset.h"
#include "freqref.h"
#include "mushor.h"
#include "about.h"
#include <QMessageBox>
#include <QColor>
#include "acfstatus.h"
#include "basefilelists.h"
#include "antennacalinfo.h"
#include <QMessageBox>
#include <QCursor>

namespace Ui {
class NSAacfGen;
}

class NSAacfGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit NSAacfGen(QWidget *parent = 0);
    ~NSAacfGen();



private slots:
    //void on_btnLoadHi3Horiz10_2_clicked();

    void on_btnClose_clicked();

    void on_btnLoadHi3Horiz10_clicked();

    void on_btnLoadHi3Vert10_clicked();

    void on_btnLoadHi3Vert15_clicked();

    void on_btnLoadHi3Horiz20_clicked();

    void on_btnLoadLow3Horiz10_clicked();

    void on_btnLoadLow3Vert10_clicked();

    void on_btnLoadLow3Vert15_clicked();

    void on_btnLoadLow3Horiz20_clicked();

    void on_btnLoadHi5Horiz10_clicked();

    void on_btnLoadHi5Vert10_clicked();

    void on_btnLoadHi5Vert15_clicked();

    void on_btnLoadHi5Horiz20_clicked();

    void on_btnLoadLow5Horiz10_clicked();

    void on_btnLoadLow5Vert10_clicked();

    void on_btnLoadLow5Vert15_clicked();

    void on_btnLoadLow5Horiz20_clicked();

    void on_actionChange_Freq_Ref_triggered();

    void on_actionChange_Report_Path_triggered();

    void on_actionAbout_triggered();

    void on_btnWriteCalDataFiles_clicked();

private:
    Ui::NSAacfGen *ui;

    int HIGH_ANTENNA_POSITION = 0;
    int LOW_ANTENNA_POSITION = 1;

    // variables
    QVector <CorrectionSet> correctionSets;
    QString workingPath;
    QString freqRefPath;
    QString _currentacfFileName;
    QString _currentFreqRefFileName;
    QString _currentReportFolder;
    QString NotFoundMarker;

    // methods
   void saveSettings();
   void loadSettings();

   void setWorkingPath(QString path);
   void setFreqRefPath(QString path);

   QStringList loadListfromFile(QString fileName);
   void listLines(QStringList list);
   int getFirstDataRow(QStringList list);
   QString findValue(QStringList list, QString match, QString splitChar);
   QString findElevation(QStringList list, QString match, QString splitChar);
   QString getBand(QStringList list);
   QStringList resizeListForRange(QStringList list);

   int _yearsToAddToCalDate;
   QString addYearToDateString(QString date, int numYears);
   void mushTarget(QString filename, ACFStatus * status);
   void updateStatus(QLabel *processLabel, int PassFail);

   void updateAntennas(ACFStatus * calInfo);


   AntennaCalInfo  * antennas = AntennaCalInfo::Instance();

   void update3MeterControls();
   void update5MeterControls();

   void writeListToFile(QString path, QString filename, QStringList list);

   QStringList buildCalDataList(int distance);

   // user feedback items
   void showCursorBusy();
   void showCursorNormal();







};

#endif // NSAACFGEN_H
