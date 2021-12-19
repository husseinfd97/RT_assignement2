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
 
 # Algorithm
 ![CamScanner 12-19-2021 17 20_1](https://user-images.githubusercontent.com/94136236/146683362-60b69bc7-6a2f-4516-a0d2-63059e20bb81.jpg)
![CamScanner 12-19-2021 17 20_2](https://user-images.githubusercontent.com/94136236/146683369-1f9ef9ca-7bf9-419f-b421-50b458041aee.jpg)
![CamScanner 12-19-2021 17 20_3](https://user-images.githubusercontent.com/94136236/146683372-68864ea8-f737-4688-900a-e516a3f80b0b.jpg)

 
 
