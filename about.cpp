#include "about.h"
#include "ui_about.h"


About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{

    ui->setupUi(this);

    QString labelText = "<html><head/><body>";
    labelText.append("<span style= font-size:10pt;font-weight:500;>Application Name: </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append(QApplication::applicationName());
    labelText.append("</span>");
    //labelText.append("<br/>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Application Version: </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append(QApplication::applicationVersion());
    labelText.append("</span>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Application Revision Date: </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append(Globals::REVISION_DATE.toString("MMMM dd, yyyy"));

    labelText.append("</span>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Description : </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append("Normalized Site Attenuation(NSA) Antenna Correction Factors(ACF) Correction File(s) Generator.");
    labelText.append("</span>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Company : </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append(QApplication::organizationName());
    labelText.append("</span>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Department : </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append(QApplication::organizationDomain());
    labelText.append("</span>");

    labelText.append("<p><span style= font-size:10pt;font-weight:500;>Author : </span>");
    labelText.append(" ");
    labelText.append("<span style= font-size:10pt;font-weight:300;>");
    labelText.append("Mike Purtell");
    labelText.append("</span>");


    labelText.append("</p></body></html>");
    ui->lblAbout->setText(labelText);
    ui->lblAbout->setStyleSheet("QLabel { background-color : white; color : black; padding:10px; }");


}

About::~About()
{
    delete ui;
}


void About::on_btnAbout_clicked()
{
    this->close();
}

QString About::getAboutLabelMarkup()
{
   // QString temp = "<html><head/><body><p><span style=" font-weight:600;">NSAacfGen: </span>version: " + APP_VERSION + "0.9.1</p><p><span style=" font-weight:600;">Description:</span> Normalized Site Attenuation Verification acf Corrections file(s) generator.</p><p><span style=" font-weight:600;">Keysight Technologies</span></p><p><span style=" font-weight:600;">Santa Rosa Hardware Test Center</span></p><p>Date: Nov 18, 2017</p></body></html>";
    //temp.append()
}
