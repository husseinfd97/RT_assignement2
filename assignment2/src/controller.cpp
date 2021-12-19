#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "my_srv/Velocity.h"
#include "std_srvs/Empty.h"
#include <string>

float Left_range, Front_range,Right_range;
float vel=0.5;

ros::Subscriber sub;
ros::Publisher pub;
ros::ServiceClient Client;



#define max_increase 1.5
#define min_decrease 0.3
#define cal_right_value 200
#define cal_front_value 360
#define cal_left_value 520
#define min_dist  1
#define Reset_value 0.5





bool control_velocity (my_srv::Velocity::Request &req, my_srv::Velocity::Response &res)
{
	
		if (req.v == "i" )
		{
			res.x = vel + 0.4*vel;
			
		}
		else if (req.v == "d" )
		{
			res.x = vel - 0.4*vel;
		}
		else if (req.v == "r" )
		{	ros::NodeHandle nh;
			ros::ServiceClient Client = nh.serviceClient<std_srvs::Empty>("/reset_positions");
			std_srvs::Empty srv;
			Client.waitForExistence();
			Client.call(srv);
			res.x=vel;
		
		}

		if (res.x > max_increase || res.x < min_decrease)
		{
			res.x=Reset_value;
		}
		vel=res.x;
		return res.x;
}



// float Find_min(int lower,int upper)
// {
//  	static int min=lower;
// 	for (int i=lower<i<upper;i++)
// 	{
//  	   if(i<n)
//        {
//        	if(v[min]>v[i])
//        	 {
// 			      min=i;
// 			      minimum(v,n,++i);
			      
//         }
// 	   }
// 	}return min;
// }


void Control_call_back(const sensor_msgs::LaserScan::ConstPtr& msg)

{
	// set left ,middle and right ranges // 
	Right_range = msg-> ranges[cal_right_value];
	Front_range = msg-> ranges[cal_front_value];
	Left_range = msg-> ranges[cal_left_value];



	geometry_msgs::Twist act_vel;
	// Check for the movement algorithm //
	if ((Left_range > min_dist && Front_range > min_dist && Right_range>min_dist)||( Left_range <min_dist && Front_range >min_dist && Right_range <min_dist))
	{
	act_vel.linear.x = vel;
	act_vel.angular.z = 0.0;
	} 
	else if ((Left_range > min_dist && Front_range< min_dist && Right_range > min_dist)||(Left_range > min_dist && Front_range>min_dist && Right_range <min_dist)){
	act_vel.linear.x = vel;
	act_vel.angular.z = 1.5;
	}
	
	else if ((Left_range <min_dist && Front_range>min_dist && Right_range >min_dist)||(Left_range < min_dist && Front_range <min_dist && Right_range >min_dist )){
	act_vel.linear.x = vel;
	act_vel.angular.z =-1.5;
	}
	else if ((Left_range > min_dist && Front_range < min_dist && Right_range <min_dist)||(Left_range <min_dist && Front_range <min_dist && Right_range <min_dist))
	{
	act_vel.linear.x = vel;
	act_vel.angular.z =1.5;
	}

	pub.publish(act_vel);
}
	
	
	int main (int argc, char **argv)
{

	ros::init(argc, argv, "maze_bot_subscriber"); 
	ros::NodeHandle n;
	ros::NodeHandle nh;
	ros::ServiceServer service= n.advertiseService("/velocity", control_velocity);
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);
	ros::Subscriber sub = nh.subscribe("/base_scan", 1,Control_call_back);
	ros::ServiceClient Client = nh.serviceClient<std_srvs::Empty>("/reset_positions");
	std_srvs::Empty srv;
 	Client.waitForExistence();
	Client.call(srv);
	
	
	ros::spin();
	return 0;
}
