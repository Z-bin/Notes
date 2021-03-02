#include <QDebug>
#include <iostream>
#include <vector>

#include "networkmanager/networking.h"
#include "networkmanager/networkmodelitem.h"

int main(int argc, char *argv[])
{
    Networking *net = new Networking;
    qDebug() << net->isEnabled() << net->isWirelessEnabled();

    NetworkModelItem *netItem = new NetworkModelItem;
    return 0;
}
