#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "localization/Locate.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

class ODOMETRY {
   public:
    static void UpdateData_IMU(const sensor_msgs::Imu::ConstPtr& msg);
    static void UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg);
    static void UpdateData_Lidar();
    static void UpdateDate_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg);

    void SetPosition(double x, double y, double w);
    localization::Locate* GetLocateInfo();

    void Reset();

    bool DebugMode;

   private:
    double Time_Last;
    localization::Locate Locate_Info;

    double x_offset;
    double y_offset;
    double w_offset;

    double Encoder_Time_Before;
    double Encoder_Time_After;
};

extern ODOMETRY Odometry;

#endif