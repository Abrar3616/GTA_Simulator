#include <ros/ros.h>
#include <iostream>
#include <string>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace std;

int main(int argc, char* argv[])
{
    ros::init(argc,argv,"gta_image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher            pub=it.advertise("/camera/image_raw",10);
    int i = 0;
    cv::Mat image;
    cv::Mat imager;
    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate(15);

    while(nh.ok())
    {
      stringstream ss;
      //stringstream si;
      ss << "/home/abrar/gta_live/images/" << std::to_string(i) << ".jpg";
      std::string image_name;
      image_name =  ss.str();
    	image = cv::imread(image_name,CV_LOAD_IMAGE_COLOR);
      if(!image.empty())
      {
        resize(image, imager, cv::Size(640, 480), 0, 0, CV_INTER_AREA);
        //si << std::setfill('0') << std::setw(4) << i;
        //std::string s = si.str();
        //cv::imwrite("/home/abrar/trajectory-6/"+ s +".jpg", imager);
        msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",imager).toImageMsg();
        pub.publish(msg);
        i++;
      }

      //ROS_INFO_STREAM(image_name);

    	ros::spinOnce();
    	loop_rate.sleep();
    }

}
