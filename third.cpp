#include"ros/ros.h"
#include"turtlesim/Spawn.h"
#include"geometry_msgs/Twist.h"
#include"turtlesim/Pose.h"
double x;                                //  小乌龟的x坐标
double y;                                //  小乌龟的y坐标
double yaw;                           //  小乌龟的偏航角
int ccx = 0;                            //  小乌龟当前运动位置的计数
double speed_x = 0.8;           //  小乌龟直线运动速度设定
double speed_a = 0.3;           //  小乌龟转角运动速度设定，不宜过大（推荐0.3及以下）

    //  小乌龟位置信息的接收回调函数
void doPose(const turtlesim::Pose::ConstPtr &pose){

    x = pose->x;
    y = pose->y;
    yaw = pose->theta;
}



int main(int argc,char** argv)
{

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




    ros::init(argc,argv,"control");
    ros::NodeHandle n;

    ros::service::waitForService("spawn");

    // generation turtle
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");
    ros::Rate rate(4);
    // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
	// ros::service::waitForService("/spawn");
	// ros::ServiceClient add_turtle_client = n.serviceClient<turtlesim::Spawn>("/spawn");

    // 初始化turtlesim::Spawn的请求数据
	turtlesim::Spawn tu2;
	tu2.request.x = 7.5;
	tu2.request.y = 8.5;
	tu2.request.name = "turtle2";

    turtlesim::Spawn tu3;
    tu3.request.x = 9;
	tu3.request.y = 4.2;
	tu3.request.name = "turtle3";

    turtlesim::Spawn tu4;
    tu4.request.x = 7.3;
	tu4.request.y = 2;
    tu4.request.theta=1.57;
	tu4.request.name = "turtle4";

    turtlesim::Spawn tu5;
    tu5.request.x = 5.7;
	tu5.request.y = 2;
	tu5.request.name = "turtle5";

    turtlesim::Spawn tu6;
    tu6.request.x = 3.9;
	tu6.request.y = 5;
	tu6.request.name = "turtle6";

    turtlesim::Spawn tu7;
    tu7.request.x = 1.5;
	tu7.request.y = 5;
	tu7.request.name = "turtle7";

    ros::Publisher pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Publisher pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
    ros::Publisher pub3 = n.advertise<geometry_msgs::Twist>("/turtle3/cmd_vel", 10);
    ros::Publisher pub4 = n.advertise<geometry_msgs::Twist>("/turtle4/cmd_vel", 10);
    ros::Publisher pub5 = n.advertise<geometry_msgs::Twist>("/turtle5/cmd_vel", 10);
    ros::Publisher pub6 = n.advertise<geometry_msgs::Twist>("/turtle6/cmd_vel", 10);
    ros::Publisher pub7 = n.advertise<geometry_msgs::Twist>("/turtle7/cmd_vel", 10);

      // 请求服务调用
	ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
			 tu2.request.x, tu2.request.y, tu2.request.name.c_str());
	client.call(tu2);
	// 显示服务调用结果
	ROS_INFO("Spwan turtle successfully [name:%s]", tu2.response.name.c_str());

    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
		tu3.request.x, tu3.request.y, tu3.request.name.c_str());
	client.call(tu3);
	ROS_INFO("Spwan turtle successfully [name:%s]", tu3.response.name.c_str());

    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
	tu4.request.x, tu4.request.y, tu4.request.name.c_str());
	client.call(tu4);
	ROS_INFO("Spwan turtle successfully [name:%s]", tu4.response.name.c_str());

    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
		tu5.request.x, tu5.request.y, tu5.request.name.c_str());
	client.call(tu5);
	ROS_INFO("Spwan turtle successfully [name:%s]", tu5.response.name.c_str());

    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
		tu6.request.x, tu6.request.y, tu6.request.name.c_str());
	client.call(tu6);
	ROS_INFO("Spwan turtle successfully [name:%s]", tu6.response.name.c_str());

    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", 
		tu7.request.x, tu7.request.y, tu7.request.name.c_str());
	client.call(tu7);
	ROS_INFO("Spwan turtle successfully [name:%s]", tu7.response.name.c_str());

    while (ccx<9)
    {
        ros::Subscriber sub = n.subscribe("/turtle1/pose",100,doPose);       

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
        }else if (ccx<=8 && x<=7.3)    
        {
            ccx = 8;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
                
        else{
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=9;
        }
        pub1.publish(twist);

        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;
    while (ccx<7)
    {
        ros::Subscriber sub2 = n.subscribe("/turtle2/pose",100,doPose);
         if (ccx<=1 && yaw>=-1.55)   // 转角90°
        {
            ccx = 1;
            twist.linear.x = 0;    // 前后
            twist.angular.z = -speed_a;
        }
         else if (ccx<=2 && y>=5.5)    
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=3 && abs(yaw)>=0.1)   // 转角90°
        {
            ccx = 3;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
        else if (ccx<=4 && x<=9)    
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=5 && abs(yaw)<=1.55)   // 转角90°
        {
            ccx = 5;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
         else if (ccx<=6 && y<=8.5)    
        {
            ccx = 6;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
       
        else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=7;
        }
        pub2.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;
        while (ccx<17)
    {
        ros::Subscriber sub3 = n.subscribe("/turtle3/pose",100,doPose);  

        if(ccx<=1 && yaw>=- 1.55)
        {
            ccx = 1;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
       else  if (ccx<=2 && y>=2.8)    
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
         else if (ccx<=3 && yaw>=-2)   // 转角
        {
            ccx = 3;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
          else if (ccx<=4 && y>=2)    
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=5 &&  abs(yaw)<=3.1)   // 转角
        {
            ccx = 5;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
        else if (ccx<=6 && x>=7.5)    
        {
            ccx = 6;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=7 &&abs( yaw)>=1.57)   // 转角
        {
            ccx = 7;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=8 && y<=5)    
        {
            ccx = 8;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=9 && abs(yaw)>=0.1)   // 转角
        {
            ccx = 9;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
         else if (ccx<=10 && x<=8.2)    
        {
            ccx = 10;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=11 && yaw>=-0.4)   // 转角
        {
            ccx = 11;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=12 && x<=9)    
        {
            ccx = 12;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=13 && yaw>=-1.53)   // 转角
        {
            ccx = 13;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
          else if (ccx<=14 && y>=3.5)    
        {
            ccx = 14;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=15 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 15;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  -speed_a;
        }
         else if (ccx<=16 && x>=7.5)    
        {
            ccx = 16;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=17;
        }

        pub3.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;

    //A
            while (ccx<11)
    {
        ros::Subscriber sub4 = n.subscribe("/turtle4/pose",100,doPose);  
         if (ccx<=1 && y<=5)    
        {
            ccx = 1;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
       else  if(ccx<=2&&abs(yaw)<=3.1)
        {
            ccx = 2;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }   
        else if (ccx<=3 && x>=5.8)    
        {
            ccx = 3;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if(ccx<=4&&abs(yaw)>=1.57)
        {
            ccx =4;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
          else if (ccx<=5 && y>=3.5)    
        {
            ccx = 5;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if(ccx<=6&&abs(yaw)>=0.1)
        {
            ccx =6;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
        else if (ccx<=7 && x<=7.3)    
        {
            ccx = 7;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=8 && x>=5.8)    
        {
            ccx = 8;
            twist.linear.x = -speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if(ccx<=9 &&abs(yaw)<=1.57)
        {
            ccx =9 ;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
          else if (ccx<=10 && y>=2)    
        {
            ccx = 10;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=11;
        }
        pub4.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;
            while (ccx<5)
    {
        ros::Subscriber sub5 = n.subscribe("/turtle5/pose",100,doPose);  
        if (ccx<=1 && abs(yaw)<=3.1)   // 转角
        {
            ccx = 1;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=2 && x>=4.3)    
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=3 && abs(yaw)>=1.58)   // 转角
        {
            ccx = 3;
            twist.linear.x = 0;    // 前后
            twist.angular.z = - speed_a;
        }
        else if (ccx<=4 && y<=5)    
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
       else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=5;
        }

        pub5.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;
            while (ccx<10)
    {
        ros::Subscriber sub6 = n.subscribe("/turtle6/pose",100,doPose);
        if(ccx<=1&&abs(yaw)<=3.1)  
        {
            ccx = 1;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;            
        }
        else if (ccx<=2 && x>=2.4)    
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=3 && abs(yaw)>=1.58)   // 转角
        {
            ccx = 3;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;
        }
        else if (ccx<=4 && y>=2)    
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=5 && abs(yaw)>=0.1)   // 转角
        {
            ccx = 5;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=6 && x<=3.9)    
        {
            ccx = 6;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=8 && yaw<=1.55)   // 转角
        {
            ccx = 8;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=9 && y<=5)    
        {
            ccx = 9;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
       else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=10;
        }

        pub6.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    ccx=0;
        while (ccx<13)
    {
        ros::Subscriber sub7 = n.subscribe("/turtle7/pose",100,doPose);  
        if(ccx<=1&&abs(yaw)<=3.1)  
        {
            ccx = 1;
            twist.linear.x = 0;    // 前后
            twist.angular.z = speed_a;            
        }
       else if (ccx<=2 && x>=0.7)    
        {
            ccx = 2;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=3 && abs(yaw)>=1.57)   // 转角D
        {
            ccx = 3;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=4 && y>=2)    
        {
            ccx = 4;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=5 && abs(yaw)>=0.1)   // 转角D
        {
            ccx = 5;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=6 && x<=1.5)    
        {
            ccx = 6;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=7 && yaw<=0.8)   // 转角
        {
            ccx = 7;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
       else if (ccx<=8 && x<=2.2)    
        {
            ccx = 8;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=9 && yaw<=1.55)   // 转角
        {
            ccx = 9;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=10 && y<=4.2)    
        {
            ccx = 10;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
        else if (ccx<=11 && yaw<=2.33)   // 转角
        {
            ccx = 11;
            twist.linear.x = 0;    // 前后
            twist.angular.z =  speed_a;
        }
        else if (ccx<=12 && y<=5)    
        {
            ccx = 12;
            twist.linear.x = speed_x;    // 前后
            twist.angular.z = 0;
        }
       else
        {
            twist.linear.x = 0;    // 前后
            twist.angular.z = 0;
            ccx=13;
        }

        pub7.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
//source devel/setup.bash
//rosrun third_pkg third
//rosrun turtlesim turtlesim_node