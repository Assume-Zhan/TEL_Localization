#include "localization/Odometry.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "Localization_node");

    // ------------------------------------------------------------
    // Setup the Ros Node.
    // ------------------------------------------------------------
    ros::NodeHandle nh("~");

    ros::Publisher Loc_Pub = nh.advertise<localization::Locate>("/Localization", 1000);

    Odometry = new ODOMETRY();

    Odometry->Init(&nh);

    // ------------------------------------------------------------
    // Get Parameter from roslaunch.
    // ------------------------------------------------------------
    if(!nh.getParam("DebugMode", Odometry->DebugMode)){
        Odometry->DebugMode = false;
    }

    if(!nh.getParam("IgnoreFirstNData_Encoder", Odometry->IgnoreFirstNData_Encoder)){
        Odometry->IgnoreFirstNData_Encoder = 1;
    }
    if(!nh.getParam("IgnoreFirstNData_IMU", Odometry->IgnoreFirstNData_IMU)){
        Odometry->IgnoreFirstNData_IMU = 1;
    }
    if(!nh.getParam("IgnoreFirstNData_FlowSensor", Odometry->IgnoreFirstNData_FlowSensor)){
        Odometry->IgnoreFirstNData_FlowSensor = 1;
    }

    int Param_Pub_Frequency;
    if(!nh.getParam("Frequency", Param_Pub_Frequency)){
        Param_Pub_Frequency = 10;
    }
    ros::Rate Pub_Frequency(Param_Pub_Frequency);

    // ------------------------------------------------------------
    // Ros Loop
    // ------------------------------------------------------------
    while(nh.ok()){
        Loc_Pub.publish(*(Odometry->GetLocation()));

        // ROS_INFO("%lf %lf %lf", Odometry->GetLocation()->PositionX, Odometry->GetLocation()->PositionY, Odometry->GetLocation()->PositionOmega);

        ros::spinOnce();
        Pub_Frequency.sleep();
    }

    delete Odometry;

    return 0;
}