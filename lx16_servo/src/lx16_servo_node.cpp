#include <ros/ros.h>
#include "lx16_servo/Servo.h"
#include "std_msgs/String.h"

void servo_pos_callback(const lx16_servo::Servo::ConstPtr msg)
{
    ROS_INFO("Set Servo ", msg->Id, " to position ", msg->Position);
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"lx16_servo");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("servo_pos", 100, servo_pos_callback);
    ros::spin();
    return 0;
}
