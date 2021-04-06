#ifndef TRACKING_H
#define TRACKING_H

#include "rectangle.h"
#include <QDebug>

class Tracking
{
public:
    std::vector<int> &next_tracking_id;
    std::vector<watchcam::rectangle> &prev_frame;
    std::vector<watchcam::rectangle> &curr_frame;
    std::vector<watchcam::rectangle> prev_faces, prev_persons, prev_objs, current_known_faces, current_unknown_faces, current_known_persons, current_unknown_persons, current_objs;

    float HUMAN_FACE_AREA_ACCEPTANCE_PERCENTAGE = .9;
    float TRACKING_AREA_ACCEPTANCE_PERCENTAGE = .6;
    float CENTER_DISTANCE_ACCEPTANCE_PERCENTAGE = .0000;

    Tracking(std::vector<watchcam::rectangle> &previous_frame, std::vector<watchcam::rectangle> &current_frame, std::vector<int> &next_id);

    void same_frame_face_person_crossmatch(std::vector<watchcam::rectangle> &faces,
                                           std::vector<watchcam::rectangle> &unknown_persons,
                                           std::vector<watchcam::rectangle> &known_persons,
                                           std::vector<watchcam::rectangle> &detected);

    void same_frame_person_face_crossmatch(std::vector<watchcam::rectangle> &unknown_faces,
                                           std::vector<watchcam::rectangle> &known_persons,
                                           std::vector<watchcam::rectangle> &known_faces,
                                           std::vector<watchcam::rectangle> &objects_curr,
                                           std::vector<watchcam::rectangle> &detected);

    void diff_frame_face_face_crossmatch(std::vector<watchcam::rectangle> &faces_curr,
                                         std::vector<watchcam::rectangle> &faces_prev,
                                         std::vector<watchcam::rectangle> &faces_curr_known,
                                         std::vector<watchcam::rectangle> &objects_curr,
                                         std::vector<watchcam::rectangle> &detected);

    void diff_frame_person_person_crossmatch(std::vector<watchcam::rectangle> &persons_curr_unknown,
                                             std::vector<watchcam::rectangle> &persons_prev,
                                             std::vector<watchcam::rectangle> &persons_curr_known,
                                             std::vector<watchcam::rectangle> &objects_curr,
                                             std::vector<watchcam::rectangle> &detected);

    void diff_frame_object_object_crossmatch(std::vector<watchcam::rectangle> &objects_curr,
                                             std::vector<watchcam::rectangle> &objects_prev,
                                             std::vector<watchcam::rectangle> &detected);

    void let_me_sort_things_out();

    std::vector<watchcam::rectangle> track();
};

#endif // TRACKING_H
