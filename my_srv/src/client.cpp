#include "ros/ros.h"
#include "my_srv/Velocity.h"
#include <cstdlib>
#include <string>

char entered_order;
	
int main(int argc, char **argv) 
{
	ros::init(argc, argv, "enter_order");
	
	while (1)
	{

		ros::NodeHandle n;
		ros::ServiceClient client = n.serviceClient<my_srv::Velocity>("/velocity");
		my_srv::Velocity velocity_srv; 
		std::cout<<"Service : Enter the order you want to be done i for increase and d for decrease or r for reset: ";
		std::cin>>entered_order;
		velocity_srv.request.v = entered_order;

		if (client.call(velocity_srv)) 
		{
		
			std::cout<<"Velocity is  "<< velocity_srv.response.x << std::endl;
		
		}
		
	}
		return 0;
}
		

