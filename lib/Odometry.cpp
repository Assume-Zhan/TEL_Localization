#include "localization/Odometry.h"

#include "localization/Reset.h"

ODOMETRY* Odometry;

ODOMETRY::ODOMETRY() {
}

ODOMETRY::~ODOMETRY() {
}

void ODOMETRY::Init(ros::NodeHandle* nh_Public, ros::NodeHandle* nh_Private) {
    Data_Encoder_sub = nh_Public->subscribe("callback_vel", 1000, CallBack_Encoder);
    Data_FlowSensor_sub = nh_Public->subscribe("FlowSensor/Position", 1000, CallBack_FlowSensor);
    Data_IMU_sub = nh_Public->subscribe("imu/data", 1000, CallBack_IMU);
    Reset_Server = nh_Public->advertiseService("Localization_Reset", Callback_Reset);

    Reset();
}

void ODOMETRY::SetPosition(double x, double y, double Omega) {
    Location.PositionX = x;
    Location.PositionY = y;
    Location.PositionOmega = Omega;
}

localization::Locate* ODOMETRY::GetLocation() {
    if (DebugMode) {
        ROS_INFO("%.3lf %.3lf %.3lf", Location.PositionX, Location.PositionY, Location.PositionOmega);
    }

    return &(Location);
}

void ODOMETRY::Reset() {
    Location.PositionX = 0.0;
    Location.PositionY = 0.0;
    Location.PositionOmega = 0.0;
    Location.VelocityX = 0.0;
    Location.VelocityY = 0.0;
    Location.VelocityOmega = 0.0;

    FirstUpdate_Encoder = FirstUpdate_FlowSensor = FirstUpdate_IMU = 0;
}

// ------------------------------------------------------------
// Update Sensor Data.
// ------------------------------------------------------------
void ODOMETRY::UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg) {
    TimeCurrent_Encoder = ros::Time::now().toSec();

    if (FirstUpdate_Encoder < IgnoreFirstNData_Encoder) {
        FirstUpdate_Encoder += 1;
    } else {
        double DeltaTime = TimeCurrent_Encoder - TimeLast_Encoder;

        // NOTE : Should not use (Location) to record encoder data.
        Location.VelocityX = msg->linear.x;
        Location.VelocityY = msg->linear.y;
        Location.VelocityOmega = msg->angular.z;

        double DeltaX = Location.VelocityX * DeltaTime;
        double DeltaY = Location.VelocityY * DeltaTime;
        double DeltaOmega = Location.VelocityOmega * DeltaTime;

        Location.PositionOmega = std::max(std::min(Location.PositionOmega + DeltaOmega, 2 * M_PI), 0.0);
        Location.PositionX += DeltaX * cos(Location.PositionOmega) - DeltaY * sin(Location.PositionOmega);
        Location.PositionY += DeltaX * sin(Location.PositionOmega) + DeltaY * cos(Location.PositionOmega);
    }

    TimeLast_Encoder = TimeCurrent_Encoder;
}

void ODOMETRY::UpdateData_IMU(const sensor_msgs::Imu::ConstPtr& msg) {
    // TODO
}

void ODOMETRY::UpdateDate_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg) {
    // TODO
}

// ------------------------------------------------------------
// Callback function.
// ------------------------------------------------------------
void ODOMETRY::CallBack_IMU(const sensor_msgs::Imu::ConstPtr& msg) {
    Odometry->UpdateData_IMU(msg);
}

void ODOMETRY::CallBack_Encoder(const geometry_msgs::Twist::ConstPtr& msg) {
    Odometry->UpdateData_Encoder(msg);
}

void ODOMETRY::CallBack_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg) {
    Odometry->UpdateDate_FlowSensor(msg);
}

bool ODOMETRY::Callback_Reset(localization::Reset::Request& req, localization::Reset::Response& res) {
    Odometry->SetPosition(req.x, req.y, req.theta);
    res.isSuccess = true;
    return true;
}