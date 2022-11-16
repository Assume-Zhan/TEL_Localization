#include "localization/Reset.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_Reset_client");

    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<localization::Reset>("Localization_Reset");

    localization::Reset srv;

    if (client.call(srv)) {
        if (srv.response.isSuccess) {
            ROS_INFO("Reset Odometry success.");
        } else {
            ROS_ERROR("Fail to reset Odometry.");
        }

    } else {
        ROS_ERROR("Failed to call service : Localization_Reset");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}