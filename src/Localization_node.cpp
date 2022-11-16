#include "localization/Odometry.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_node");

    // ------------------------------------------------------------
    // Setup the Ros Node.
    // ------------------------------------------------------------
    ros::NodeHandle nh("~");

    ros::Subscriber Data_Encoder_sub = nh.subscribe("/callback_vel", 1000, ODOMETRY::CallBack_Encoder);
    ros::Subscriber Data_FlowSensor_sub = nh.subscribe("/FlowSensor/Position", 1000, ODOMETRY::CallBack_FlowSensor);
    ros::Subscriber Data_Imu_sub = nh.subscribe("/imu/data", 1000, ODOMETRY::CallBack_IMU);

    ros::Publisher Loc_Pub = nh.advertise<localization::Locate>("/Localization", 1000);

    // ------------------------------------------------------------
    // Get Parameter from roslaunch.
    // ------------------------------------------------------------
    if (!nh.getParam("DebugMode", Odometry.DebugMode)) {
        Odometry.DebugMode = false;
    }

    if (!nh.getParam("IgnoreFirstNData_Encoder", Odometry.IgnoreFirstNData_Encoder)) {
        Odometry.IgnoreFirstNData_Encoder = 1;
    }
    if (!nh.getParam("IgnoreFirstNData_IMU", Odometry.IgnoreFirstNData_IMU)) {
        Odometry.IgnoreFirstNData_IMU = 1;
    }
    if (!nh.getParam("IgnoreFirstNData_FlowSensor", Odometry.IgnoreFirstNData_FlowSensor)) {
        Odometry.IgnoreFirstNData_FlowSensor = 1;
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
        Loc_Pub.publish(*(Odometry.GetLocation()));

        ros::spinOnce();
        Pub_Frequency.sleep();
    }

    return 0;
}