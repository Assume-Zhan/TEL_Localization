#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

class ODOMETRY {
   public:
    void UpdateData_IMU();
    void UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg);
    void UpdateData_Lidar();
    void UpdateDate_Flowsensor();

    void SetPosition(double x, double y, double w);
    geometry_msgs::Pose2D* GetPosition();

    void Reset();

   private:
    double Time_Last;
    geometry_msgs::Pose2D Position;

    double x_offset;
    double y_offset;
    double w_offset;

    double Encoder_Time_Before;
    double Encoder_Time_After;
};

extern ODOMETRY Odometry;

void DataCallback_IMU();
void DataCallback_Encoder();
void DataCallback_Lidar();
void DataCallBack_Flowsensor();

#endif