#include "onvif_hasan/mainwindow_onvif.h"
#include "ui_mainwindow_onvif.h"
#include <QDebug>
#include <onvif_hasan/soapDeviceBindingProxy.h>
#include <onvif_hasan/soapMediaBindingProxy.h>
#include <onvif_hasan/wsseapi.h>
#include <onvif_hasan/wsaapi.h>
#include "onvif_hasan/soapH.h"
#include "onvif_hasan/soapRemoteDiscoveryBindingProxy.h"
#include "onvif_hasan/soapPTZBindingProxy.h"
#include "onvif_hasan/soapPullPointSubscriptionBindingProxy.h"
#include  "onvif_hasan/ErrorLog.h"
#include <bits/stdc++.h>
#include <QMediaPlayer>
#include <QNetworkRequest>
#include <bits/stdc++.h>
#include <QMessageBox>
#include <QFile>
using namespace std;
int ptzability=-1,src=0;
unordered_map<string,bool>mp;
int pre = 0,devider=0,ptZ=-1,first_part_finish=0;
stringstream ss ;
std::string sss;
QStringList middle_part,first_part,last_part;
map<int,QStringList>storage;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define RIGHTUPPERCORNER 8
#define RIGHTLOWERCORNER 9
#define LEFTUPPERCORNER 6
#define LEFTLOWERCORNER 7
#define ZOOMIN 4
#define ZOOMOUT 5
#define speed 1
#define sp 10
QString array[10]={"1","2"};

MainWindow_onvif::MainWindow_onvif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_onvif)
{
    int  _metadataVersion = 1;
    char* _xaddr="http://localhost/service";
    char* _type="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
    char* _scope="scope";
    char* _endpoint="urn";


    discoveryObj = new DiscoveryObj(CLIENT_MODE, _metadataVersion, _xaddr, _type, _scope, _endpoint);
    connect(discoveryObj,SIGNAL(discoveredDevice(DescDevice)) ,this,SLOT(onDiscoveredDevice(DescDevice)));
    ui->setupUi(this);

    //timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(slider_delay()));
    ui->movement_step->setStyleSheet("combobox-popup: 0;");
    ui->movement_step->clear();
    for( int i = 1 ; i<= 40 ; i++){
        ss.clear();
        sss="";
        ss<<i;
        ss>>sss;
        ui->movement_step->addItem(QString::fromStdString( sss ));
    }
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget;
    mediaPlayer->setVideoOutput(videoWidget);
    ui->horizontalLayout_3->addWidget(videoWidget);

    QPixmap pixmap("onvif_hasan/Resources/zoom-in-button.png");
    QIcon ButtonIcon(pixmap);
    ui->ZoomIn->setIcon(ButtonIcon);

    QPixmap pixmap1("onvif_hasan/Resources/zoom-out.png");
    QIcon ButtonIcon1(pixmap1);
    ui->ZoomOut->setIcon(ButtonIcon1);

    QPixmap pixmap2("onvif_hasan/Resources/left.png");
    QIcon ButtonIcon2(pixmap2);
    ui->left->setIcon(ButtonIcon2);

    QPixmap pixmap3("onvif_hasan/Resources/down.png");
    QIcon ButtonIcon3(pixmap3);
    ui->down->setIcon(ButtonIcon3);

    QPixmap pixmap4("onvif_hasan/Resources/up.png");
    QIcon ButtonIcon4(pixmap4);
    ui->up->setIcon(ButtonIcon4);

    QPixmap pixmap5("onvif_hasan/Resources/right.png");
    QIcon ButtonIcon5(pixmap5);
    ui->right->setIcon(ButtonIcon5);

    QPixmap pixmap6("onvif_hasan/Resources/left_upper.png");
    QIcon ButtonIcon6(pixmap6);
    ui->leftupper->setIcon(ButtonIcon6);

    QPixmap pixmap7("onvif_hasan/Resources/left_lower.png");
    QIcon ButtonIcon7(pixmap7);
    ui->leftlower->setIcon(ButtonIcon7);

    QPixmap pixmap8("onvif_hasan/Resources/right_upper.png");
    QIcon ButtonIcon8(pixmap8);
    ui->rightupper->setIcon(ButtonIcon8);

    QPixmap pixmap9("onvif_hasan/Resources/right_lower.png");
    QIcon ButtonIcon9(pixmap9);
    ui->rightlower->setIcon(ButtonIcon9);

    QPixmap pixmap10("onvif_hasan/Resources/circle.png");
    QIcon ButtonIcon10(pixmap10);
    ui->middle_circle->setIcon(ButtonIcon10);

    QPixmap pixmap11("onvif_hasan/Resources/up.png");
    QIcon ButtonIcon11(pixmap11);
    ui->row_up->setIcon(ButtonIcon11);

    QPixmap pixmap12("onvif_hasan/Resources/down.png");
    QIcon ButtonIcon12(pixmap12);
    ui->row_down->setIcon(ButtonIcon12);

    ui->display_video->setEnabled(false);
    //ui->pushButton_add->setEnabled(false);
    ui->pushButton_login->setEnabled(false);
    ui->label_header->setStyleSheet("QLabel{font-size: 18pt;font-weight: bold;}");
    ui->tableWidget->setColumnWidth( 0, 115 );
    ui->tableWidget->setColumnWidth( 1, 65 );
    ui->tableWidget->setColumnWidth( 2, 300 );
//    ui->ZoomIn->setAutoRepeat(true);
//    ui->ZoomOut->setAutoRepeat(true);
//    ui->up->setAutoRepeat(true);
//    ui->down->setAutoRepeat(true);
//    ui->left->setAutoRepeat(true);
//    ui->right->setAutoRepeat(true);
//    ui->rightupper->setAutoRepeat(true);
//    ui->rightlower->setAutoRepeat(true);
//    ui->leftupper->setAutoRepeat(true);
//    ui->leftlower->setAutoRepeat(true);

    ui->rightlower->setStyleSheet(
                "border: 1px solid dimgray;"
                "border-bottom-right-radius: 15px;"
                );
    ui->rightupper->setStyleSheet(
                "border: 1px solid dimgray;"
                "border-top-right-radius: 15px;"
                );
    ui->leftupper->setStyleSheet(
                "border: 1px solid dimgray;"
                "border-top-left-radius: 15px;"
                );
    ui->leftlower->setStyleSheet(
                "border: 1px solid dimgray;"
                "border-bottom-left-radius: 15px;"
                );
    ui->left->setStyleSheet(
                "border: 1px solid dimgray;"
                );
    ui->right->setStyleSheet(
                "border: 1px solid dimgray;"
                );
    ui->up->setStyleSheet(
                "border: 1px solid dimgray;"
                );
    ui->down->setStyleSheet(
                "border: 1px solid dimgray;"
                );
    ui->middle_circle->setStyleSheet(
                "border: 1px solid dimgray;"
                );

//    TemplateforSourecFile();
//    loadFromTextFile();
    ptZ=-1;
    ui->tableWidget->hideColumn(3);

    configFileData = readConfigFileData();
    getSourceInfosFromConfigFileData();

    //connect(ui->Zoom,SIGNAL(valueChanged(int)), this,SLOT(slotSetValue(int)));
}

QString MainWindow_onvif::readConfigFileData()
{
    QFile inputFile("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");
    //QFile inputFile("/home/sigmind/Pictures/sabbir/car_wiht_lp_and_recogFace_with_DBFace_branch_bkup/.HTPA-KK-1/onvif_hasan/deepstream_app_source1_peoplenet.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    QString cfgData = in.readAll();
    inputFile.close();
    return cfgData;
}

void MainWindow_onvif::getSourceInfosFromConfigFileData()
{
     int numberOfSources = getNumberOfSources();
     for(int source = 0; source < numberOfSources; source++)
     {
        QString property = "\n[source" + QString::number(source) + "]";
        int parentfirst =  configFileData.indexOf(property) + property.length();
        int parentlast = end_indexof(configFileData, parentfirst, "\n[", 0);
        QString substring = configFileData.mid(parentfirst, parentlast-parentfirst);


        QString subproperty = "\nuri=";
        QString uri = getData(substring, subproperty, parentfirst);

        ui->tableWidget->insertRow( ui->tableWidget->rowCount() );

        QRegExp rx("(\\@|\\/)");
        if(uri.contains("rtsp"))
        {
            QString ip = uri.split(rx)[3];
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(ip));
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(uri));
        }

     }
}

int MainWindow_onvif::end_indexof(QString mainString, int first, QString endString, int initial_index)
{
    int last;
    for (int i = 0; i < mainString.length(); i++) {
        if (mainString.mid(i, endString.length()) == endString and i > first) {
            last = initial_index+i+1;
            break;
        }
    }
    return last;
}

QString MainWindow_onvif::getData(QString substring, QString subproperty, int parentfirst)
{
    int first = substring.indexOf(subproperty) + subproperty.length();
    int last = end_indexof(substring, first, "\n", parentfirst);

    substring = configFileData.mid(first + parentfirst, last- first - parentfirst);

    return substring;
}



MainWindow_onvif::~MainWindow_onvif()
{
    delete ui;
}

void MainWindow_onvif::onDiscoveredDevice(DescDevice dev)
{
    for( int i = 0 ; i < dev.xAddrs.size() ; i++)
    {
        if(dev.xAddrs[i]==' ')
        {
            int sz = dev.xAddrs.size();
            dev.xAddrs.remove(i,sz-i);
            break;
        }
    }
    ui->onvifDevCB->addItem(dev.xAddrs);
    ui->pushButton_login->setEnabled(true);
}

void MainWindow_onvif::on_btnSendProb_clicked()
{
    ui->onvifDevCB->clear();
    discoveryObj->sendProb();
}
void MainWindow_onvif::on_pushButton_login_clicked()
{
    ptZ=-1;
    ui->display_video->setEnabled(false);
    m_deviceurl=QString(ui->onvifDevCB->currentText()).toStdString();

    Password = ui->pass_lineEdit->text();
    m_passwd = Password.toStdString();

    Username = ui->Username_edit->text();
    m_username = Username.toStdString();

    ui->Username_edit->clear();
    ui->pass_lineEdit->clear();

    std::string IP1 = m_deviceurl;
    ip_address = "",port="";

    for( int i = 0 ; i <(int) IP1.size() ; i++)
    {
        if(IP1[i]==':')
        {
            for( i = i+3 ; i <(int) IP1.size() ; i++)
            {
                if(IP1[i]=='/') break;
                ip_address+=IP1[i];
            }
            break;
        }
    }
    IP_add  = QString::fromStdString( ip_address );


    char ipHostName[128] = { 0 };
    strcat(ipHostName, "http://");
    strcat(ipHostName, ip_address.c_str());
    strcat(ipHostName, "/onvif/device_service");
    //std::cout<<"iphostname = "<<ipHostName<<endl;
    rtsp_url = "";
    //rtsp://192.168.0.109:554/cam/realmonitor?channel=1&subtype=0&unicast=true&proto=Onvi

    if(getRTSPUrl(ipHostName,rtsp_url)!=-1)
    {

        ptzContinuousMove(10);
        //std::cout<<"ptZ = "<<ptZ<<endl;
        ui->display_video->setEnabled(true);

        for( int i = 0 ,cnt=0; i <(int) rtsp_url.size() ; i++)
        {
            if(rtsp_url[i]==':') cnt++;
            if(cnt==2)
            {
                for( i = i+1 ;  i <(int) rtsp_url.size() ; i++)
                {
                    if(rtsp_url[i]=='/') break;
                    port+=rtsp_url[i];
                }
                break;
            }
        }
    }

    ui->lineEdit_rtsp->setText(QString::fromStdString(rtsp_url));
}


int MainWindow_onvif::getRTSPUrl(const char*mediaAddr,string&rtspUrl){
    if(mediaAddr==NULL){
        return -1;
    }
    MediaBindingProxy proxyMedia;
    proxyMedia.soap_endpoint = mediaAddr;
    soap_register_plugin(proxyMedia.soap, soap_wsse);
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, m_username.c_str(), m_passwd.c_str()))
    {
        //qDebug()<<2;
        rtspUrl = "Wrong Username or Password";
        return -1;
    }

    tt__Transport               transport;
    transport.Tunnel = NULL;
    transport.Protocol = tt__TransportProtocol__RTSP;

    tt__StreamSetup             setup;
    setup.Transport = &transport;
    setup.Stream = tt__StreamType__RTP_Unicast;

    _trt__GetStreamUri          StreamUri_req;
    _trt__GetStreamUriResponse  StreamUri_rep;

    StreamUri_req.StreamSetup = &setup;

    string profileToken;
    getProfile(mediaAddr,profileToken);
    StreamUri_req.ProfileToken = profileToken;


    int result = proxyMedia.GetStreamUri(mediaAddr, NULL, &StreamUri_req, &StreamUri_rep);
    //std::cout<<StreamUri_rep.MediaUri->Uri<<endl;
    if (SOAP_OK != result)
    {
        //qDebug()<<3;
        rtspUrl="GetStreamUri error";
        return -1;
    }
    //std::cout<<StreamUri_rep.MediaUri->Uri<<endl;
    rtspUrl = StreamUri_rep.MediaUri->Uri;
    return SOAP_OK;
}

int MainWindow_onvif::getProfile(const char*mediaAddr,string&profileToken){
    if(mediaAddr==NULL){
        return -1;
    }
    MediaBindingProxy proxyMedia;
    proxyMedia.soap_endpoint = mediaAddr;
    soap_register_plugin(proxyMedia.soap, soap_wsse);
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, m_username.c_str(), m_passwd.c_str()))
    {
        profileToken = "Wrong Username or Password";
        return -1;
    }
    _trt__GetProfiles           Profiles_req;
    _trt__GetProfilesResponse   Profiles_rep;
    int result = proxyMedia.GetProfiles(mediaAddr, NULL, &Profiles_req, &Profiles_rep);
    if (SOAP_OK != result)
    {
        profileToken="GetProfiles error.";
        return -1;
    }
    profileToken = Profiles_rep.Profiles[0]->token;
    return SOAP_OK;
}


void MainWindow_onvif::on_display_video_clicked()
{
    //ptz();
    ptzability=-1;
    //ui->pushButton_add->setEnabled(true);
    rtsp = ui->lineEdit_rtsp->text().toStdString();
    Table_rtsp = QString::fromStdString(rtsp);
    std::string username_pass = m_username+":"+m_passwd+"@";
    rtsp.insert(7,username_pass);
    RTSP = QString::fromStdString(rtsp);
    //qDebug()<<RTSP;

    const QUrl url1 = QUrl(RTSP);
    const QNetworkRequest requestRtsp1(url1);
    mediaPlayer->setMedia(requestRtsp1);
    mediaPlayer->play();
    ptzability=1;
}



int MainWindow_onvif:: DeviceInformation(char*szHostName,QString &Device_INFO)
{
    DeviceBindingProxy proxyDevice;
    proxyDevice.soap_endpoint = szHostName;
    soap_register_plugin(proxyDevice.soap, soap_wsse);
    struct soap *soap = soap_new();
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyDevice.soap, NULL, m_username.c_str(), m_passwd.c_str()))
    {
        Device_INFO = "Wrong Username or Password";
        return -1;
    }
    _tds__GetDeviceInformation *tds__GetDeviceInformation = soap_new__tds__GetDeviceInformation(soap, -1);
    _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse = soap_new__tds__GetDeviceInformationResponse(soap, -1);
    if (SOAP_OK == proxyDevice.GetDeviceInformation(tds__GetDeviceInformation, tds__GetDeviceInformationResponse))
    {
        QString Manufacturer =QString::fromStdString(tds__GetDeviceInformationResponse->Manufacturer);
        QString Model =QString::fromStdString(tds__GetDeviceInformationResponse->Model);
        QString FirmwareVersion =QString::fromStdString(tds__GetDeviceInformationResponse->FirmwareVersion);
        QString SerialNumber =QString::fromStdString(tds__GetDeviceInformationResponse->SerialNumber);
        QString HardwareId =QString::fromStdString(tds__GetDeviceInformationResponse->HardwareId);
        Device_INFO = QString("Manufacturer : "+Manufacturer+", "+"Model : "+Model+", "+"FirmwareVersion : "+FirmwareVersion+", "+
                              "SerialNumber : "+SerialNumber+", "+"HardwareId : "+HardwareId+"\n");
    }
    else
    {
        Device_INFO = "Device Information Error";
    }
    soap_destroy(soap);
    soap_end(soap);
    return 0;
}

void MainWindow_onvif::on_pushButton_add_clicked()
{
    ui->pushButton_add->setEnabled(false);
    if(mp.count(ip_address)) return;

    mp[ip_address]=true;
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    Device_INFO = "";
    char ipHostName[128] = { 0 };
    strcat(ipHostName, "http://");
    strcat(ipHostName, ip_address.c_str());
    strcat(ipHostName, "/onvif/device_service");
    DeviceInformation(ipHostName,Device_INFO);
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,3, new QTableWidgetItem(QString::number(ui->tableWidget->rowCount()-1)));
    //indx_mapping[src]=indx.size()-1;
    //ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(QString::number(src)));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(IP_add));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,1, new QTableWidgetItem(QString::fromStdString( port )));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(RTSP));
    src++;

    addCameraBlocksToConfigFile();
}



void MainWindow_onvif::on_pushButton_remove_clicked()
{
    std::set<int, std::greater<int>> selectedRows;
    auto itemList = ui->tableWidget->selectedItems();
    for (auto& item : itemList)
    {
        selectedRows.insert(item->row());
    }
    for (int row : selectedRows)
    {
        mp.erase( ui->tableWidget->item(row,0)->text().toStdString());
        remove_data.push_back(data(ui->tableWidget->item(row,0)->text(),ui->tableWidget->item(row,1)->text(),ui->tableWidget->item(row,2)->text(),ui->tableWidget->item(row,3)->text()));
        ui->tableWidget->removeRow(row);
    }

}

int MainWindow_onvif::getMediaUrl(string& mediaAddr){
    DeviceBindingProxy proxyDevice;
    proxyDevice.soap_endpoint = m_deviceurl.c_str();

    soap_register_plugin(proxyDevice.soap, soap_wsse);
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyDevice.soap, NULL, m_username.c_str(), m_passwd.c_str()))
    {
        mediaAddr = "Wrong Username or Password";
        return -1;
    }
    _tds__GetCapabilities           Bilities_req;
    _tds__GetCapabilitiesResponse   Bilities_rep;
    int result = proxyDevice.GetCapabilities(m_deviceurl.c_str(), NULL, &Bilities_req, &Bilities_rep);

    if (SOAP_OK != result)
    {
        mediaAddr="GetCapabilities error";
        return -1;
    }
    else{
        if (Bilities_rep.Capabilities == NULL || Bilities_rep.Capabilities->Media == NULL)
        {
            mediaAddr="no capability";
            return -1;
        }
    }
    mediaAddr = Bilities_rep.Capabilities->Media->XAddr;
    return SOAP_OK;
}

int MainWindow_onvif::ptzRelativeMove(/*const char* deviceAddr,*/int command)
{
    sss = QString(ui->movement_step->currentText()).toStdString();
    ss.clear();
    ss<<sss;
    ss>>devider;
    PTZBindingProxy proxyPTZ;
    proxyPTZ.soap_endpoint = m_deviceurl.c_str();

    std::string strMediaAddr;
    int result = 0;
    result = getMediaUrl(strMediaAddr);
    if (result!=SOAP_OK){
        return -1;
    }
    std::string strProfileToken;
    result = getProfile(strMediaAddr.c_str(), strProfileToken);
    if (result!=SOAP_OK){
        return -1;
    }

    soap_register_plugin(proxyPTZ.soap, soap_wsse);
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, m_username.c_str(), m_passwd.c_str()))
    {
        return -1;
    }
    _tptz__RelativeMove ptz_req;
    _tptz__RelativeMoveResponse ptz_resp;
    //memset(&ptz_req, 0x0, sizeof(ptz_req));
    //memset(&ptz_resp, 0x0, sizeof(ptz_resp));

    ptz_req.ProfileToken = strProfileToken;
    ptz_req.Speed = soap_new_tt__PTZSpeed(proxyPTZ.soap, -1);;
    //memset(ptz_req.Translation, 0x0, sizeof(tt__PTZVector));
    ptz_req.Speed->PanTilt = (struct tt__Vector2D *)soap_new_tt__Vector2D(proxyPTZ.soap, -1);
    //memset(ptz_req.Translation->PanTilt, 0x0, sizeof(tt__Vector2D));
    //std::string str="http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace";
    //ptz_req.Translation->PanTilt->space =&str;
    ptz_req.Translation = soap_new_tt__PTZVector(proxyPTZ.soap, -1);
    ptz_req.Translation->PanTilt = (struct tt__Vector2D *)soap_new_tt__Vector2D(proxyPTZ.soap, -1);
    tt__Vector1D* zoom = (struct tt__Vector1D *)soap_new_tt__Vector1D(proxyPTZ.soap, -1);
    ptz_req.Translation->Zoom = zoom;
    std::string str="http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace";
    ptz_req.Translation->PanTilt->space =&str;
    std::string str2 ="http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace";
    ptz_req.Translation->Zoom->space = &str2;
    //memset(ptz_req.Translation->Zoom, 0x0, sizeof(tt__Vector1D));
    int d=100-devider;
    //devider=10;
    //std::cout<<d<<endl;
    //devider=10;
    switch (command)
    {

    case RIGHTUPPERCORNER:
        //ptz_req.Speed->PanTilt->x = -((float)speed / 10);
        ptz_req.Translation->PanTilt->x = ((float)speed / d);
        ptz_req.Translation->PanTilt->y = ((float)speed / d);
        break;
    case RIGHTLOWERCORNER:
        //ptz_req.Speed->PanTilt->x = -((float)speed / 10);
        ptz_req.Translation->PanTilt->x = ((float)speed / d);
        ptz_req.Translation->PanTilt->y = -((float)speed / d);
        break;
    case LEFTUPPERCORNER:
        //ptz_req.Speed->PanTilt->x = -((float)speed / 10);
        ptz_req.Translation->PanTilt->x = -((float)speed / d);
        ptz_req.Translation->PanTilt->y = ((float)speed / d);
        break;
    case LEFTLOWERCORNER:
        //ptz_req.Speed->PanTilt->x = -((float)speed / 10);
        ptz_req.Translation->PanTilt->x = -((float)speed / d);
        ptz_req.Translation->PanTilt->y = -((float)speed / d);
        break;
    case LEFT:
        //ptz_req.Speed->PanTilt->x = -((float)speed / 10);
        ptz_req.Translation->PanTilt->x = -((float)speed / d);
        ptz_req.Translation->PanTilt->y = 0;
        break;
    case RIGHT:
        //ptz_req.Speed->PanTilt->x = ((float)speed / 10);
        ptz_req.Translation->PanTilt->x = ((float)speed / d);
        ptz_req.Translation->PanTilt->y = 0;
        break;
    case sp:
        ptz_req.Speed->PanTilt->x =1.0;
        //ptz_req.Translation->PanTilt->x = 0;
        ptz_req.Speed->PanTilt->y = ((float)speed / d);
        //ptz_req.Translation->PanTilt->y = ((float)speed / d);
    case UP:
        ptz_req.Translation->PanTilt->x = 0;
        //ptz_req.Speed->PanTilt->y = ((float)speed / 10);
        ptz_req.Translation->PanTilt->y = ((float)speed / d);
        break;
    case DOWN:
        ptz_req.Translation->PanTilt->x = 0;
        //ptz_req.Speed->PanTilt->y = -((float)speed / 10);
        ptz_req.Translation->PanTilt->y = -((float)speed / d);
        break;
    case ZOOMIN:
        ptz_req.Translation->Zoom->x = .00001;
        break;
    case ZOOMOUT:
        ptz_req.Translation->Zoom->x = -.00001;
        break;
    default:
        break;
    }
    if (proxyPTZ.RelativeMove(proxyPTZ.soap_endpoint,NULL,&ptz_req, &ptz_resp) == SOAP_OK)
        //std::cout<<"\nsuccess\n";
        return 0;
    else
        //std::cout<<"\nfail\n";
        return -1;
}


int MainWindow_onvif::ptzContinuousMove(/*const char* deviceAddr,*/int command)
{

    PTZBindingProxy proxyPTZ;
    proxyPTZ.soap_endpoint = m_deviceurl.c_str();

    std::string strMediaAddr;
    int result = 0;
    result = getMediaUrl(strMediaAddr);
    if (result!=SOAP_OK){
        return -1;
    }
    std::string strProfileToken;
    result = getProfile(strMediaAddr.c_str(), strProfileToken);
    if (result!=SOAP_OK){
        return -1;
    }

    soap_register_plugin(proxyPTZ.soap, soap_wsse);
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,  m_username.c_str(), m_passwd.c_str()))
    {
        return -1;
    }

    _tptz__ContinuousMove continuousMove;// = soap_new__tptz__ContinuousMove(proxyDevice.soap, -1);
    _tptz__ContinuousMoveResponse response;// = soap_new__tptz__ContinuousMoveResponse(proxyDevice.soap, -1);
    continuousMove.ProfileToken = const_cast<char *>(strProfileToken.c_str());
    tt__PTZSpeed* velocity = soap_new_tt__PTZSpeed(proxyPTZ.soap, -1);
    continuousMove.Velocity = velocity;
    tt__Vector2D* panTilt = soap_new_tt__Vector2D(proxyPTZ.soap, -1);
    continuousMove.Velocity->PanTilt = panTilt;
    std::string str="http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace";
    continuousMove.Velocity->PanTilt->space =&str;
    tt__Vector1D* zoom = soap_new_tt__Vector1D(proxyPTZ.soap, -1);
    continuousMove.Velocity->Zoom = zoom;
    //continuousMove.Velocity->PanTilt->x=optio
    switch (command)
    {
    case LEFT:
        continuousMove.Velocity->PanTilt->x = -((float)speed / 10);
        continuousMove.Velocity->PanTilt->y = 0;
        break;
    case RIGHT:
        continuousMove.Velocity->PanTilt->x = ((float)speed / 10);
        continuousMove.Velocity->PanTilt->y = 0;
        break;
    case UP:
        continuousMove.Velocity->PanTilt->x = 0;
        continuousMove.Velocity->PanTilt->y = ((float)speed / 10);
        break;
    case DOWN:
        continuousMove.Velocity->PanTilt->x = 0;
        continuousMove.Velocity->PanTilt->y = -((float)speed / 10);
        break;
    case ZOOMIN:
        continuousMove.Velocity->Zoom->x = -((float)speed / 10);
        break;
    case ZOOMOUT:
        continuousMove.Velocity->Zoom->x = -((float)speed / 10);
        break;
    default:
        ptZ=0;
        break;
    }
    //wait for test
    if (proxyPTZ.ContinuousMove(proxyPTZ.soap_endpoint,NULL,&continuousMove, &response) == SOAP_OK)
        //std::cout<<"\nsuccess\n";
        return 0;
    else
        //std::cout<<"\nfail\n";
        return -1;
}




void MainWindow_onvif::on_right_clicked()
{
    if(ptZ!=-1) ptzRelativeMove(3);
    //ptzContinuousMove(3);
}

void MainWindow_onvif::on_left_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(2);
    //ptzContinuousMove(2);
}

void MainWindow_onvif::on_down_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(1);
    //ptzContinuousMove(1);
}

void MainWindow_onvif::on_up_clicked()
{
    if(ptZ!=-1) ptzRelativeMove(0);
    //ptzContinuousMove(0);
}

void MainWindow_onvif::on_ZoomIn_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(4);
    //ptzContinuousMove(4);
}

void MainWindow_onvif::on_ZoomOut_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(5);
    //ptzContinuousMove(5);
}

void MainWindow_onvif::on_leftupper_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(6);
}

void MainWindow_onvif::on_leftlower_clicked()
{
    if(ptZ!=-1) ptzRelativeMove(7);
}

void MainWindow_onvif::on_rightupper_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(8);
}

void MainWindow_onvif::on_rightlower_clicked()
{
    cout<<"ptZ = "<<ptZ<<endl;
    if(ptZ!=-1)ptzRelativeMove(9);
}

void MainWindow_onvif::on_speed_clicked()
{
    if(ptZ!=-1)ptzRelativeMove(10);
}

//void MainWindow_onvif::loadFromTextFile()
//{
//    //QFile input_file("/home/sigmind/Pictures/sabbir/car_wiht_lp_and_recogFace_with_DBFace_branch_bkup/.HTPA-KK-1/onvif_hasan/deepstream_app_source1_peoplenet.txt");
//    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

//    if(input_file.open(QIODevice::ReadOnly)){
//        QTextStream in(&input_file);

//        int source_number = 0;
//        QString source = "[source"+QString::number(source_number)+"]";

//        while(!in.atEnd()){
//            QString line = in.readLine();

//            if(first_part_finish && line==QString("[sink0]"))
//            {
//                last_part.append(line);
//                while(!in.atEnd())
//                {
//                    line = in.readLine();
//                    last_part.append(line);
//                }
//                break;
//            }
//            if(!first_part_finish && line != source) first_part.append(line);
//            else{
//                first_part_finish=1;
//                if(line==source)
//                {
//                    src++;
//                    QStringList temp;
//                    temp.append(line);
//                    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
//                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,3, new QTableWidgetItem(QString::number(ui->tableWidget->rowCount()-1)));
//                    //indx_mapping[src]=indx.size()-1;
//                    for( int j = 1 ; j<=4 ; j++) {line = in.readLine(); temp.append(line);}
//                    int x = line.size();
//                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(line.mid(4,x-4)));
//                    string s = line.toStdString(),ip_read="", portt="";;
//                    reverse(s.begin(),s.end());
//                    while(s.size() && s.back()!='@') s.pop_back();;
//                    if(s.size() && s.back()=='@') s.pop_back();
//                    reverse(s.begin(),s.end());
//                    //rtsp://admin:bhtpa-kk@192.168.1.42/Streaming/Channels/101
//                    for( int i = 0 ; i <(int) s.size() ; i++)
//                    {
//                        if(s[i]==':')
//                        {
//                            for( i = i+1 ; i <(int) s.size() ; i++)
//                            {
//                                if(s[i]>='0' && s[i]<='9'){
//                                    portt+=s[i];
//                                }
//                                else break;
//                            }
//                            break;
//                        }
//                        else if(s[i]=='/') break;
//                        ip_read+=s[i];
//                    }
//                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,1, new QTableWidgetItem(QString::fromStdString(portt)));
//                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(QString::fromStdString( ip_read)));

//                    for( int j = 1 ; j <= 26 ; j++)  {line = in.readLine(); temp.append(line);}
//                    storage[source_number]=temp;
//                    ++source_number;
//                    source = "[source"+QString::number(source_number)+"]";

//                }
//            }
//        }
//        input_file.close();
//    }
//    qDebug()<<"first part read that means full cfg file : \n sz = "<<first_part.size()<<"\n"<<first_part;

//}

//void MainWindow_onvif::TemplateforSourecFile()
//{
//    //QFile input_file("onvif_hasan/Resources/deepstream_app_source1_peoplenet.txt");
//    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

//    if(input_file.open(QIODevice::ReadOnly)){
//        QTextStream in(&input_file);
//        QString source = "[source"+QString::number(0)+"]";
//        middle_part.append("\n");
//        while(!in.atEnd()){
//            QString line = in.readLine();
//            if(line == source){
//                middle_part.append(line);
//                for( int i = 1 ; i<=31 ; i++) {
//                    line = in.readLine();
//                    middle_part.append(line);
//                }
//                break;
//            }
//        }
//        input_file.close();
//    }
//    qDebug()<<"middle part sz : "<<middle_part.size()<<'\n'<<"allah is one and almighty :"<<endl
//           <<middle_part<<endl;
//}

void MainWindow_onvif::addCameraBlocksToConfigFile()
{
    int lastSourceNumber = getLastSourceNumberFromConfigFile();

    addSourceAfter(lastSourceNumber);
    addSinkAfter(lastSourceNumber);
}

int MainWindow_onvif::getLastSourceNumberFromConfigFile()
{
    int numberOfSources = getNumberOfSources();
    int lastSourceNumber = numberOfSources - 1;
    return lastSourceNumber;
}

int MainWindow_onvif::getNumberOfSources()
{
    QString sourcePattern = "\n[source";
    int numberOfSources = configFileData.count(sourcePattern);
    return numberOfSources;
}

void MainWindow_onvif::addSourceAfter(int lastSourceNumber)
{
    QString newSourceBlockData = generateSourceBlockAfter(lastSourceNumber);
    int lastSourceBlockEndPosition = getBlockEndPositionBefore("\n[sink0]");
    addNewBlockAt(lastSourceBlockEndPosition, newSourceBlockData);
}

void MainWindow_onvif::addSinkAfter(int lastSourceNumber)
{
    QString newSinkBlockData = generateSinkBlockAfter(lastSourceNumber);
    int lastSinkBlockEndPosition = getBlockEndPositionBefore("\n[osd]");
    addNewBlockAt(lastSinkBlockEndPosition, newSinkBlockData);
}

//    QString num = QString::number(src);

//    qDebug()<<"src number is : "<<src<<" inside addnewsource methed\n"<<middle_part<<endl;

//    for( int i = 7 , j = 0 ; j< num.size() ; i++,j++)
//    {
//        middle_part[1][i]=num[j];
//        qDebug()<<" char show: "<<middle_part[1][i]<<" "<<num[j]<<" "<<middle_part[1].size()
//               <<" "<<middle_part[1]<<endl;//2
//    }
////    qDebug()<<" after loopsds : \n"<<middle_part<<endl;

//    int sz = middle_part[1].size();
//    qDebug()<<"sz : "<<sz<<endl;
//    if(middle_part[1][sz-1]!=']')
//    {
//        middle_part[1]+=']';
//        qDebug()<<" sub str show: "<<middle_part[1]<<" "<<middle_part[1][sz-1]<<endl;
//    }
////    qDebug()<<" after if sds : \n"<<middle_part<<endl;

//    sz = middle_part[5].size();
//    //std::cout<<"sz= "<<sz<<endl;
//    sz-=4;
//    int rtsp_size = RTSP.size();
////    std::cout<<"sz= "<<sz<<" "<<rtsp_size<<endl;
//    while(sz<rtsp_size)
//    {
//        sz++;
//        middle_part[5]+='0';
//    }
//    if(sz>rtsp_size)
//    {
//        int extra = sz-rtsp_size;
//        int indx = middle_part[5].size()-extra;
//        middle_part[5].remove(indx,extra);
//    }
//    int i = 4 , j = 0 ;
//    while(rtsp_size--)
//    {
//        middle_part[5][i++]=RTSP[j++];
//    }

//    /// add sink portion
//    middle_part +="\n";
//    QString tm = "[sink"+QString::number(src)+"]";
//    middle_part +=tm;
//    middle_part +="enable=1";
//    middle_part +="#Type - 1=FakeSink 2=EglSink 3=File";
//    middle_part +="type=2";
//    middle_part +="sync=0";
//    middle_part +="source-id="+QString::number(src);
//    middle_part +="gpu-id=0";
//    middle_part +="nvbuf-memory-type=0";
//    middle_part +="\n";

//    QStringList temp = middle_part;
//    storage[src]=temp;

//    qDebug()<<"make source : size "<<middle_part.size()<<" \n"<<middle_part;
//    middle_part.clear();
//    TemplateforSourecFile();// load again basic part
//}




QString MainWindow_onvif::generateSourceBlockAfter(int lastSourceNumber)
{
    QString newBlockData;
    newBlockData.append("\n");

    QString newSource = "\n[source"+QString::number(lastSourceNumber + 1)+"]";
    newBlockData.append(newSource);
    newBlockData.append("\nenable=1");
    newBlockData.append("\n#Type - 1=CameraV4L2 2=URI 3=MultiURI 4=RTSP");
    newBlockData.append("\ntype=4");

    int lastRow = ui->tableWidget->rowCount() - 1;
    newBlockData.append("\nuri=" + ui->tableWidget->item(lastRow,2)->text());

    newBlockData.append("\nnum-sources=1");
    newBlockData.append("\ngpu-id=0");
    newBlockData.append("\ncudadec-memtype=0");

    newBlockData.append("\nsmart-record=0");
    newBlockData.append("\nsmart-rec-container=0");
    newBlockData.append("\nsmart-rec-file-prefix=watchcam");
    newBlockData.append("\nsmart-rec-dir-path=/home/sigmind/Videos/records");
    newBlockData.append("\nsmart-rec-video-cache=500");
    newBlockData.append("\nsmart-rec-duration=500");
    newBlockData.append("\nsmart-rec-start-time=300");
    newBlockData.append("\nsmart-rec-interval=0");

    newBlockData.append("\n");

    return newBlockData;
}

QString MainWindow_onvif::generateSinkBlockAfter(int lastSourceNumber)
{
    QString newBlockData;
    newBlockData.append("\n");

    QString newSink = "\n[sink"+QString::number(lastSourceNumber + 1)+"]";
    newBlockData.append(newSink);
    newBlockData.append("\nenable=1");
    newBlockData.append("\n#Type - 1=FakeSink 2=EglSink 3=File");
    newBlockData.append("\ntype=2");
    newBlockData.append("\nsync=0");
    newBlockData.append("\nsource-id=0");
    newBlockData.append("\ngpu-id=0");
    newBlockData.append("\nnvbuf-memory-type=0");

    newBlockData.append("\n");

    return newBlockData;
}

int MainWindow_onvif::getBlockEndPositionBefore(QString pattern)
{
    return configFileData.indexOf(pattern);
}

void MainWindow_onvif::addNewBlockAt(int previousBlockEndPosition, QString newBlockData)
{
    configFileData.insert(previousBlockEndPosition, newBlockData);
}

//void MainWindow_onvif::editSourceNumber(){
////    QFile input_file("onvif_hasan/Resources/deepstream_app_source1_peoplenet.txtt");
//    QFile input_file("onvif_hasan/Resources/src_add_test.txt");

//    if (!input_file.open(QFile::WriteOnly)) {
//        //qDebug() << "Error opening for write: " << input_file.errorString();
//        return;
//    }
//    QTextStream outStream(&input_file);

//    qDebug()<<"fst part sz : "<<first_part.size()<<"\n first part full str : "<<first_part<<endl;

//    for(int i = 0; i < first_part.size(); i++){
//        qDebug()<<"first part single line : "<<first_part[i];
//        outStream << first_part[i]<<"\n";
//    }

//    int row_sz = ui->tableWidget->rowCount();
//    qDebug()<<"row size : "<<row_sz;

//    for( int k = 0 ; k < row_sz ; k++ )
//    {
//        int indx = ui->tableWidget->item(k,3)->text().toInt();
//        auto &x = storage[indx];
//        QString num = QString::number(k);
//        for( int i = 7 , j = 0 ; j< num.size() ; i++,j++)
//        {
//            x[0][i]=num[j];
//            qDebug()<<"num[j] : "<<num[j]<<" x[0][i] : "<<x[0][i];
//        }
//        int sz = x[0].size();
//        qDebug()<<"x[0][sz-1] : "<<x[0][sz-1]<<" x[0] : "<<x[0];

//        if(x[0][sz-1]!=']')
//        {
//            x[0].clear();
//            qDebug()<<"not equal 3rd bracket";

////            x[0]+=']';// error issue for '2]'
//            x[0]="";// error issue for '2]'
//        }
//        outStream <<"\n";
//        qDebug()<<"x.size() : "<<x.size();
//        for( int i = 0 ; i < x.size() ; i++)
////        for( int i = 1 ; i < x.size() ; i++)
//        {
//            qDebug()<<"each line ck : "<<x[i]<<" and sz : "<<x[i].size()<<endl;
//            outStream << x[i]<<"\n";
//        }
//        outStream <<"\n";
//    }
//    for(int i = 0; i < last_part.size(); i++){
//        qDebug()<<"each line last ck : "<<last_part[i]<<endl;
//        outStream << last_part[i]<<"\n";
//    }
//    input_file.close();

//    qDebug()<<"last part that means integrated part : \n"<<" sz = "<<last_part.size()<<" \n"<<last_part;
//}

void MainWindow_onvif::on_row_up_clicked()
{
    int cur = ui->tableWidget->currentRow();
    if(cur==0) return;
    ipp = ui->tableWidget->item(cur,0)->text();
    portt = ui->tableWidget->item(cur,1)->text();
    rtspp = ui->tableWidget->item(cur,2)->text();
    indx = ui->tableWidget->item(cur,3)->text();

    ipp2 = ui->tableWidget->item(cur-1,0)->text();
    portt2 = ui->tableWidget->item(cur-1,1)->text();
    rtspp2 = ui->tableWidget->item(cur-1,2)->text();
    indx2 = ui->tableWidget->item(cur-1,3)->text();

    ui->tableWidget->setItem( cur-1,0,new QTableWidgetItem(ipp));
    ui->tableWidget->setItem( cur-1,1,new QTableWidgetItem(portt));
    ui->tableWidget->setItem( cur-1,2,new QTableWidgetItem(rtspp));
    ui->tableWidget->setItem( cur-1,3,new QTableWidgetItem(indx));

    ui->tableWidget->setItem( cur,0,new QTableWidgetItem(ipp2));
    ui->tableWidget->setItem( cur,1,new QTableWidgetItem(portt2));
    ui->tableWidget->setItem( cur,2,new QTableWidgetItem(rtspp2));
    ui->tableWidget->setItem( cur,3,new QTableWidgetItem(indx2));
    ui->tableWidget->setCurrentCell(cur-1,ui->tableWidget->currentColumn());
}

void MainWindow_onvif::on_row_down_clicked()
{
    int cur = ui->tableWidget->currentRow();
    if(cur==ui->tableWidget->rowCount()-1) return;
    ipp = ui->tableWidget->item(cur,0)->text();
    portt = ui->tableWidget->item(cur,1)->text();
    rtspp = ui->tableWidget->item(cur,2)->text();
    indx = ui->tableWidget->item(cur,3)->text();

    ipp2 = ui->tableWidget->item(cur+1,0)->text();
    portt2 = ui->tableWidget->item(cur+1,1)->text();
    rtspp2 = ui->tableWidget->item(cur+1,2)->text();
    indx2 = ui->tableWidget->item(cur+1,3)->text();

    ui->tableWidget->setItem( cur+1,0,new QTableWidgetItem(ipp));
    ui->tableWidget->setItem( cur+1,1,new QTableWidgetItem(portt));
    ui->tableWidget->setItem( cur+1,2,new QTableWidgetItem(rtspp));
    ui->tableWidget->setItem( cur+1,3,new QTableWidgetItem(indx));

    ui->tableWidget->setItem( cur,0,new QTableWidgetItem(ipp2));
    ui->tableWidget->setItem( cur,1,new QTableWidgetItem(portt2));
    ui->tableWidget->setItem( cur,2,new QTableWidgetItem(rtspp2));
    ui->tableWidget->setItem( cur,3,new QTableWidgetItem(indx2));
    ui->tableWidget->setCurrentCell(cur+1,ui->tableWidget->currentColumn());
}

void MainWindow_onvif::on_pushButton_write_clicked()
{
   // editSourceNumber();
    saveConfigFile();
}

void MainWindow_onvif::saveConfigFile()
{
    QString qPath("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

    QFile qFile(qPath);
    if (qFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&qFile); out << configFileData;
        qFile.close();
    }
}

void MainWindow_onvif::on_Undo_remove_clicked()
{
    if(remove_data.size()==0) return ;
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(remove_data.back().ip));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,1, new QTableWidgetItem(remove_data.back().port));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(remove_data.back().rtsp));
    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1,3, new QTableWidgetItem(remove_data.back().indx));
    remove_data.pop_back();
}


