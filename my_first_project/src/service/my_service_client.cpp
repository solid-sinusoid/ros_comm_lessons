#include "ros/ros.h"
#include "my_first_project/euler2quat.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<my_first_project::euler2quat>("p2q");
  my_first_project::euler2quat srv;

  srv.request.rpy.roll = atof(argv[1]);
  srv.request.rpy.pitch = atof(argv[2]);
  srv.request.rpy.yaw = atof(argv[3]);

  if (argc < 3)
  {
    ROS_INFO("Give your angles: r = %f p = %f y = %f", srv.request.rpy.roll, srv.request.rpy.pitch, srv.request.rpy.yaw);
    return 1;
  }
  
  if (client.call(srv))
  {
    ROS_INFO("Quat: x = %f y = %f z = %f w = %f", srv.response.xyw.z, srv.response.xyw.y, srv.response.xyw.z, srv.response.xyw.w);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
