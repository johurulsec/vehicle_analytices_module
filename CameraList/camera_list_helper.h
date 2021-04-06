#ifndef CAMERA_LIST_HELPER_H
#define CAMERA_LIST_HELPER_H

#include <QString>
#include <QDebug>

class camera_list_helper
{
private:
    QString source_name;
    QString enable;
    QString type;
    QString uri;
    QString num_sources;
    QString gpu_id;
    QString mem_type;
    QString cuda_mem_type;

public:
    camera_list_helper();
    camera_list_helper(QString source_name, QString enable, QString type, QString uri, QString num_sources, QString gpu_id);
    camera_list_helper(QString source_name, QString enable, QString type, QString uri, QString num_sources, QString gpu_id, QString mem_type, QString cuda_mem_type);

    QString getSourceName();
    QString getEnable();
    QString getType();
    QString getUri();
    QString getNumSources();
    QString getGpuId();
    QString getMemType();
    QString getCudaMemType();

    void printCameralistHelper();

};

#endif // CAMERA_LIST_HELPER_H
