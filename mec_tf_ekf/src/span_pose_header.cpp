#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry msg_OUT;

void odomCallback(const nav_msgs::Odometry& msg_IN){
  msg_OUT = msg_IN;
  msg_OUT.header.frame_id = "UTM";

  return;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_pose_ekf_geometry_to_odom");
  
  ros::NodeHandle node;

  ros::Subscriber sub = node.subscribe("span/pose", 1000, odomCallback);
  ros::Publisher pub = node.advertise<nav_msgs::Odometry>("span/pose_remapped", 1000);
  ros::Rate loop_rate(100);
  while(ros::ok())
  {
  	pub.publish(msg_OUT);
  	ros::spinOnce();
  	loop_rate.sleep();
  }
  
  return 0;
};