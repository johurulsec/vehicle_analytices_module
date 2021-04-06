#include <iostream>
//#include "device.h"
#include <QDebug>

#include "probing.h"
#include <QObject>


probing::probing(QObject *parent) : QObject (parent)
{
    qDebug() << "Started probing ............ ";

    int  _metadataVersion = 1;
    char* _xaddr="http://localhost/service";
    char* _type="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
    char* _scope="scope";
    char* _endpoint="urn";
    discoveryObj = new DiscoveryObj(CLIENT_MODE, _metadataVersion, _xaddr, _type, _scope, _endpoint);
    connect(discoveryObj,SIGNAL(discoveredDevice(DescDevice)) ,this,SLOT(onDiscoveredDevice(DescDevice)));



    qDebug() << "\n**********************Prob send********************";
    //ui->onvifDevCB->clear();
    discoveryObj->sendProb();
}

void probing::onDiscoveredDevice(DescDevice dev)
{


    qDebug() << "\n**********************On dev found********************";
    qDebug() << "Dev found = " << dev.xAddrs;
    qDebug() << "Dev found scope = " << dev.scopes;


//    QString name;
//    char * pch = strstr((char*)dev.scopes.toStdString().data(), "OnvifVideoServer");
//    if(pch > NULL){
//        name = "OnvifVideoServer";
//    }
    //ui->onvifDevCB->addItem(dev.xAddrs + " " + name, QVariant::fromValue(dev));

   // ui->onvifDevCB->addItem(dev.xAddrs + " " + dev.scopes, QVariant::fromValue(dev));
  }

