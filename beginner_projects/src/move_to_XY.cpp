#include<ros/ros.h>
#include<geometry_msgs/Pose2D.h>
#include<turtlesim/Pose.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
#include<cstdlib>

ros::Publisher pub;
geometry_msgs::Pose2D current ;
geometry_msgs::Pose2D desired ;
geometry_msgs::Twist cmd;
const double PI = 3.141592654;
bool task = false;

void callback(const turtlesim::Pose::ConstPtr & msg)
{
  current.x = msg->x;
  current.y = msg->y;
  current.theta = msg->theta;
}

double getdistance()
{
   return sqrt(pow(desired.y-current.y,2) + pow(desired.x-current.x,2));
}

double getangle()
{
   double x = desired.x - current.x;
   double y = desired.y - current.y;
   double theta = atan2(y,x);
   double headingError = theta - current.theta;

   return headingError;
}

void setvelocity()
{
  double distance = getdistance();
  double angle = getangle();

  if(task=true && abs(distance) > 0.1){

     if(abs(angle) > 0.1){
        cmd.linear.x = 0.0;
        cmd.angular.z = 0.5 * angle;
      }
      else{
        cmd.linear.x = 0.5 * distance;
        cmd.angular.z = 0.0;
      }
  }
  else{
    task = false;
    std::cout<<"Your goal is reached "<<std::endl<<std::endl;
    cmd.angular.z = 0.0;
    cmd.linear.x = 0.0;
  }
}

void desiredvalues()
{           
  std::cout<<std::endl;
  std::cout<<"Enter your desired x : ";
  std::cin>>desired.x;
  std::cout<<"Enter your desired y : ";
  std::cin>>desired.y;
  task = true;
}

int main(int argc, char** argv ){

    ros::init(argc, argv, "movetoxynode");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/turtle1/pose",10,callback);
    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Rate rate(10);

    while(ros::ok()){
        ros::spinOnce();
        
        if(task==false){
         desiredvalues();
        }

        setvelocity();
        pub.publish(cmd);
        std::cout<<"Your current x and y : "<<current.x <<" , "<<current.y<<std::endl;
        std::cout<<"Your desired x and y : "<<desired.x<<", "<<desired.y<<std::endl;
        std::cout<<"Your angle to goal is : "<< getangle()<<std::endl;
        rate.sleep();
    }

}