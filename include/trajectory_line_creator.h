#ifndef IMAGE_HINT_TRANSFORMER_H
#define IMAGE_HINT_TRANSFORMER_H

#include "lms/module.h"
#include "lms/math/polyline.h"
#include "street_environment/road.h"
#include "sensor_utils/car.h"
#include "trajectory_generator.h"
#include "street_environment/trajectory.h"


enum class LaneState{
    CLEAR,DANGEROUS,BLOCKED
};

class TrajectoryLineCreator : public lms::Module {

public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    street_environment::Trajectory simpleTrajectory(bool useSavety, float endVelocity);
    bool advancedTrajectory(street_environment::Trajectory &trajectory,bool rightSide, float endVelocity,float minTime,float maxTime);
    lms::ReadDataChannel<street_environment::EnvironmentObjects> envObstacles;
    lms::ReadDataChannel<street_environment::RoadStates> roadStates;
    lms::ReadDataChannel<street_environment::RoadLane> road;
    lms::ReadDataChannel<street_environment::Car> car;
    lms::WriteDataChannel<lms::math::polyLine2f> debug_trajectory;
    lms::WriteDataChannel<lms::math::polyLine2f> debug_trajectory2;
    lms::WriteDataChannel<street_environment::Trajectory> trajectory;
    TrajectoryGenerator* generator;

    // for the velocity adjustement
    float curvatureAtLargeDistancePT1 = 0;
    float alphaPT1; // between 0 and 1. if 1 only current value

    lms::math::vertex2f interpolateRoadAtDistance(const float distanceIn);
    float targetVelocity();
    int counter = 0;

    float dt = 0.01;
    float t_sinceLastUpdate = 0;

    bool obstacleInSightGlobal = false;
    bool oneTrajGenerated = false;

    float d1_last = -0.2;

    Trajectory lastResult;

    LaneState getLaneState(float tangDistance, bool rightSide,street_environment::EnvironmentObject** reason = nullptr);
};

#endif /* IMAGE_HINT_TRANSFORMER_H */
