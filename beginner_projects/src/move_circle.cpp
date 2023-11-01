#include<ros/ros.h>
#include<geometry_msgs/Twist.h>

geometry_msgs::Twist cmd;
ros::Publisher pub;
int length;
int speed = 3;
bool flag = false;

void Input()
{
  std::cout<<"Enter your radius of the circle : ";
  std::cin>> length;
  std::cout<<std::endl;
  flag = true;
}

void movecircle()
{
    cmd.linear.x = speed;
    cmd.angular.z = speed/length;
}

int main(int argc , char** argv ){
    ros::init(argc, argv, "movecircle");
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        if(!flag){
            Input();
        }
        movecircle();
        pub.publish(cmd);
        rate.sleep();

    }
}