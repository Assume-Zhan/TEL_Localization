#include "localization/Odometry.h"

ODOMETRY Odometry;

void ODOMETRY::SetPosition(double x, double y, double w) {
    Locate_Info.PositionX = x;
    Locate_Info.PositionY = y;
    Locate_Info.Omega = w;
}

localization::Locate* ODOMETRY::GetLocateInfo() {
    return &(Locate_Info);
}

void ODOMETRY::Reset() {
    Time_Last = ros::Time::now().toSec();

    Locate_Info.PositionX = 0.0;
    Locate_Info.PositionY = 0.0;
    Locate_Info.Omega = 0.0;
}

void ODOMETRY::UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg) {
}

void ODOMETRY::UpdateDate_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg) {
}

void ODOMETRY::UpdateData_IMU(const sensor_msgs::Imu::ConstPtr& msg) {
}