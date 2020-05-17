#include <ros/ros.h>
#include "../../../devel/include/spider_messages/Servo.h"
#include "../../../devel/include/spider_messages/LegPower.h"
#include "std_msgs/String.h"
#include "../lx16lib/lx16driver.h"
#include <wiringPi.h>
#include <vector>

struct servoCommand
{
    int id;
    int position;
};

std::vector<servoCommand> commands;

void powerSwitchCallback(const spider_messages::LegPowerConstPtr msg)
{
    bool on = msg->PowerToLegs;
    digitalWrite (7,on);
}

void servoPosCallback(const spider_messages::Servo::ConstPtr msg)
{
    ROS_INFO("Set Servo ", msg->Id, " to position ", msg->Position);
    servoCommand c = {msg->Id,msg->Position};
    commands.push_back(c);
}

int main(int argc, char** argv)
{
    wiringPiSetup ();
    pinMode (7,OUTPUT); //Turn on power relay

    ros::init(argc,argv,"lx16_servo");
    ros::NodeHandle m_nh;
    ros::Subscriber power_sub = m_nh.subscribe("servo_power", 100, &powerSwitchCallback);
    ros::Subscriber position_sub =  m_nh.subscribe("servo_pos", 100, &servoPosCallback);
    digitalWrite (7,true);
    lx16driver m_driver("/dev/serial0",true);
    if( m_driver.isOperational() == false ){
        ROS_ERROR("Serial /dev/serial0 not available");
    }

    ros::Rate r(100); // 100 hz
    while (ros::ok())
    {
        if(commands.size() > 0)
        {
            servoCommand s = commands[commands.size()-1];
            commands.pop_back();
            m_driver.ServoMoveTimeWrite(s.id,s.position,100);
        }
        ros::spinOnce();
        r.sleep();
    }
    digitalWrite (7,false);
    return 0;
}
