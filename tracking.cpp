#include "tracking.h"

Tracking::Tracking(std::vector<watchcam::rectangle> &previous_frame, std::vector<watchcam::rectangle> &current_frame, std::vector<int> &next_id):
    prev_frame(previous_frame), curr_frame(current_frame), next_tracking_id(next_id)
{

}

void Tracking::let_me_sort_things_out()
{
    for(int i=0; i<prev_frame.size(); i++)
    {
        if(prev_frame[i].track_id<0)
        {
            if(prev_frame[i].is_face) prev_faces.push_back(prev_frame[i]);
            else prev_persons.push_back(prev_frame[i]);
        }
        else
        {
            prev_objs.push_back(prev_frame[i]);
        }
    }

    for(int i=0; i<curr_frame.size(); i++)
    {
        if(curr_frame[i].track_id<0)
        {
            if(curr_frame[i].is_face) current_known_faces.push_back(curr_frame[i]);
        }
        else
        {
            if(curr_frame[i].name=="face") current_unknown_faces.push_back(curr_frame[i]);
            else if(curr_frame[i].name=="person") current_unknown_persons.push_back(curr_frame[i]);
            else current_objs.push_back(curr_frame[i]);
        }
    }
}

std::vector<watchcam::rectangle> Tracking::track()
{
//    //qDebug()<<"total size: "<<curr_frame.size()<<endl;

//    for(int i=0; i<prev_frame.size(); i++)
//    {
//        //qDebug()<<"prev i: "<<i<<" name: "<<prev_frame[i].name.c_str()<<" type: "<<prev_frame[i].type<<" track id: "<<prev_frame[i].track_id<<endl;
//    }

//    for(int i=0; i<curr_frame.size(); i++)
//    {
//        //qDebug()<<"i: "<<i<<" name: "<<curr_frame[i].name.c_str()<<" type: "<<curr_frame[i].type<<" track id: "<<curr_frame[i].track_id<<endl;
//    }

    let_me_sort_things_out();
//    //qDebug()<<"cr_kn_fc: "<<current_known_faces.size()<<" cr_kn_psn: "<<current_known_persons.size()<<" cr_unkn_fc: "<<current_unknown_faces.size()<<" cr_unkn_psn: "<<current_unknown_persons.size()<<" cr_obj: "<<current_objs.size()<<endl;

    std::vector<watchcam::rectangle> rects;

    diff_frame_face_face_crossmatch(current_unknown_faces, prev_faces, current_known_faces, current_objs, rects);
    same_frame_face_person_crossmatch(current_known_faces, current_unknown_persons, current_known_persons, rects);
    diff_frame_person_person_crossmatch(current_unknown_persons, prev_persons, current_known_persons, current_objs, rects);
    same_frame_person_face_crossmatch(current_unknown_faces,current_known_persons, current_known_faces, current_objs, rects);
    diff_frame_object_object_crossmatch(current_objs, prev_objs, rects);

    for(int i=0; i<current_known_faces.size(); i++)
    {
        rects.push_back(current_known_faces[i]);
    }

    prev_faces.clear();
    prev_objs.clear();
    prev_persons.clear();

//    //qDebug()<<rects.size()<<endl;

    current_known_faces.clear();
    current_objs.clear();
    current_unknown_persons.clear();
    current_known_persons.clear();
    current_unknown_faces.clear();

//    for(int i=0; i<rects.size(); i++)
//    {
//        //qDebug()<<"i: "<<i<<" name: "<<rects[i].name.c_str()<<" type: "<<rects[i].type<<" track id: "<<rects[i].track_id<<endl;
//    }

    return rects;
}

void Tracking::same_frame_face_person_crossmatch(std::vector<watchcam::rectangle> &faces,
                                               std::vector<watchcam::rectangle> &unknown_persons,
                                               std::vector<watchcam::rectangle> &known_persons,
                                               std::vector<watchcam::rectangle> &detected)
{

//    //qDebug()<<"debug size1: "<<faces.size()<<" "<<unknown_persons.size()<<" "<<known_persons.size()<<" "<<detected.size()<<endl;
    for(int i=0; i<faces.size(); i++)
    {
        double area = faces[i].height*faces[i].width;
        double max_intersection = 0.0;
        int max_match = -1;
        for(int j=0; j<unknown_persons.size(); j++)
        {
            double intersection = faces[i].intersection_with(unknown_persons[j]);
            if(intersection > max_intersection)
            {
//                //qDebug()<<"j: "<<j<<endl;
//                //qDebug()<<"face box: t:"<<faces[i].top<<" b: "<<faces[i].bot<<" l: "<<faces[i].left<<" r: "<<faces[i].right<<endl;
//                //qDebug()<<"person box: t:"<<unknown_persons[j].top<<" b: "<<unknown_persons[j].bot<<" l: "<<unknown_persons[j].left<<" r: "<<unknown_persons[j].right<<endl;
                max_intersection = intersection;
                max_match = j;
            }
        }
//        //qDebug()<<"deeebug: "<<max_match<<" "<<max_intersection<<endl;
        if(max_match!=-1 && max_intersection/area>=HUMAN_FACE_AREA_ACCEPTANCE_PERCENTAGE)
        {
//            //qDebug()<<"max match: "<<max_match<<endl;
            unknown_persons[max_match].track_id = -1;
            unknown_persons[max_match].name = faces[i].name;
            detected.push_back(unknown_persons[max_match]);
            known_persons.push_back(unknown_persons[max_match]);
            unknown_persons.erase(unknown_persons.begin() + max_match);
        }
    }
//    //qDebug()<<"detected size1: "<<detected.size()<<endl;
}

void Tracking::diff_frame_face_face_crossmatch(std::vector<watchcam::rectangle> &faces_curr,
                                             std::vector<watchcam::rectangle> &faces_prev,
                                             std::vector<watchcam::rectangle> &faces_curr_known,
                                             std::vector<watchcam::rectangle> &objects_curr,
                                             std::vector<watchcam::rectangle> &detected)
{

    for(int i=0; i<faces_prev.size(); i++)
    {
        double area = faces_prev[i].height*faces_prev[i].width;
        double max_intersection = 0.0;
        int max_match = -1;
        bool face_exist = false;

        for(int j=0; j<faces_curr_known.size(); j++)
        {
            if(faces_prev[i].name== faces_curr_known[j].name)
            {
                face_exist = true;
                break;
            }
        }
        if(face_exist) continue;

        for(int j=0; j<faces_curr.size(); j++)
        {
            double intersection = faces_prev[i].intersection_with(faces_curr[j]);
            if(intersection > max_intersection)
            {
                max_intersection = intersection;
                max_match = j;
            }
        }
        if(max_match!=-1 && max_intersection/area>=TRACKING_AREA_ACCEPTANCE_PERCENTAGE)
        {
            faces_curr[max_match].track_id = -1;
            faces_curr[max_match].name = faces_prev[i].name;
            detected.push_back(faces_curr[max_match]);
            faces_curr_known.push_back(faces_curr[max_match]);
            faces_curr.erase(faces_curr.begin() + max_match);
        }
    }
//    for(int i=0; i<faces_curr.size(); i++)
//    {
//        objects_curr.push_back(faces_curr[i]);
//    }
//    //qDebug()<<"detected size2: "<<detected.size()<<endl;
}

void Tracking::same_frame_person_face_crossmatch(std::vector<watchcam::rectangle> &unknown_faces,
                                       std::vector<watchcam::rectangle> &known_persons,
                                       std::vector<watchcam::rectangle> &known_faces,
                                       std::vector<watchcam::rectangle> &objects_curr,
                                       std::vector<watchcam::rectangle> &detected)
{

    for(int i=0; i<known_persons.size(); i++)
    {
        double area = 1;
        double max_intersection = 0.0;
        int max_match = -1;
        bool face_exist = false;

        for(int j=0; j<known_faces.size(); j++)
        {
            if(known_persons[i].name== known_faces[j].name)
            {
                face_exist = true;
                break;
            }
        }
        if(face_exist) continue;

        for(int j=0; j<unknown_faces.size(); j++)
        {
            double intersection = known_persons[i].intersection_with(unknown_faces[j]);
            if(intersection > max_intersection)
            {
                max_intersection = intersection;
                max_match = j;
                area = unknown_faces[j].height*unknown_faces[j].width;
            }
        }
        if(max_match!=-1 && max_intersection/area>=HUMAN_FACE_AREA_ACCEPTANCE_PERCENTAGE)
        {
            unknown_faces[max_match].track_id = -1;
            unknown_faces[max_match].name = known_persons[i].name;
            detected.push_back(unknown_faces[max_match]);
            unknown_faces.erase(unknown_faces.begin() + max_match);
        }
    }

    for(int i=0; i<unknown_faces.size(); i++)
    {
        objects_curr.push_back(unknown_faces[i]);
    }

//    //qDebug()<<"detected size3: "<<detected.size()<<endl;
}

void Tracking::diff_frame_person_person_crossmatch(std::vector<watchcam::rectangle> &persons_curr_unknown,
                                                 std::vector<watchcam::rectangle> &persons_prev,
                                                 std::vector<watchcam::rectangle> &persons_curr_known,
                                                 std::vector<watchcam::rectangle> &objects_curr,
                                                 std::vector<watchcam::rectangle> &detected)
{

//    //qDebug()<<"detected size4: "<<persons_curr_unknown.size()<<" "<< persons_prev.size()<<" "<< objects_curr.size()<<" "<<detected.size()<<endl;

    for(int i=0; i<persons_prev.size(); i++)
    {
        double area = persons_prev[i].height*persons_prev[i].width;
        double max_intersection = 0.0;
        int max_match = -1;
        bool face_exist = false;

        for(int j=0; j<persons_curr_known.size(); j++)
        {
            if(persons_prev[i].name== persons_curr_known[j].name)
            {
                face_exist = true;
                break;
            }
        }
        if(face_exist) continue;

        for(int j=0; j<persons_curr_unknown.size(); j++)
        {
            double intersection = persons_prev[i].intersection_with(persons_curr_unknown[j]);
            if(intersection > max_intersection)
            {
                max_intersection = intersection;
                max_match = j;
            }
        }
        if(max_match!=-1 && max_intersection/area>=TRACKING_AREA_ACCEPTANCE_PERCENTAGE)
        {
            persons_curr_unknown[max_match].track_id = -1;
            persons_curr_unknown[max_match].name = persons_prev[i].name;
            detected.push_back(persons_curr_unknown[max_match]);
            persons_curr_known.push_back(persons_curr_unknown[max_match]);
            persons_curr_unknown.erase(persons_curr_unknown.begin() + max_match);
        }
    }
    for(int i=0; i<persons_curr_unknown.size(); i++)
    {
        objects_curr.push_back(persons_curr_unknown[i]);
    }
//    //qDebug()<<"detected size4: "<<persons_curr_unknown.size()<<" "<< persons_prev.size()<<" "<< objects_curr.size()<<" "<<detected.size()<<endl;
}

void Tracking::diff_frame_object_object_crossmatch(std::vector<watchcam::rectangle> &objects_curr,
                                                 std::vector<watchcam::rectangle> &objects_prev,
                                                 std::vector<watchcam::rectangle> &detected)
{
    for(int i=0; i<objects_prev.size(); i++)
    {
        double area = objects_prev[i].height*objects_prev[i].width;
        double max_intersection = 0.0;
        int max_match = -1;
        for(int j=0; j<objects_curr.size(); j++)
        {
            if(objects_curr[j].type != objects_prev[i].type) continue;
            double intersection = objects_prev[i].intersection_with(objects_curr[j]);
            if(intersection > max_intersection)
            {
                max_intersection = intersection;
                max_match = j;
            }
        }
        if(max_match!=-1 && max_intersection/area>=TRACKING_AREA_ACCEPTANCE_PERCENTAGE)
        {
            objects_curr[max_match].track_id = objects_prev[i].track_id;
            objects_curr[max_match].name = objects_prev[i].name;
            detected.push_back(objects_curr[max_match]);
            objects_curr.erase(objects_curr.begin() + max_match);
        }
    }

    for(int i=0; i<objects_curr.size(); i++)
    {
        while(next_tracking_id.size()<=objects_curr[i].type) next_tracking_id.push_back(0);
        objects_curr[i].track_id = next_tracking_id[objects_curr[i].type]++;
        detected.push_back(objects_curr[i]);
    }
//    //qDebug()<<"detected size5: "<<objects_curr.size()<<" "<<objects_prev.size()<<" "<<detected.size()<<endl;
}
