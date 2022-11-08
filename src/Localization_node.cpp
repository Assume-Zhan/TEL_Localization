#include "localization/Odometry.h"

void Data_Encoder_Callback(const geometry_msgs::Twist::ConstPtr &msg);

int main(int argc, char **argv) {
    ros::init(argc, argv, "Localization_node");
    ros::NodeHandle nh;

    ros::Subscriber Data_Encoder_sub = nh.subscribe("callback_vel", 1000, Data_Encoder_Callback);

    ros::Publisher Loc_Pub = nh.advertise<geometry_msgs::Pose2D>("Localization_Position", 1000);

    ros::Rate Pub_Frequency(10);

    while (nh.ok()) {
        Loc_Pub.publish(*(Odometry.GetPosition()));

        ros::spinOnce();
        Pub_Frequency.sleep();
    }

    return 0;
}

void Data_Encoder_Callback(const geometry_msgs::Twist::ConstPtr &msg) {
    Odometry.UpdateData_Encoder(msg);
}