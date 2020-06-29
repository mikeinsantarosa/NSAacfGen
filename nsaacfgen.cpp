/* File     : nsaacfgen.cpp
 * Author   : Mike Purtell
 * Date     : Nov 18, 2017
 *
 * Purpose  :
 *
 * Main object to control
 * coordinating loading
 * correction objects and indicating
 * progress and results.
 *
 *
 *
 * TODO:
 * Allow for an verride key
 * to use as the rx/tx file name base
 * in the event the program can't
 * figure out te file names dynamically.
 *
 * write the 4 other files that are in
 * the acf folder.
 *
 * 3mAcf.txt
 * 3mAntennas.txt
 * 5mAcf.txt
 * 5mAntennas.txt
 *
 * */

#include "nsaacfgen.h"
#include "ui_nsaacfgen.h"

NSAacfGen::NSAacfGen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NSAacfGen)
{
    ui->setupUi(this);
    loadSettings();

    if (workingPath == "")
        workingPath = "/home/mandbx/Desktop/nsa-acf-parts/target/";

    if (freqRefPath == "")
        freqRefPath = "/home/mandbx/Desktop/nsa-acf-parts/target/";
    //ui->tabDistanceSelector->setAutoFillBackground(true);
    //ui->tabDistanceSelector->setStyleSheet("background-color: darkgray");

    NotFoundMarker = "NotFound";

    _yearsToAddToCalDate = 1;

    ui->tabDistanceSelector->setCurrentIndex(0);


}

NSAacfGen::~NSAacfGen()
{
    delete ui;
}

void NSAacfGen::saveSettings()
{
    QSettings setting("Keysight","NSA-ACF-Generator");

    setting.beginGroup("ProgramFolders");

    setting.setValue("workingPath",workingPath);
    setting.setValue("freqRefPath",freqRefPath);
    setting.setValue("freqRefFile",_currentFreqRefFileName);
    setting.setValue("reportFolder",_currentReportFolder);
    setting.setValue("StartupPosition",this->geometry());

    setting.endGroup();

}

void NSAacfGen::loadSettings()
{
    // load setting
    QSettings setting("Keysight","NSA-ACF-Generator");

    setting.beginGroup("ProgramFolders");

    workingPath = setting.value("workingPath").toString();
    freqRefPath = setting.value("freqRefPath").toString();
    _currentFreqRefFileName = setting.value("freqRefFile").toString();
    _currentReportFolder = setting.value("reportFolder").toString();
    QRect rect = setting.value("StartupPosition").toRect();
    setGeometry(rect);

    setting.endGroup();
    // qDebug() << "Loaded freq ref file in settings - " << _currentFreqRefFileName;
    ui->linefreqRef->setText(_currentFreqRefFileName);
    ui->lineReportPath->setText(_currentReportFolder);
}

void NSAacfGen::setWorkingPath(QString path)
{
    if(!path.isEmpty())
    {
        QFileInfo fileinfo(path);
        workingPath = fileinfo.path();
        saveSettings();
    }
}

void NSAacfGen::setFreqRefPath(QString path)
{
    if(!path.isEmpty())
    {
        QFileInfo fileinfo(path);
        freqRefPath = fileinfo.path();
        ui->linefreqRef->setText(path);
        saveSettings();
    }
}

QString NSAacfGen::addYearToDateString(QString date, int numYears)
{
    QStringList group = date.split(" ");

    int newYear = (QString(group[2]).trimmed()).toInt();
    newYear = newYear + numYears;

    QString result = (QString(group[0]).trimmed() + " " + QString(group[1]).trimmed() + " " + QString::number(newYear));

    qDebug() << "new date - " << result;

    return result;

}


void NSAacfGen::mushTarget(QString filename, ACFStatus * status)
{

    if (!_currentFreqRefFileName.isEmpty())

    {

        FreqRef * rFreq = new FreqRef(_currentFreqRefFileName);

        if (!filename.isEmpty())

        {
            CorrectionSet * cor = new CorrectionSet(filename);
            status->setFilename(cor->getFilename());
            status->setDistance(cor->getDistance());
            status->setPolarity(cor->getPolarity());
            status->setSerial((cor->getSerial()));
            status->setModel(cor->getModel());
            status->setCalDate(cor->getCalDate());
            status->setBand(cor->getBand());

            Mushor * mush = new Mushor(cor->getKey());

            mush->setFreqList(rFreq->getPoints());
            // int numFreqs = mush->setFreqList(rFreq->getPoints());

            mush->setListToTranslate(cor->getPoints());
            // int numACFPoints = mush->setListToTranslate(cor->getPoints());


            mush->setReportableFileNames(cor->getRxFilename(), cor->getTxFilename());

            mush->setOutputFolder(_currentReportFolder);
            mush->MushData();

            delete cor;
            delete mush;


        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("ACF File not set. Click OK to close the dialog");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Freq ref not set. Click OK to close the dialog");
        msgBox.exec();
    }


}

void NSAacfGen::updateStatus(QLabel *processLabel, int PassFail)
{
    QColor alarmRed = QColor(255,0,0);
    QColor alarmGreen = QColor(0,255,0);

    QString style = "background: rgb(%1, %2, %3);";
    if (PassFail)
    {
       processLabel->setStyleSheet(style.arg(alarmGreen.red()).arg(alarmGreen.green()).arg(alarmGreen.blue()));
    }
    else
    {
        processLabel->setStyleSheet(style.arg(alarmRed.red()).arg(alarmRed.green()).arg(alarmRed.blue()));
    }
}

void NSAacfGen::updateAntennas(ACFStatus *calInfo)
{
    bool result = false;
    qDebug() << "Inside  update3MeterControls()";
    result = antennas->AssignStatusItem(calInfo);

    if (result)
    {
        if (antennas->get3MeterListComplete())
        {
            update3MeterControls();
            qDebug() << "Updating 3 meter controls";

        }

        if (antennas->get5MeterListComplete())
        {

            update5MeterControls();
            qDebug() << "Updating 5 meter controls";
        }
    }


}

void NSAacfGen::update3MeterControls()
{
    // update the 3 meter High

    QVector <ACFStatus> set = antennas->get3mAntennaSet();


    ui->line3RxHighModel->setText(set[HIGH_ANTENNA_POSITION].getModel());
    ui->line3TxHighModel->setText(set[HIGH_ANTENNA_POSITION].getModel());
    ui->line3RxHighSerial->setText(set[HIGH_ANTENNA_POSITION].getRXSerial());
    ui->line3TxHighSerial->setText(set[HIGH_ANTENNA_POSITION].getTXSerial());
    ui->line3RxHighCalDate->setText(set[HIGH_ANTENNA_POSITION].getCalDate());
    ui->line3TxHighCalDate->setText(set[HIGH_ANTENNA_POSITION].getCalDate());

    // update the 3 meter Low

    ui->line3RxLowModel->setText(set[LOW_ANTENNA_POSITION].getModel());
    ui->line3TxLowModel->setText(set[LOW_ANTENNA_POSITION].getModel());
    ui->line3RxLowSerial->setText(set[LOW_ANTENNA_POSITION].getRXSerial());
    ui->line3TxLowSerial->setText(set[LOW_ANTENNA_POSITION].getTXSerial());
    ui->line3RxLowCalDate->setText(set[LOW_ANTENNA_POSITION].getCalDate());
    ui->line3TxLowCalDate->setText(set[LOW_ANTENNA_POSITION].getCalDate());

 }

void NSAacfGen::update5MeterControls()
{
    // update the 3 meter High
    QVector <ACFStatus> set = antennas->get5mAntennaSet();

    ui->line5RxHighModel->setText(set[HIGH_ANTENNA_POSITION].getModel());
    ui->line5TxHighModel->setText(set[HIGH_ANTENNA_POSITION].getModel());
    ui->line5RxHighSerial->setText(set[HIGH_ANTENNA_POSITION].getRXSerial());
    ui->line5TxHighSerial->setText(set[HIGH_ANTENNA_POSITION].getTXSerial());
    ui->line5RxHighCalDate->setText(set[HIGH_ANTENNA_POSITION].getCalDate());
    ui->line5TxHighCalDate->setText(set[HIGH_ANTENNA_POSITION].getCalDate());

    // update the 3 meter Low

    ui->line5RxLowModel->setText(set[LOW_ANTENNA_POSITION].getModel());
    ui->line5TxLowModel->setText(set[LOW_ANTENNA_POSITION].getModel());
    ui->line5RxLowSerial->setText(set[LOW_ANTENNA_POSITION].getRXSerial());
    ui->line5TxLowSerial->setText(set[LOW_ANTENNA_POSITION].getTXSerial());
    ui->line5RxLowCalDate->setText(set[LOW_ANTENNA_POSITION].getCalDate());
    ui->line5TxLowCalDate->setText(set[LOW_ANTENNA_POSITION].getCalDate());

}

void NSAacfGen::writeListToFile(QString path, QString filename, QStringList list)
{
    // check the path for a / and add it if it's missing
    int len = path.length();

    if (path[len-1] != '/')
    {
        path.append('/');
    }

    QString pathAndFileName = "";
    pathAndFileName.append(path);
    pathAndFileName.append(filename);

    if ((!path.isNull()) && (!filename.isNull()))
    {

        QFile fOut(pathAndFileName);
        if(fOut.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream s(&fOut);
            for (int i = 0; i < list.count(); i++)
            {
                s << list.at(i) << '\n';
            }
        }
        else
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::critical(this,"File Write problem","Couldn't open the file [" + pathAndFileName + "] for writing!",QMessageBox::Ok);

        }

    }
    else
    {
        // inform the user nothing to save yet,
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this,"Missing information","Not enough information to save the data yet",QMessageBox::Ok);

    }




}

QStringList NSAacfGen::buildCalDataList(int distance)
{
    QStringList list;
    QString dollar = "$";
    QString newYear;

    if (distance ==3 )
    {
        newYear = addYearToDateString(ui->line3TxLowCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblTx3Low->text() + dollar + ui->line3TxLowModel->text() + dollar + ui->line3TxLowSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line3RxLowCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblTx3Low->text() + dollar +ui->line3RxLowModel->text() + dollar + ui->line3RxLowSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line3TxHighCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblTx3High->text() + dollar +ui->line3TxHighModel->text() + dollar + ui->line3TxHighSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line3RxHighCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblRx3High->text() + dollar +ui->line3RxHighModel->text() + dollar + ui->line3RxHighSerial->text()  + dollar + newYear);


    }
    if (distance == 5 )
    {

        newYear = addYearToDateString(ui->line5TxLowCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblTx5Low->text() + dollar + ui->line5TxLowModel->text() + dollar + ui->line5TxLowSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line5RxLowCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblRx5Low->text() + dollar + ui->line5RxLowModel->text() + dollar + ui->line5RxLowSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line5TxHighCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblTx5High->text() + dollar + ui->line5TxHighModel->text() + dollar + ui->line5TxHighSerial->text()  + dollar + newYear);
        newYear = addYearToDateString(ui->line5RxHighCalDate->text(), _yearsToAddToCalDate);
        list.append(ui->lblRx5High->text() + dollar + ui->line5RxHighModel->text() + dollar + ui->line5RxHighSerial->text()  + dollar + newYear);

    }

    return list;

}

void NSAacfGen::showCursorBusy()
{
    this->setCursor(QCursor(Qt::BusyCursor));
}

void NSAacfGen::showCursorNormal()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}



void NSAacfGen::on_btnClose_clicked()
{
    saveSettings();
    QCoreApplication::quit();
}

/*
 *  Using this method as a file tester
 *
 * // --
 *   temp code marker
 * // --
 *
 * */
void NSAacfGen::on_btnLoadHi3Horiz10_clicked()
{

    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status = new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);

        }

        updateStatus(ui->lblHi3Horiz10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi3horiz10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi3Vert10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            qDebug() << "attempting an antenna update...";
            updateAntennas(status);
        }

        updateStatus(ui->lblHi3Vert10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi3vert10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi3Vert15_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi3Vert15,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi3vert15->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi3Horiz20_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi3Horiz20,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi3horiz20->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow3Horiz10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow3Horiz10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow3horiz10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow3Vert10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow3Vert10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow3vert10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow3Vert15_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow3Vert15,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow3vert15->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow3Horiz20_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow3Horiz20,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow3horiz20->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi5Horiz10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi5Horiz10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi5horiz10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi5Vert10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi5Vert10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi5vert10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi5Vert15_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi5Vert15,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi5vert15->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadHi5Horiz20_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblHi5Horiz20,(!status->getFilename().contains(NotFoundMarker)));
        ui->linehi5horiz20->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow5Horiz10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);


        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow5Horiz10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow5horiz10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow5Vert10_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow5Vert10,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow5vert10->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow5Vert15_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow5Vert15,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow5vert15->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_btnLoadLow5Horiz20_clicked()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File",workingPath,"Text File (*.txt)");

    if ((!_currentFreqRefFileName.isEmpty()) && (!fileToOpen.isNull()))
    {
        this->showCursorBusy();
        ACFStatus * status= new ACFStatus;
        mushTarget(fileToOpen, status);
        setWorkingPath(fileToOpen);

        if(status->getUniqueSerialsAvailable())
        {
            updateAntennas(status);
        }

        updateStatus(ui->lblLow5Horiz20,(!status->getFilename().contains(NotFoundMarker)));
        ui->linelow5horiz20->setText(fileToOpen);
        this->showCursorNormal();
    }
}

void NSAacfGen::on_actionChange_Freq_Ref_triggered()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this,"Open File", freqRefPath,"Text File (*.txt)");

    if(!fileToOpen.isEmpty())
    {
        FreqRef * rFreq = new FreqRef(fileToOpen);
        _currentFreqRefFileName = fileToOpen;

        ui->linefreqRef->setText(fileToOpen);

        setFreqRefPath(fileToOpen);

        saveSettings();

    }



}


void NSAacfGen::on_actionChange_Report_Path_triggered()
{

    QString OutputFolder = QFileDialog::getExistingDirectory ( this, ("Select Output Folder"), _currentReportFolder, QFileDialog::ShowDirsOnly);

    if(!OutputFolder.isEmpty())
    {
        _currentReportFolder = OutputFolder;
    }
    ui->lineReportPath->setText(_currentReportFolder);

    saveSettings();

}

void NSAacfGen::on_actionAbout_triggered()
{
    About *about = new About;
    about->show();

}

void NSAacfGen::on_btnWriteCalDataFiles_clicked()
{

    if(!_currentReportFolder.isNull())
    {

        this->showCursorBusy();

        // save the 2 file list files
        baseFileLists * base = new baseFileLists();

        QString meter3ListName = base->get3mFilesListName();
        QString meter5ListName = base->get5mFilesListName();
        QString meter3AntennaCalFile = base->get3mAntennasFileName();
        QString meter5AntennaCalFile = base->get5mAntennasFileName();


        QStringList meter3List = base->get3MeterFileList();
        QStringList meter5List = base->get5MeterFileList();

        if (!meter3List.count() < 1)
        {
            writeListToFile(_currentReportFolder, meter3ListName, meter3List);
        }
        if (!meter5List.count() < 1)
        {
            writeListToFile(_currentReportFolder, meter5ListName, meter5List);
        }

        // check for 3 meter cal data and save if it exists

        bool list3Ready = antennas->get3MeterListComplete();

        if (list3Ready)
        {
            writeListToFile(_currentReportFolder, meter3AntennaCalFile, buildCalDataList(3));
        }
        // check for 3 meter cal data and save if it exists

        bool list5Ready = antennas->get5MeterListComplete();

        if (list5Ready)
        {
            writeListToFile(_currentReportFolder, meter5AntennaCalFile, buildCalDataList(5));
        }


    }
    this->showCursorNormal();

  }
