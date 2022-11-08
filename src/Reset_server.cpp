#include "localization/Odometry.h"
#include "localization/Reset.h"

/**
 * @brief Reset the Odometry.
 *
 * @param req If there are some parameters can't pass by launch file, use this server.
 * @param res Always return true
 */
bool Callback_Reset(localization::Reset::Request &req, localization::Reset::Response &res) {
    Odometry.Reset();
    res.isSuccess = true;
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_Reset_server");
    ros::NodeHandle nh;

    ros::ServiceServer Server = nh.advertiseService("Localization_Reset", Callback_Reset);

    ros::spin();
    return 0;
}