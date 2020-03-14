#include <ros/ros.h>
#include "lx16_servo/Servo.h"
#include "std_msgs/String.h"
#include "../lx16lib/lx16driver.h"
#include "lx16_servo_node.h"



int main(int argc, char** argv)
{
    ros::init(argc,argv,"lx16_servo");
    Lx16ServoNode servoNode;
    ros::spin();
    return 0;
}

Lx16ServoNode::Lx16ServoNode()
    :m_nh()
    ,m_sub(m_nh.subscribe("servo_pos", 100, &Lx16ServoNode::servoPosCallback,this))
    ,m_driver("/dev/serial0",true)
{
    if( m_driver.isOperational() == false ){
        ROS_ERROR("Serial /dev/serial0 not available");
    }
}

void Lx16ServoNode::servoPosCallback(const lx16_servo::Servo::ConstPtr msg)
{
    ROS_INFO("Set Servo ", msg->Id, " to position ", msg->Position);
    m_driver.ServoMoveTimeWrite(msg->Id,msg->Position,100);
}
