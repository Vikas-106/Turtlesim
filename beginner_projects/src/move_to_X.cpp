#include<ros/ros.h>
#include<geometry_msgs/Pose2D.h>
#include<turtlesim/Pose.h>
#include<geometry_msgs/Twist.h>

geometry_msgs::Pose2D current , desired;
ros::Publisher pub;
geometry_msgs::Twist cmd;

void callback(const turtlesim::Pose::ConstPtr &msg)
{
   current.x=msg->x;
}

double getdistance()
{
    return desired.x - current.x;
}

void setvelocity()
{ 
 
    double value = getdistance();
    if (abs(value) > 0.01)
    {
       cmd.linear.x=value;
    }
    else{
        cmd.linear.x =0;
    }
}

int main(int argc, char** argv){
    ros::init(argc, argv,"movetox_node");
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("/turtle1/pose",10,callback);
    std::cout<<"Enter your desired X location : ";
    std::cin >> desired.x;
    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        setvelocity();
        pub.publish(cmd);
        std::cout<<"Current x : "<<current.x <<std::endl;
        std::cout<<"desired X : "<<desired.x <<std::endl;
        std::cout<<"distance to x : "<<getdistance()<<std::endl;
        rate.sleep();
    }

}