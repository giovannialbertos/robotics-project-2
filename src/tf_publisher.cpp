#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

#include <sstream>

class tf_pub_class {
private:
    ros::NodeHandle n;
    ros::Subscriber odom_sub;
    tf::TransformBroadcaster tf_odom;

public:
    tf_pub_class() {
        odom_sub = n.subscribe("/t265/odom", 1, &tf_pub_class::callback, this);
    }

    void callback(const nav_msgs::Odometry::ConstPtr &msg) {
        tf::Transform transform;
        transform.setOrigin(
                tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z));
        tf::Quaternion q;
        q.setX(msg->pose.pose.orientation.x);
        q.setY(msg->pose.pose.orientation.y);
        q.setZ(msg->pose.pose.orientation.z);
        q.setW(msg->pose.pose.orientation.w);
        transform.setRotation(q);
        tf_odom.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
    }
};
		
int main(int argc, char **argv){
    
	ros::init(argc, argv, "tf_publisher");
	tf_pub_class my_tf_pub_class;
    	ros::spin(); 
  	return 0;
}
