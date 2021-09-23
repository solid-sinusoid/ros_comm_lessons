#include "ros/ros.h"
#include "my_first_project/euler2quat.h"

bool euler2quad(my_first_project::euler2quat::Request &req,
              my_first_project::euler2quat::Response &res)
{
  ROS_INFO("Get params: r=%f p=%f y=%f", req.rpy.roll, req.rpy.pitch, req.rpy.yaw);

  float cy = cos(req.rpy.yaw * 0.5);
  float sy = sin(req.rpy.yaw * 0.5);
  float cp = cos(req.rpy.pitch * 0.5);
  float sp = sin(req.rpy.pitch * 0.5);
  float cr = cos(req.rpy.roll * 0.5);
  float sr = sin(req.rpy.roll * 0.5);
  res.xyw.w = cr * cp * cy + sr * sp * sy;
  res.xyw.x = sr * cp * cy - cr * sp * sy;
  res.xyw.y = cr * sp * cy + sr * cp * sy;
  res.xyw.z = cr * cp * sy - sr * sp * cy;

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("p2q", euler2quad);
  ROS_INFO("Ready");
  ros::spin();

  return 0;
}