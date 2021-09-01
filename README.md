# GTA_Simulator
A realtime simulator with motion blur for computor vision community using Grand Theft Auto V (GTA-V)

## About
GTA_Simulator is a realtime simulator that uses GTA-V as the source and has the option to add three levels of motion blur to the source. It extracts images and 6D poses against those images from the GTA-V game using the ScriptHookV library. It is based on G2D: from GTA to Data by Anh-Dzung Doan et. al. However in contrast to that work we propose a realtime data extraction algorithm. After extraction these images and poses are then saved in a network shared folder for another PC to access and use for mapping etc. This System uses two PC's with GPUs, one a windows 10 PC that runs the GTA-V game and the data extraction algorithm and one a Ubuntu 16.04 PC that uses that data as a feed to a mapping algorithm like ORB-SLAM etc. with or without added motion blur.

## Pre-requisites
The following are the pre-requisites that need to fulfilled:

**1) Windows 10 PC**

  - [GTA-V](https://store.steampowered.com/app/271590/Grand_Theft_Auto_V/)
  - [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/downloads/) atleast
  - Working [G2D](https://github.com/dadung/G2D) source code
  - Network shared folder between Windows 10 and Ubuntu 16.04 PCs

**2) Ubuntu 16.04 PC**

  - Network shared folder between Ubuntu 16.04 and Windows 10 PCs
  - [ROS Kinetic Kame](http://wiki.ros.org/kinetic/Installation)
  - [Catkin Workspace](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)
  - [ORB-SLAM](https://github.com/raulmur/ORB_SLAM)

## Installation
Once all the pre-requisites have been fulfilled we can begin to setup the simulator:

**Windows 10 PC**

  - Goto the Trajectory Tool folder of G2D and replace script.cpp and script.h file with ours from GTA-Scripts folder.
  - Open our script.cpp file in visual studio and replace the ip address in line 29 and 30 with that of your Ubuntu 16.04 PC that has the network shared folder.
  - Build the solution then take the G2D-Trajectory.asi file from bin folder and add it to the GTA-V directory.

You can also adjust the script.cpp file to get camera pose in quaternions. Simply uncomment lines 134 and 142 and subsequently comment line 143.

**Ubuntu 16.04 PC**

  - Create standard individual packages for Blur-GTA, Blur-Merger and Merger scripts with those names in catkin_ws. 
  - Remember to change the input and output directories in the scripts to your specific directories. Also remember to make the python scripts executable. Build the packages.
  - Update the camera parameters for ORB-SLAM using the camera intrinsic parameters provided in the repository.
    
## Usage
Once all necessary scripts and packages have been installed we can get started on using the GTA_Simulator:

**Windows 10 PC**

  - Run GTA-V. Once the game is up and running you can use the Condition Tool of G2D to adjust the conditions like time and weather etc. You can also use the Native trainer of ScriptHookV to adjust the time and weather conditions of the game. However to adjust the pedestrian and vehicle density you must use the Condition tool of G2D. 
  - To start the extraction of images and poses from GTA-V, press the F5 key. A notification will let you know when the extraction starts.
  - To end the extraction press the END key. Again a notification will let you know when extraction stops.
  - You can find the images and pose file in the network shared folder. The images will be in the images folder and the poses in the pose.txt file. 

**Ubuntu 16.04 PC**

  - You can use the bash script provided to automatically execute the other scripts after adjusting it based on how much motion blur is needed, if at all.
  - This script will run ORB-SLAM and the blur nodes if required. The mapping will start.

Be sure to wait a few seconds for ORB-SLAM to setup before starting the extraction of images and 6D poses.

The pose file contains the 6D poses in the following format:

With Quaternions:
              
    # pathtoimage tx ty tz qx qy qz qw
    
With Roll, Pitch and Yaw in Degrees:

    # pathtoimage tx ty tz p r y

## License
This work and any data acquired from this work is for educational and research purposes only. Any commercial use is strictly prohibited.

Also as a courtesy to Rockstar Games please purchase the Grand Theft Auto V game.

## Support
If you have any queries or questions please feel free to contact me at: (abrar16qureshi@gmail.com) 

Contributions (bug reports, bug fixes, improvements, etc.) are very welcome and should be submitted in the form of new issues and/or pull requests on GitHub.

## Acknowledgments
We would like to thank Alexander Blade, the original author of the ScriptHookV library and all the contributors of the ScriptHookV library. 

Also we would like to thank Anh-Dzung Doan et. al. for their G2D code that gave us the base for this work. 
