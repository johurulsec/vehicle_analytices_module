#include "uniquefacewidget.h"
#include "ui_uniquefacewidget.h"

uniqueFaceWidget::uniqueFaceWidget(QString, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uniqueFaceWidget)
{
    ui->setupUi(this);
//    this->setStyleSheet("border: 8px solid rgb(0, 0, 0);");
    this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(51, 255, 51); ");//blue
    uniq_list.clear();
    list_u.clear();
    //qDebug()<<"uniqe_face_widget constructor here";
    ck=4;

    box_layout_cam_list = new QVBoxLayout(this);
    //ui->scrollAreaWidgetContents->setLayout(box_layout_cam_list);
    grid_uniq_faces = new QGridLayout; // Initialize Grid Layout
    ui->scrollAreaWidgetContents->setLayout(grid_uniq_faces);

}

uniqueFaceWidget::~uniqueFaceWidget()
{
    //qDebug()<<"destr unique_face_widget";
    uniq_list.clear();
    for(int i =0;i<uniq_list.size(); i++){
        delete uniq_list.at(i);
    }
    list_u.clear();
    delete ui;
}

void uniqueFaceWidget::setLabelForShowMaskDis(QString data)
{
    //ui->label_show_not_wearing_masks_or_violating_distance_rule->setText(data);
}

void uniqueFaceWidget::u_addNot(faceUniq *noti)
{
    qDebug()<<"u_addNot call for bottom notif "<<uniq_list.size();

    if (uniq_list.size() < 10){// Checked size of list is 100 or not!
        qDebug()<<"uniq_faceList less than 5";
        uniq_list.push_back(noti); // Added face in Lists
        grid_uniq_faces->addWidget(noti, 0, column_index_u); // load data into grid layout.

    }else {
        qDebug()<<"face list greater than 100";
        delete uniq_list.at(0); // deallocation done
        uniq_list.removeFirst(); // remove first element
        uniq_list.push_back(noti); // face added into list

        QListIterator<faceUniq*> iter(uniq_list); // iterator
        iter.toFront(); // iterator start from first


        // set face into grid layout which are new come
        for (int i = 0; i < 1; ++i){
            for (int j = 0; j < 10; ++j){
                // for 100 cell
                grid_uniq_faces->addWidget(iter.next(), i, j); // load data into grid layout.
            }

        }

    }
    //  Grid index customize
    if(column_index_u == 10){
        //qDebug()<<"colum index equal 10";
        column_index_u = -1;
    }
    column_index_u++;

    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());

}

