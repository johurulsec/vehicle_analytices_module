#include "camera_list_helper.h"

camera_list_helper::camera_list_helper(){

}

camera_list_helper::camera_list_helper(QString source_name, QString enable, QString type, QString uri, QString num_sources, QString gpu_id)
{
    this->source_name = source_name;
    this->enable = enable;
    this->type = type;
    this->uri = uri;
    this->num_sources = num_sources;
    this->gpu_id = gpu_id;

}

camera_list_helper::camera_list_helper(QString source_name, QString enable, QString type, QString uri, QString num_sources, QString gpu_id, QString mem_type, QString cuda_mem_type)
{
    this->source_name = source_name;
    this->enable = enable;
    this->type = type;
    this->uri = uri;
    this->num_sources = num_sources;
    this->gpu_id = gpu_id;
    this->mem_type = mem_type;
    this->cuda_mem_type = cuda_mem_type;
}

QString camera_list_helper::getSourceName(){
    return source_name;
}

QString camera_list_helper::getEnable(){
    return enable;
}

QString camera_list_helper::getType(){
    return type;
}

QString camera_list_helper::getUri(){
    return uri;
}

QString camera_list_helper::getNumSources(){
    return num_sources;
}

QString camera_list_helper::getGpuId(){
    return gpu_id;
}

QString camera_list_helper::getMemType(){
    return mem_type;
}

QString camera_list_helper::getCudaMemType(){
    return cuda_mem_type;
}

void camera_list_helper::printCameralistHelper()
{
    ////qDebug()<< "Hello" << this->source_name << endl;
}
