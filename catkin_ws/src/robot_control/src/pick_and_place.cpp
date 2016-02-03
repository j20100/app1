/*
Code for GEI745, ROS pick and place plateform.
Author: Tristan Crossman, Tristan.Crossman@Usherbrooke.ca
License: BSD

Vers: 0.0.1
Date: 13/11/14
*/


#include "ros/ros.h"
#include "robotJointControl.h"


int main(int argc, char** argv)
{
  /*
   The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "pick and place");

  //AJOUTEZ CI-DESSOUS VOTRE CODE DE LA TACHE PICK AND PLACE


}