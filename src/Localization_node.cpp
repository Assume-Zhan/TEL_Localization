#include "localization/Odometry.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_node");

    // ------------------------------------------------------------
    // Setup the Ros Node.
    // ------------------------------------------------------------
    ros::NodeHandle nh_Public;
    ros::NodeHandle nh_Private("~");

    // ------------------------------------------------------------

    ros::Publisher Loc_Pub = nh_Public.advertise<localization::Locate>("Localization", 1000);

    Odometry = new ODOMETRY();

    Odometry->Init(&nh_Public, &nh_Private);

    // ------------------------------------------------------------
    // Get Parameter from roslaunch.
    // ------------------------------------------------------------
    if (!nh_Private.getParam("DebugMode", Odometry->DebugMode)) {
        Odometry->DebugMode = false;
    }

    if (!nh_Private.getParam("IgnoreFirstNData_Encoder", Odometry->IgnoreFirstNData_Encoder)) {
        Odometry->IgnoreFirstNData_Encoder = 1;
    }
    if (!nh_Private.getParam("IgnoreFirstNData_IMU", Odometry->IgnoreFirstNData_IMU)) {
        Odometry->IgnoreFirstNData_IMU = 1;
    }
    if (!nh_Private.getParam("IgnoreFirstNData_FlowSensor", Odometry->IgnoreFirstNData_FlowSensor)) {
        Odometry->IgnoreFirstNData_FlowSensor = 1;
    }

    int Param_Pub_Frequency;
    if (!nh_Private.getParam("Frequency", Param_Pub_Frequency)) {
        Param_Pub_Frequency = 100;
    }
    ros::Rate Pub_Frequency(Param_Pub_Frequency);

    // ------------------------------------------------------------
    // Ros Loop
    // ------------------------------------------------------------
    while (nh_Private.ok()) {
        Loc_Pub.publish(*(Odometry->GetLocation()));

        ros::spinOnce();
        Pub_Frequency.sleep();
    }

    delete Odometry;

    return 0;
}