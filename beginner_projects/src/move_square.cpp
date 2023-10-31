#include<ros/ros.h>
#include<geometry_msgs/Twist.h>

double length , speed ;
geometry_msgs::Twist cmd;
ros::Publisher pub;
bool flag = false;
bool task = false;

void Input()
{
   std::cout<<"Enter your length of the square : ";
   std::cin>>length;
   std::cout<<std::endl;
   speed = length;
   flag = true ;
}

void rotate()
{
    cmd.angular.z = speed;
    double dist = 0;
    double t3 = ros::Time::now().toSec();
    while (dist < M_PI/2)
    {
        pub.publish(cmd);
        double t4 = ros::Time::now().toSec();
        dist = speed * abs(t4 - t3);
        
    }
 
    cmd.angular.z = 0.0;
    pub.publish(cmd);

    
}

void moveline()
{
    cmd.linear.x = speed;
    double distance = 0;
    double t1 = ros::Time::now().toSec();
    while (distance < length)
    {
        pub.publish(cmd);
        double t2 = ros::Time::now().toSec();
        distance = speed * abs(t2 - t1);
        
    }
   
    cmd.linear.x = 0.0;
    pub.publish(cmd);
    rotate();
    
}

void drawsquare()
{
    for (int i = 0; i < 4; i++)
    {
      moveline();
    }  
  task = true;
}

int main(int argc , char** argv){
    ros::init(argc, argv, "movesquare");
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Rate rate(10);
    while(ros::ok()){
     ros::spinOnce();
     if(!flag){
        Input();
     }
     drawsquare();
     if(task){
        break;
     }
     rate.sleep();
    }
}