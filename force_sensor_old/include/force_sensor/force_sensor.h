#ifndef __FORCE_SENSOR__  //重複定義回避
#define __FORCE_SENSOR__

// Gazebo dependencies
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/gazebo_client.hh>

// ROS dependencies
#include <ros/ros.h>
#include <geometry_msgs/WrenchStamped.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

int collision_count_1 = 0;
int collision_count_2 = 0;
int collision_count_3 = 0;
int collision_count_4 = 0;

double ros_rate;
int count1 = 0;
int count2 = 0;

geometry_msgs::WrenchStamped msgWrenchedStamped1;
geometry_msgs::WrenchStamped msgWrenchedStamped2;

#endif // #define __FORCE_SENSOR__
