#include <ros/ros.h>
#include <iostream>
#include "std_msgs/String.h"

std_msgs::String choice;
bool running = true;


void input_card(){
    std::cin >> choice.data;
}
void read_message(const std_msgs::String::ConstPtr& val){
  ROS_INFO("%s\n", val->data.c_str());
  ROS_INFO("chose one >>\ttic\tpuk\tbla\tzuw\tret\ttype 'quit' to quit");
  input_card();
}

void quit(const std_msgs::String::ConstPtr& val){
  running = false;
}

//this node sends the messages to the boost
int main(int argc, char *argv[]) {
    ros::init(argc, argv, "P_3");
    ros::NodeHandle nh;
    ros::Publisher publisher = nh.advertise<std_msgs::String>("p3_topic", 1);
    ros::Subscriber feedback = nh.subscribe("feed_topic", 1, read_message);
    ros::Subscriber q = nh.subscribe("quit_topic", 1, quit);
    std::string a, b, c, d, e;
    a = "tic";
    b = "puk";
    c = "bla";
    d = "zuw";
    e = "ret";
    ROS_INFO("[PLAYER 3]");
    ROS_INFO("chose one >>\ttic\tpuk\tbla\tzuw\tret\ttype 'quit' to quit");
    input_card();
    while (ros::ok && choice.data != "quit") {
      if (choice.data == a || choice.data == b || choice.data == c ||
         choice.data == d || choice.data == e || choice.data == "quit"){
           publisher.publish(choice);
           ROS_INFO("Your play was sent.");
           choice.data = " ";
      } else if(choice.data != " ") {
        ROS_INFO("wrong option, try again...");
        input_card();
      }
      ros::Duration(0.5).sleep();
	    ros::spinOnce();
    };
}
