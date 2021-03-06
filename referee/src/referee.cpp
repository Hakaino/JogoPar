#include "ros/ros.h"
#include <iostream>
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
//#include <experimental/random>
//#include <math.h>
#include <image_transport/image_transport.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

std::string players[] = {"", "", "", ""};
int points[] = {0, 0, 0, 0};
std_msgs::String strea_message;

void p1(const std_msgs::String::ConstPtr& val){
    players[0] = val->data;
}

void p2(const std_msgs::String::ConstPtr& val){
    players[1] = val->data;
}

void p3(const std_msgs::String::ConstPtr& val){
    players[2] = val->data;
}

void p4(const std_msgs::String::ConstPtr& val){
    players[3] = val->data;
}

/*
bool winner = false;

class ImageSaver{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;

    int i = 0;
    char filename[80];

public:
    ImageSaver()
            : it_(nh_)
    {
        image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ImageSaver::imageCb, this);
    }


    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        if(winner){
            sprintf(filename,"Winner_Round:%d.png", i++);
            cv::imwrite(filename,cv_ptr->image);
            winner = false;
        }
    }
};*/

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "referee");
    ros::NodeHandle nh;
    ros::Subscriber player_1 = nh.subscribe("p1_topic", 1, p1);
    ros::Subscriber player_2 = nh.subscribe("p2_topic", 1, p2);
    ros::Subscriber player_3 = nh.subscribe("p3_topic", 1, p3);
    ros::Subscriber player_4 = nh.subscribe("p4_topic", 1, p4);
    //"/cmd_vel_mux/input/navi"     //use this topic when using the turtlebot
    ros::Publisher velocity = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Publisher feedback = nh.advertise<std_msgs::String>("feed_topic", 1);
    ros::Duration(1.0).sleep();
    geometry_msgs::Twist msg;
    std::stringstream ss;
    int round = 0;
    int highest = 0;
    int untie = 0;
    ROS_INFO("\tLet's play a game...");
    while (ros::ok && round + untie <= 4){
        ros::spinOnce();
        ros::Duration(0.5).sleep();
        if (players[0] != "" && players[1] != "" && players[2] != "" && players[3] != "") {
            round++;
            //this checks if the two players have the same card
            for (int px = 0; px < 4; px++) for (int py = 0; py < 4; py++)
                    if (px != py && players[px] == players[py]){
                        points[px]++;
                        points[py]++;
                    } else if (players[px] == "quit") break;
            ss.str(std::string());
            ss << "ROUND "<< round << "\tP1: " << points[0] << "\tP2: "
               << points[1] << "\tP3: " << points[2] << "\tP4: " << points[3];
            strea_message.data = ss.str();
            ROS_INFO("%s", strea_message.data.c_str());
            feedback.publish(strea_message);
            for (int i = 0; i < 4; i++) players[i] = "";
        };
        //check for tie
        if (round > 4){
            untie = -round + 6;
            for (int j = 0; j < 4; j++) if (points[j] > highest) highest = points[j];
            for (int j = 0; j < 4; j++) if (points[j] == highest) untie--;
        };
    };
    //this will find out the winner
    for (int player = 0; player < 4; player++) if (points[player] == highest) {
            ss.str(std::string());
            ss << "\n\n\t#####################################" <<
               "\n\t###   The winner is player "<< player + 1 <<"!!!   ###" <<
               "\n\t#####################################\n";
            strea_message.data = ss.str();
            ROS_INFO("s%", strea_message.data.c_str());
            feedback.publish(strea_message);
            msg.angular.z = player * M_PI / 2;
            velocity.publish(msg);
            ros::Duration(1.0).sleep();
            /*winner = true;
            ImageSaver is;*/
            ros::Duration(1.0).sleep();
            ros::spinOnce();
        };
}
