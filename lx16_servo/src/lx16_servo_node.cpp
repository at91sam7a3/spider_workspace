#include <ros/ros.h>
#include "../../../devel/include/spider_messages/Servo.h"
#include "../../../devel/include/spider_messages/LegPower.h"
#include "std_msgs/String.h"
#include "../lx16lib/lx16driver.h"
#include <wiringPi.h>

lx16driver m_driver("/dev/serial0",true);



void powerSwitchCallback(const spider_messages::LegPowerConstPtr msg)
{
    bool on = msg->PowerToLegs;
    digitalWrite (7,on);
}

void servoPosCallback(const spider_messages::Servo::ConstPtr msg)
{
    m_driver.ServoMoveTimeWrite(msg->Id,msg->Position,100);
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"lx16_servo");

    ros::NodeHandle m_nh;

    ros::Duration(0.1).sleep();

    wiringPiSetup ();
    pinMode (7,OUTPUT); //Turn on power relay
    digitalWrite (7,true);
    ros::Duration(0.1).sleep();
    if( m_driver.isOperational() == false ){
        ROS_ERROR("Serial /dev/serial0 not available");
    }
    m_driver.ServoVoltageRead(0);



    ros::Subscriber power_sub = m_nh.subscribe("servo_power", 100, &powerSwitchCallback);
    ros::Subscriber position_sub =  m_nh.subscribe("servo_pos", 100, &servoPosCallback);
    ros::Rate r(100); // 100 hz
    while (ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
    digitalWrite (7,false);
    return 0;
}
