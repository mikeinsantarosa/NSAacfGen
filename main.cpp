/* File     : main.cpp
 * Author   : Mike Purtell
 * Date     : Nove 18, 2017
 *
 * Purpose  :
 *
 * Main program entry/starting point.
 *
 *
 * */

#include "nsaacfgen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NSAacfGen w;
    w.show();

    return a.exec();
}
