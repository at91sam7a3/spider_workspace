#ifndef LX16_SERVO_NODE_H
#define LX16_SERVO_NODE_H


class Lx16ServoNode
{
public:
    Lx16ServoNode();
    ~Lx16ServoNode() = default;

private:
    void servoPosCallback(const spider_messages::Servo::ConstPtr msg);

private:
    ros::NodeHandle m_nh;
    ros::Subscriber m_sub;
    lx16driver m_driver;
};


#endif // LX16_SERVO_NODE_H
