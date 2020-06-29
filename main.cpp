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

    // Setup application properties
    a.setOrganizationName("Keysight Technologies");
    a.setOrganizationDomain("Hardware Test Center");
    a.setApplicationName("NSAAcfGen");
    a.setApplicationVersion("0.9.5");
    // revision date is in the Globals class



    NSAacfGen w;
    w.show();

    return a.exec();
}
