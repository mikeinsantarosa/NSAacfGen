

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QPalette>
#include <QDebug>
#include "version.h"
//#include "globals.h"

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:


    void on_btnAbout_clicked();

private:
    Ui::About *ui;
    QString getAboutLabelMarkup();
    QString getRevDate();



};

#endif // ABOUT_H
