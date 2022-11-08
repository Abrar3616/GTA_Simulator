# GTA_Simulator
A realtime simulator with motion blur for computor vision community using Grand Theft Auto V (GTA-V)

## About
GTA_Simulator is a realtime simulator that uses GTA-V as the source and has the option to add three levels of motion blur to the source. It extracts images and 6D poses against those images from the GTA-V game using the ScriptHookV library. It is based on G2D: from GTA to Data by Anh-Dzung Doan et. al. However in contrast to that work we propose a realtime data extraction algorithm. After extraction, these images and 6D poses are then saved in a network shared folder for another PC to access and use for mapping etc. This System uses two PC's with GPUs, one a windows 10 PC that runs the GTA-V game and the data extraction algorithm and one a Ubuntu 16.04 PC that uses that data as a feed to a mapping algorithm like ORB-SLAM etc. with or without added motion blur.

## Pre-requisites
note: two platform explanantion
The following are the pre-requisites that need to fulfilled:

**1) Windows 10 PC**

  - [GTA-V](https://store.steampowered.com/app/271590/Grand_Theft_Auto_V/)
  - [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/downloads/) or above
  - Working [G2D](https://github.com/dadung/G2D) source code
  - Network shared folder between Windows 10 and Ubuntu 16.04 PCs

**2) Ubuntu 16.04 PC**

  - Network shared folder between Ubuntu 16.04 and Windows 10 PCs
  - [ROS Kinetic Kame](http://wiki.ros.org/kinetic/Installation)
  - [Catkin Workspace](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)
  - [ORB-SLAM](https://github.com/raulmur/ORB_SLAM)

### Create a Network Shared Folder
We'll show you how to create a network shared folder for use with this simulator:

**Ubuntu 16.04 PC**

  - First create a folder named 'gta_live' in the home directory

![Screenshot from 2021-09-01 16-37-13](https://user-images.githubusercontent.com/74458556/131667953-e3c97810-3041-4ffe-8560-6f4281d10a8c.png)

  - Inside it create another folder named 'images'. This is where we will save the extracted images. 
  - Then create an empty text file named pose.txt inside 'gta_live folder but outside 'images' folder. Make sure to alter its permissions so that others can also read and write. This way the Windows 10 PC can also write to this file. This is where we will save the poses of the extracted images.

![Screenshot from 2021-09-01 16-49-34](https://user-images.githubusercontent.com/74458556/131667968-d85da6e1-a2a1-4c90-ae3a-7537be021bd6.png)

  - Then right click on 'gta_live' folder
  - Open 'properties'

![Screenshot from 2021-09-01 17-09-17](https://user-images.githubusercontent.com/74458556/131668877-73832b7c-2e67-44de-a3f6-c601bad4c3e8.png)

  - Click on 'Local Network Share' tab

![Screenshot from 2021-09-01 16-49-02](https://user-images.githubusercontent.com/74458556/131667961-96dc19bf-0202-4442-9368-47fd507b2c84.png)

  - Tick the 'Share this folder' box
  - Also tick both the 'Allow others to create and delete files in this folder' and 'Guest access (for people without a user account)' boxes

![Screenshot from 2021-09-01 16-49-12](https://user-images.githubusercontent.com/74458556/131667963-f826958f-af8c-4ec9-99b0-88357a95e842.png)

  - Then finally click on 'Create Share' button

![Screenshot from 2021-09-01 16-49-27](https://user-images.githubusercontent.com/74458556/131667966-397230d9-8ed2-45ec-9466-c1b662294e5b.png)

Now the folder is shared, we just need to access it from the Windows 10 PC.

![Screenshot from 2021-09-01 16-50-04](https://user-images.githubusercontent.com/74458556/131667970-2c5b0051-66b8-4cc4-8c9d-4cf3b17b179f.png)

**Windows 10 PC**

  - Double click on 'This PC'
 
![Untitled](https://user-images.githubusercontent.com/74458556/131666942-259240d2-ae9f-4efa-be55-5847db83a77d.png)

  - Right click on empty space and select the option 'Add a network location'. 
 
![Untitled1](https://user-images.githubusercontent.com/74458556/131666950-75f124f2-6ca8-477e-adfb-3583ad70d8f7.png) 
 
  - A window will open up. Click on 'Next'
 
![Untitled2](https://user-images.githubusercontent.com/74458556/131666919-9d7ad242-e6fb-476f-95be-982401cd0dfc.png)

  - Then choose the 'Choose a custom network location' option or click on 'Next'

![Untitled3](https://user-images.githubusercontent.com/74458556/131666924-191a3a98-ee0f-4d6e-b2df-41b7fae94914.png)

  - Here you enter the ip address and folder name in the dialog box as such:
  
        \\*ip address of Ubuntu 16.04 PC*\gta_live
        
![Untitled4](https://user-images.githubusercontent.com/74458556/131666928-c411d82d-f584-473a-86ef-217b65e6bd32.png)
        
  - Click 'Next'
  - Next you can select a custom name for this network location according to your preferences. This will not affect how the location will be accesssed. You will still have to enter the location in the script as above.

![Untitled5](https://user-images.githubusercontent.com/74458556/131666930-ffe21411-5a68-4cf7-b7b2-23941d313647.png)

  - Now the window will show a success message once the location is created. Click 'Finish'

![Untitled6](https://user-images.githubusercontent.com/74458556/131666934-0bf5eeca-c820-4387-91e9-2aab022ba842.png)

  - You can now see your newly added network shared folder on 'This PC' under 'Network Locations'  
      
![Untitled7](https://user-images.githubusercontent.com/74458556/131666938-ff94c9aa-b7dc-4206-9a52-e4882f7e66a4.png)

## Installation
Once all the pre-requisites have been fulfilled we can begin to setup the simulator:

**Windows 10 PC**

  - Goto the Trajectory Tool folder of G2D and replace script.cpp and script.h file with ours from GTA-Scripts folder.
  - Open our script.cpp file in visual studio and replace the ip address in line 29 and 30 with that of your Ubuntu 16.04 PC that has the network shared folder.
  - Build the solution then take the G2D-Trajectory.asi file from bin folder and add it to the GTA-V directory.

You can also adjust the script.cpp file to get camera pose in quaternions instead of pitch, roll and yaw in degrees. Simply uncomment lines 134 and 142 and subsequently comment line 143.

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
  - You can find the images and 6D pose file in the network shared folder. The images will be in the images folder and the poses in the pose.txt file. 

**Ubuntu 16.04 PC**

  - You can use the bash script provided to automatically execute the other scripts after adjusting it based on how much motion blur is needed, if at all.
  - This script will run ORB-SLAM and the blur nodes if required. The mapping will start.

Be sure to wait a few seconds for ORB-SLAM to setup before starting the extraction of images and 6D poses.

The pose file contains the 6D poses in the following format:

With Quaternions:
              
    # pathtoimage tx ty tz qx qy qz qw
    
With Pitch, Roll and Yaw in Degrees:

    # pathtoimage tx ty tz p r y

## Further Data

[Dataset for ORBSLAM3](https://drive.google.com/drive/folders/1iDRRug1AiDDXy9CsOzIch_M3QqtdbFBa?usp=sharing)
[Compilation of Datasets](https://drive.google.com/drive/folders/14ngM6XH_hETcywOdPr9Pvkdmbr6eIRHX?usp=share_link)

## License
This work and any data acquired from this work is for educational and research purposes only. Any commercial use is strictly prohibited.

Also as a courtesy to Rockstar Games please purchase the Grand Theft Auto V game.

## Support
If you have any queries or questions please feel free to contact me at: (abrar16qureshi@gmail.com) 

Contributions (bug reports, bug fixes, improvements, etc.) are very welcome and should be submitted in the form of new issues and/or pull requests on GitHub.

## Acknowledgments
We would like to thank Alexander Blade, the original author of the ScriptHookV library and all the contributors of the ScriptHookV library. 

Also we would like to thank Anh-Dzung Doan et. al. for their G2D code that gave us the base for this work. 
