#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <tf/transform_broadcaster.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class nav_class {
private:
    ros::NodeHandle n;
    ros::Subscriber nav_sub;
    ros::Publisher nav_pub;
    std::vector<std::vector<std::string>> waypoints;
    geometry_msgs::PoseStamped goal;
    int goalNum = 0;

public:
    explicit nav_class(std::vector<std::vector<std::string>> content) {
        waypoints = std::move(content);
        nav_sub = n.subscribe("/move_base/status", 1, &nav_class::callback, this);
        nav_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
    }

    void callback(const actionlib_msgs::GoalStatusArray::ConstPtr& msg){
        if(!msg->status_list.empty()) {
            if (msg->status_list[msg->status_list.size()-1].status != 1 && goalNum < waypoints.size()) {
                goal.header.stamp = ros::Time::now();
                goal.header.frame_id = "map";
                goal.pose.position.x = std::stod(waypoints[goalNum][0]);
                goal.pose.position.y = std::stod(waypoints[goalNum][1]);
                goal.pose.position.z = std::stod(waypoints[goalNum][2]);
                goal.pose.orientation = tf::createQuaternionMsgFromYaw(std::stod(waypoints[goalNum][3]));
                nav_pub.publish(goal);
                goalNum++;
            }
        }
        else{
            goal.header.stamp = ros::Time::now();
            goal.header.frame_id = "map";
            goal.pose.position.x = std::stod(waypoints[goalNum][0]);
            goal.pose.position.y = std::stod(waypoints[goalNum][1]);
            goal.pose.position.z = std::stod(waypoints[goalNum][2]);
            goal.pose.orientation = tf::createQuaternionMsgFromYaw(std::stod(waypoints[goalNum][3]));
            nav_pub.publish(goal);
            goalNum++;
        }
    }
};

int main(int argc, char **argv){


    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, word;
    std::ifstream file("/home/anesanico/robotics/src/second_project/waypoints.csv");
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }

        std::cout<<"CSV File read\n";
    }
    else
        std::cout<<"Could not open the file\n";

    ros::init(argc, argv, "navigation");
    nav_class my_nav_class(content);
    ros::spin();
    return 0;
}
