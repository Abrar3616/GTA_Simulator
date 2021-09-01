#!/bin/bash

clear

#Following commands run ROSCORE

echo "Starting ROSCORE"
roscore &
sleep 2
echo "Started ROSCORE"

#Following commands run ORB_SLAM after a 2 second delay

echo "Starting ORB_SLAM"
source ~/.bashrc
roslaunch ORB_SLAM Test.launch &
sleep 7
echo "Started ORB_SLAM"

#Following commands run the integration algorithm after a 7 second delay

cd /home/abrar/catkin_ws
source devel/setup.bash

#To run GTA without blur uncomment the following 3 lines and comment the rest of the lines

echo "Started Merger_Node"
rosrun merger merger_node

#To run GTA with blur uncomment the following 6 lines and comment the above 3 lines. Also choose the amount of blur low, medium or high

#echo "Starting Blur_Node"
#rosrun blur_gta blur_low.py &
#rosrun blur_gta blur_medium.py &
#rosrun blur_gta blur_high.py &
#echo "Started Blur_Node"

#echo "Started Blur_Merger_Node"
#rosrun blur_merger blur_merger_node
