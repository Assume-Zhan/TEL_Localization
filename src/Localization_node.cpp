#include "localization/Odometry.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_node");

    // ------------------------------------------------------------
    // Setup the Ros Node.
    // ------------------------------------------------------------
    ros::NodeHandle nh("~");

    ros::Subscriber Data_Encoder_sub = nh.subscribe("/callback_vel", 1000, ODOMETRY::UpdateData_Encoder);
    ros::Subscriber Data_FlowSensor_sub = nh.subscribe("/FlowSensor/Position", 1000, ODOMETRY::UpdateDate_FlowSensor);
    ros::Subscriber Data_Imu_sub = nh.subscribe("/imu/data", 1000, ODOMETRY::UpdateData_IMU);

    ros::Publisher Loc_Pub = nh.advertise<localization::Locate>("/Localization", 1000);

    // ------------------------------------------------------------
    // Get Parameter from roslaunch.
    // ------------------------------------------------------------
    if (!nh.getParam("DebugMode", Odometry.DebugMode)) {
        Odometry.DebugMode = false;
    }

    int Param_Pub_Frequency;
    if (!nh.getParam("Frequency", Param_Pub_Frequency)) {
        Param_Pub_Frequency = 10;
    }
    ros::Rate Pub_Frequency(Param_Pub_Frequency);

    // ------------------------------------------------------------
    // Ros Loop
    // ------------------------------------------------------------
    while (nh.ok()) {
        Loc_Pub.publish(*(Odometry.GetLocateInfo()));

        ros::spinOnce();
        Pub_Frequency.sleep();
    }

    return 0;
}