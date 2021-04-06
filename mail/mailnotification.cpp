#include "mailnotification.h"


char* MailNotification::payload_text = NULL;

/* =============== attachment =============== */

#include <cstring>
#include <iostream>
#include <stdlib.h>
//#include <curses.h>

static const int CHARS= 76;     //Sending 54 chararcters at a time with \r , \n and \0 it becomes 57
static const int ADD_SIZE= 7;   // ADD_SIZE for TO,FROM,SUBJECT,CONTENT-TYPE,CONTENT-TRANSFER-ENCODING,CONETNT-DISPOSITION and \r\n
static const int SEND_BUF_SIZE= 72;
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


void encodeblock(unsigned char in[3], unsigned char out[4], int len)
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode(FILE *infile, unsigned char *output_buf)
{
    unsigned char in[3], out[4];
    int i, len;
    *output_buf = 0;

    while(!feof(infile)) {
        len = 0;
        for(i = 0; i < 3; i++) {
            in[i] = (unsigned char) getc(infile);
            if(!feof(infile) ) {
                len++;
            }
            else {
                in[i] = 0;
            }
        }
        if(len) {
            encodeblock(in, out, len);
            strncat((char*)output_buf, (char*)out, 4);
        }
    }
}



/* =============== attachment =============== */

string MailNotification::generateRandom(){
    /* Decleration and initialization of static constant string type variable */
    static const string charList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /* srand() initialize random number generator */
    /* time() for get current time */
    srand(time(0));
    string alphanumeric = "";

    for(int i = 0; i < 23; i++) {
        /* rand() generate random number */
        alphanumeric += charList [rand() % charList.size()];
    }
    return alphanumeric;
}

void MailNotification::createFileLoad(string encoded_buf)
{
//    const char *filename = basename(path.c_str());
//    FILE* hFile=NULL;
//    hFile = fopen(path.c_str(),"rb");
//    size_t fileSize(0);

//    if(!hFile)
//    {
//        //qDebug() << path.c_str();
//        //qDebug() << "File not found!!!";
//        exit (EXIT_FAILURE);
//    }

//    fseek(hFile,0,SEEK_END);
//    fileSize = ftell(hFile);
//    fseek(hFile,0,SEEK_SET);
//    //qDebug() << "Encoding " + QString(filename) + " please be patient...";

    int no_of_rows = encoded_buf.length()/SEND_BUF_SIZE + 1;
//    int charsize = (no_of_rows*72)+(no_of_rows*2);
//    unsigned char* b64encode = new unsigned char[charsize];
//    *b64encode = 0;
//    encode(hFile, b64encode);
//    string encoded_buf = (char*)b64encode;

    int pos = 0;
    string sub_encoded_buf = "";
    for(int i = 0; i <= no_of_rows-1; i++)
    {
        sub_encoded_buf += encoded_buf.substr(pos*72,72);
        sub_encoded_buf += "\r\n";
        pos++;
    }

    string filename = "warning.png";
    string fileLoad = "";
    fileLoad.append("Content-Type: application/x-msdownload; name=\"" + filename + "\"\r\n");
    fileLoad.append("Content-Transfer-Encoding: base64\r\n");
    fileLoad.append("Content-Disposition: attachment; filename=\"" + filename + "\"\r\n");
    fileLoad.append("\r\n");
    fileLoad.append(sub_encoded_buf);

    this->attachmentLoad.push_back(fileLoad);

    //delete[] b64encode;

}

MailNotification::MailNotification(string from, string to, string subject, string message)
{
    this->from = from;
    this->to = to;
    this->subject = subject;
    this->message = message;
    this->curl = curl_easy_init();
    setUser(string("watchcam@sigmindai.net"), string("00125680")); //username, password (can be an app password) //lgstdnmpavdhkgnb
}

MailNotification::MailNotification()
{
    this->curl = curl_easy_init();
    setUser(string("watchcam@sigmindai.net"), string("00125680")); //username, password (can be an app password) //lgstdnmpavdhkgnb
}

MailNotification::~MailNotification()
{
    //curl_easy_cleanup(this->curl);
}

void MailNotification::resetParameters()
{
    this->res = CURLE_OK;
    this->recipients = NULL;
    this->upload_ctx.lines_read = 0;
    this->attachmentList.clear();
    this->attachmentLoad.clear();
    this->recipientList.clear();
//    //qDebug() << "init curl done";
}

void MailNotification::setDateAndMessageId()
{
    time_t now = time(0);
    //this->date = ctime(&now);
    tm *gmtm = gmtime(&now);
    this->date = asctime(gmtm);
    this->message_id = to_string(gmtm->tm_year + 1900) + to_string(gmtm->tm_mon +1) + to_string(gmtm->tm_mday) + to_string(gmtm->tm_hour) + to_string(gmtm->tm_min) + to_string(gmtm->tm_sec);
    this->message_id.append(".Horde.");
    this->message_id.append(generateRandom());
    this->message_id.append("@sigmindai.net");
    ////qDebug() << message_id.c_str();
}

size_t MailNotification::payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    char *data;
    char *tt = NULL;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = strchr(payload_text, '\n');

    if(data)
    {
        size_t pSize = strlen(payload_text);
        size_t dSize = strlen(data);
        size_t diff = pSize-dSize+1;
        ////qDebug() << payload_text;
        tt = (char*)malloc((diff) * sizeof(char));
        strncpy(tt, payload_text, diff);

        //tt[diff] = '\0';

        ////qDebug() << diff;

        ////qDebug() << tt;

        if(tt) {
            //size_t len = strlen(tt);
            memcpy(ptr, tt, diff);
            upload_ctx->lines_read++;
            ////qDebug() << len;
            payload_text = data + 1;
            free(tt);
            return diff;
        }
    }

    //qDebug() << "000";
    return 0;
}

void MailNotification::setUser(string username, string password)
{
    this->from = this->username = username;
    this->password = password;
    //qDebug() << "u-pass";
}

void MailNotification::setAllCurlOptions()
{
    //qDebug() << "upto start setcurloption";
    curl_easy_setopt(this->curl, CURLOPT_USERNAME, this->username.c_str()); //d2F0Y2hjYW1Ac2lnbWluZGFpLm5ldA==
    curl_easy_setopt(this->curl, CURLOPT_PASSWORD, this->password.c_str()); //MDAxMjU2ODBXYXRjaENhbQ==

    curl_easy_setopt(this->curl, CURLOPT_URL, "smtps://host15.registrar-servers.com:465");
    //qDebug() << "upto smtp";

    curl_easy_setopt(this->curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    curl_easy_setopt(this->curl, CURLOPT_MAIL_FROM, this->from.c_str());
    //qDebug() << "upto FROM";
    //qDebug() << this->to.c_str();
    this->recipients = curl_slist_append(NULL, this->to.c_str());
    //qDebug() << "upto recipient";


    if(this->recipientList.size() > 0){
        for(unsigned int i = 0; i < this->recipientList.size(); i++){
            this->recipients = curl_slist_append(this->recipients, this->recipientList.at(i).c_str());
        }
    }

    curl_easy_setopt(this->curl, CURLOPT_MAIL_RCPT, this->recipients);

    if(this->attachmentList.size() > 0){
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, strlen(payload_text));
    }

    curl_easy_setopt(this->curl, CURLOPT_READFUNCTION, this->payload_source);
    curl_easy_setopt(this->curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(this->curl, CURLOPT_UPLOAD, 1L);

    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
}

void MailNotification::sendEmail()
{
    if(myStyles::emailsTo.size()){
        //qDebug() << "mails .." << myStyles::emailsTo;
        QString em=myStyles::emailsTo.at(0);
        setTo(em.toStdString());
        for(int i=1;i<myStyles::emailsTo.size();i++){
            em= myStyles::emailsTo.at(i);
            addRecipient(em.toStdString());
        }

        cout << "tos " << to << endl;

        cout << from << " "<< to << " " << " " << subject << " " << message << endl;
        if(this->from != this->username){
            //qDebug() << "the \"from\" account and the \"username\" doesn't match";
            return;
        }

        if(this->to == "" || this->from == "" || this->subject == "" || this->message == ""){
            //qDebug() << "Either From, To, Subject or Message missing";
            return;
        }



        setDateAndMessageId();
        setPayloadText();
        //qDebug() << "before all curl opttions";
        setAllCurlOptions();
        //qDebug() << "all curl options";

        this->res = curl_easy_perform(this->curl);

        /* Check for errors */
        if(this->res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(this->res));

        /* Free the list of recipients */
        //qDebug() << "before free recipients";
        //curl_slist_free_all(this->recipients);
        //qDebug() << "after free recipients";
        resetParameters();
    }

}

void MailNotification::setFrom(string f)
{
    this->from = f;
}

void MailNotification::setTo(string t)
{
    this->to = t;
}

void MailNotification::addRecipient(string c)
{
    this->recipientList.push_back(c);
    //qDebug() << QString(c.c_str());
}

void MailNotification::setSubject(string s)
{
    this->subject = s;
}

void MailNotification::setMessage(string m)
{
    this->message = m;
}

void MailNotification::addAttachment(string path)
{
    ////qDebug() << QString(path.c_str());
    this->attachmentList.push_back(path);
}

void MailNotification::setPayloadText()
{
    payload_text = NULL;
    //string to_str = "To: <" +this->to+ ">\r\n";
    string to_str = "To: \r\n";
    string from_str = "From: <" +this->from+ ">(Watchcam)\r\n";
    //string cc_str = "Cc: <" + this->cc + ">\r\n";
    string date_str = "Date: " + this->date;
    string subject_str = "Subject: " + this->subject +"\r\n";
    string message_str = this->message + "\r\n";
    string id_str = "Message-ID: <" + this->message_id + ">\r\n";
    //qDebug() << "message";

    string xxx;
    if(this->attachmentList.size() > 0){
        for(unsigned int i = 0; i < this->attachmentList.size(); i++){
            this->createFileLoad(this->attachmentList.at(i));
        }

        xxx = date_str + to_str + from_str + id_str + subject_str;
//        if(this->cc == ""){
//            xxx = date_str + to_str + from_str + id_str + subject_str;
//        }else{
//            xxx = date_str + to_str + from_str + cc_str + id_str + subject_str;
//        }

        xxx.append("Content-Type: multipart/mixed;\r\n boundary=\"XXXXXMyBoundry\"\r\n");
        xxx.append("Mime-Version: 1.0\r\n\r\n");
        xxx.append("This is a multi-part message in MIME format.\r\n\r\n");
        xxx.append("--XXXXXMyBoundry\r\n");
        xxx.append("Content-Type: text/plain; charset=\"UTF-8\"\r\n");
        xxx.append("Content-Transfer-Encoding: quoted-printable\r\n\r\n");
        xxx.append(message_str + "\r\n");


        string fileLoadList = "";
        for(unsigned int i = 0; i < this->attachmentLoad.size(); i++){
            fileLoadList.append("--XXXXXMyBoundry\r\n");
            fileLoadList.append(this->attachmentLoad.at(i));
        }

        xxx.append(fileLoadList);
        xxx.append("--XXXXXMyBoundry\r\n");

    }else{
        to_str = "To: <" +this->to+ ">\r\n";
        xxx = date_str + to_str + from_str + id_str + subject_str + string("\r\n") + message_str;
//        if(this->cc == ""){
//            xxx = date_str + to_str + from_str + id_str + subject_str + string("\r\n") + message_str;
//        }else{
//            xxx = date_str + to_str + from_str + cc_str + id_str + subject_str + string("\r\n") + message_str;
//        }
    }


    payload_text = (char*)malloc(xxx.length()*sizeof(char*));
    strcpy(payload_text ,xxx.c_str());
    ////qDebug() << payload_text;
    //return payload_text;

}
