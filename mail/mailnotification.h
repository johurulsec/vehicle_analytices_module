#ifndef MAILNOTIFICATION_H
#define MAILNOTIFICATION_H

#include <QDebug>
#include <curl/curl.h>
#include <iostream>
#include <ctime>
#include <string>
#include <string.h>
#include <cstddef>
#include <vector>
#include <mystyles.h>
#include <QString>

//#include <libgen.h>

using namespace std;

struct upload_status {
    int lines_read;
};


class MailNotification : public QObject
{
    Q_OBJECT

public:
    MailNotification(string from, string to, string subject, string message);
    MailNotification();
    ~MailNotification();
    string from;
    string to;
    vector <string> recipientList;
    string subject;
    string message;
    string date;
    string message_id;

    vector <string> attachmentList;
    vector <string> attachmentLoad;

    struct upload_status upload_ctx;

    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients;

    void setUser(string username, string password);



    void setFrom(string f);
    void setTo(string t);
    void addRecipient(string c);
    void setSubject(string s);
    void setMessage(string m);
    void addAttachment(string path);

public slots:
    void sendEmail();

signals:

private:
    string username;
    string password;
    static char *payload_text;

    void resetParameters();
    void setPayloadText();
    void setDateAndMessageId();

    static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
    void setAllCurlOptions();

    string generateRandom();
    void createFileLoad(string encoded_buf);


};


#endif // MAILNOTIFICATION_H
