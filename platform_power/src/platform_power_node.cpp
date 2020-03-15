#include <ros/ros.h>
#include "std_msgs/String.h"
#include "../../../devel/include/platform_power/LegPower.h"
#include <wiringPi.h>

void powerSwitchCallback(const platform_power::LegPowerConstPtr msg)
{
    bool on = msg->PowerToLegs;
    digitalWrite (7,on);
}

int main(int argc, char** argv)
{
    wiringPiSetup ();
    pinMode (7,OUTPUT); //Turn on power relay
    ros::init(argc,argv,"platform_power");
    ros::NodeHandle m_nh;
    ros::Subscriber m_sub = m_nh.subscribe("servo_power", 100, &powerSwitchCallback);
    ros::spin();
    return 0;
}
