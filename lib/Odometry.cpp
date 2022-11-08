#include "localization/Odometry.h"

ODOMETRY Odometry;

void ODOMETRY::SetPosition(double x, double y, double w) {
    Position.x = x;
    Position.y = y;
    Position.theta = w;
}

geometry_msgs::Pose2D* ODOMETRY::GetPosition() {
    return &(Position);
}

void ODOMETRY::Reset() {
    Time_Last = ros::Time::now().toSec();
    Position.x = Position.y = Position.theta = 0.0;
}

void ODOMETRY::UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg) {
}