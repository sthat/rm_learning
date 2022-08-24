#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#define PI 3.1415926

/*
    需求：订阅位置信息，发布速度信息
        订阅话题： /turtle1/pose
        发布话题： /turtle1/cmd_vel

    发布方实现：
        1、包含头文件；
        2、初始化 ROS 节点；
        3、创建节点句柄；
        4、创建发布对象
        5、发布逻辑实现
        6、spinOnce（）

*/

double x;                                //  小乌龟的x坐标
double y;                                //  小乌龟的y坐标
double yaw;                           //  小乌龟的偏航角
int ccx = 0;                            //  小乌龟当前运动位置的计数
double speed_x = 0.8;           //  小乌龟直线运动速度设定
double speed_a = 0.3;           //  小乌龟转角运动速度设定，不宜过大（推荐0.3及以下）

    //  小乌龟位置信息的接收回调函数
void doPose(const turtlesim::Pose::ConstPtr &pose){
    // ROS_INFO("Got pose_msg: XY_pose(%.2f,%.2f),Dir(%.2f),Accle(%.2f,%.2f)",
    // pose->x,pose->y,pose->theta,pose->linear_velocity,pose->angular_velocity);
    x = pose->x;
    y = pose->y;
    yaw = pose->theta;
}

int main(int argc,char * argv[])
{
    // 2、初始化 ROS 节点；
    ros::init(argc,argv,"mycontrol");
    // 3、创建节点句柄；
    ros::NodeHandle nh;
    // 4、创建发布对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    // 5、发布逻辑实现
    ros::Rate rate(4);
    geometry_msgs::Twist twist;
    // 参数设置
    float linear_x;
    float angular_z;

    twist.linear.x = 0;    // 前后
    twist.angular.z = 0;   // 偏航
    // 无需考虑的参数 --- 对于小乌龟而言
    twist.linear.y = 0;
    twist.linear.z = 0;
    twist.angular.x = 0;
    twist.angular.y = 0;

    while (ros::ok())
    {  
        //  尝试使用坐标控制   
        //  创建订阅对象（小乌龟的位置信息）
        ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,doPose);
        //   输出小乌龟的xy坐标、角度
        ROS_INFO("xy pose:%.2f,%.2f,yaw:%.2f",x,y,yaw);


        //  实现根据小乌龟的所在位置，控制其移动

        //S
        if (x<=7 && ccx==0)    // 
        {
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }else if (x>=7 && yaw<1.53 && ccx<=1)    // 转角90°1
        {
            ccx = 1;
            twist.linear.x = 0;   
            twist.angular.z = speed_a;
        }else if (ccx<=2 && y<=7)
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }else if (ccx<=3 && abs(yaw)<=3.1)   // 转角90°2
        {
            ccx = 3;
            twist.linear.x = 0;   
            twist.angular.z = speed_a;
        }else if (ccx<=4 && x>=5.5)
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }else if (ccx<=5 && abs(yaw)>=1.57)   // 转角90°3
        {
            ccx = 5;
            twist.linear.x = 0;    // 前后
            twist.angular.z = -speed_a;
        }else if (ccx<=6 && y<=8.5)    
        {
            ccx = 6;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }else if (ccx<=7 && yaw>=0.01)   // 转角90°
        {
            ccx = 7;
            twist.linear.x = 0;    // 前后
            twist.angular.z = -speed_a;
        }else if (ccx<=8 && x<=7.5)    
        {
            ccx = 8;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }

        //U
         else if (ccx<=9 && abs(yaw)<=1.55)   // 转角90°3
        {
            ccx = 9;
            twist.linear.x = 0;    // 前后
            twist.angular.z = -speed_a;      
        }
        else if (ccx<=10 && y>=5.5)    
        {
            ccx = 10;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=11 && abs(yaw)>=0.1)   // 转角90°
        {
            ccx = 11;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
        else if (ccx<=12 && x<=9)    
        {
            ccx = 12;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=13 && abs(yaw)<=1.53)   // 转角90°
        {
            ccx = 13;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
         else if (ccx<=14 && y<=8.5)    
        {
            ccx = 14;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=15 && yaw>=-1.53)   // 转角90°
        {
            ccx = 15;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }

        //B
         else if (ccx<=16 && y>=2.8)    
        {
            ccx = 16;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=17 && yaw>=-2)   // 转角
        {
            ccx = 17;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
          else if (ccx<=17 && y>=2)    
        {
            ccx = 17;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=18 &&  abs(yaw)<=3.1)   // 转角
        {
            ccx = 18;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
        else if (ccx<=19 && x>=7.5)    
        {
            ccx = 19;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=20 &&abs( yaw)>=1.57)   // 转角
        {
            ccx = 20;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=21 && y<=5)    
        {
            ccx = 21;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=22 && abs(yaw)>=0.1)   // 转角
        {
            ccx = 22;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
         else if (ccx<=23 && x<=8.2)    
        {
            ccx = 23;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=24 && yaw>=-0.4)   // 转角
        {
            ccx = 24;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=25 && x<=9)    
        {
            ccx = 25;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=26 && yaw>=-1.53)   // 转角
        {
            ccx = 26;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=27 && y>=3.5)    
        {
            ccx = 27;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=28 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 28;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
         else if (ccx<=29 && x>=7.5)    
        {
            ccx = 29;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=30 && abs(yaw)>=1.57)   // 转角
        {
            ccx = 30;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
          else if (ccx<=31 && y>=2)    
        {
            ccx = 31;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=32 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 32;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
         else if (ccx<=33 && x>=7.3)    
        {
            ccx = 33;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }


        //A
        else if (ccx<=34 && abs(yaw)>=1.55)   // 转角
        {
            ccx = 34;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
        else if (ccx<=35 && y<=5)    
        {
            ccx = 35;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=36 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 36;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
          else if (ccx<=37 && x>=5.8)    
        {
            ccx = 37;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }       
        else if (ccx<=38 && abs(yaw)>=1.55)   // 转角
        {
            ccx = 38;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=39 && y>=3.5)    
        {
            ccx = 39;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=40 &&abs(yaw)>=0.1)   // 转角
        {
            ccx = 40;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=41 && x<=7.3)    
        {
            ccx = 41;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=42 &&abs( yaw)<=3.1)   // 转角
        {
            ccx = 42;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=43 && x>=5.8)    
        {
            ccx = 43;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=44 && abs(yaw)>=1.55)   // 转角
        {
            ccx = 44;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }      
        else if (ccx<=45 && y>=2)    
        {
            ccx = 45;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=46 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 46;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }

        //L
        else if (ccx<=47 && x>=4.1)    
        {
            ccx = 47;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=48 && abs(yaw)>=1.55)   // 转角
        {
            ccx = 48;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
        else if (ccx<=49 && y<=5)    
        {
            ccx = 49;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=50 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 50;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=51 && x>=0.7)    
        {
            ccx = 51;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=52 && abs(yaw)>=1.55)   // 转角D
        {
            ccx = 52;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=53 && y>=2)    
        {
            ccx = 53;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=54 && abs(yaw)>=0.1)   // 转角D
        {
            ccx = 54;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=55 && x<=1.5)    
        {
            ccx = 55;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=56 && yaw<=0.8)   // 转角
        {
            ccx = 56;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=57 && x<=2.2)    
        {
            ccx = 57;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=58 && yaw<=1.55)   // 转角
        {
            ccx = 58;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=59 && y<=4.2)    
        {
            ccx = 59;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=60 && yaw<=2.33)   // 转角
        {
            ccx = 60;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=61 && y<=5)    
        {
            ccx = 61;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=62 && abs(yaw)>=0.1)   // 转角
        {
            ccx = 62;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
       else if (ccx<=63 && x<=2.4)    
        {
            ccx = 63;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=64 && abs(yaw)<=1.55)   // 转角
        {
            ccx = 64;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
        else if (ccx<=65 && y>=2)    
        {
            ccx = 65;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=66 && abs(yaw)>=0.1)   // 转角
        {
            ccx = 66;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=67 && x<=3.9)    
        {
            ccx = 67;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=68 && yaw<=1.55)   // 转角
        {
            ccx = 68;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=69 && y<=5)    
        {
            ccx = 69;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }




        else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
        }
        pub.publish(twist);

        // 休眠
        rate.sleep();
        // 6、spinOnce（）
        ros::spinOnce();

    }   
    return 0;
}
//rosrun letter_pkg letter
//rosrun turtlesim turtlesim_node