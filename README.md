# RT_assignement2
S5165612

# Description
This main idea from this project to to make the robot follow the track 
without crashing using laser scanner have range from 0 to 720 represents 
actual angle range from 0 to 180 degrees and the user can controll the 
velocity by using services.


# Installing
```
catkin_make
```
 # Running
 ```
 roscore &
 ```
 ```
 rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world 
 ```
 ```
 rosrun assignment2 controller_node
 ```
 ```
 rosrun my_srv client_node
 ```
 
 
