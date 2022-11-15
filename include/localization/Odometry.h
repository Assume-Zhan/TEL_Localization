#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_

#include <cmath>

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "localization/Locate.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

class ODOMETRY {
   public:
    ODOMETRY();
    ~ODOMETRY();

    static void CallBack_IMU(const sensor_msgs::Imu::ConstPtr& msg);
    static void CallBack_Encoder(const geometry_msgs::Twist::ConstPtr& msg);
    static void CallBack_Lidar();
    static void CallBack_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg);

    void SetPosition(double x, double y, double Omega);
    localization::Locate* GetLocation();

    void Reset();

    bool DebugMode;
    int Param_IgnoreFirstNData_Encoder;
    int Param_IgnoreFirstNData_IMU;
    int Param_IgnoreFirstNData_FlowSensor;

    double x_offset;
    double y_offset;
    double w_offset;

   private:
    void UpdateData_IMU(const sensor_msgs::Imu::ConstPtr& msg);
    void UpdateData_Encoder(const geometry_msgs::Twist::ConstPtr& msg);
    void UpdateData_Lidar();
    void UpdateDate_FlowSensor(const geometry_msgs::Pose2D::ConstPtr& msg);

    localization::Locate Location;

    double TimeLast_Encoder;
    double TimeLast_FlowSensor;
    double TimeLast_IMU;

    double TimeCurrent_Encoder;
    double TimeCurrent_FlowSensor;
    double TimeCurrent_IMU;

    int FirstUpdate_Encoder;
    int FirstUpdate_FlowSensor;
    int FirstUpdate_IMU;
};

extern ODOMETRY Odometry;

#endif