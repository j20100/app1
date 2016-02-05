/*
Code for GEI745, ROS pick and place plateform.
Author: Tristan Crossman, Tristan.Crossman@Usherbrooke.ca
License: BSD

Vers: 0.0.1
Date: 13/11/14
*/

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <string>
#include <map>
#include "robotJoint.h"
#include <math.h>


class robotJointControl
{

public:
	double theta1, theta2, theta4; //angles des articulations rotoides
	double d3; //amplitude de la translation de l'articulation prismatiques

	robotJointControl(ros::NodeHandle* node); //initialisation de la classe robotJointControl

	double getJoint(std::string joint_name); // récupére la valeur d'un joint
	void setJoint(std::string joint_name, double joint_send_value); //fixe une valeur pour un joint
	void goalPos(std::string joint_name, double joint_send_value, ros::Duration time_tot, ros::Rate rate); //génère un thread en fonction d'un profil de trajectoire

	/*COMPLETEZ LA FONCTION CI DESSOUS DE LA CINEMATIQUE INVERSE*/
	void IK(double, double, double, double);

private:
	std::map<std::string, robotJoint*> joint_map_; //conteneur permettant d'accéder aux fonctions de la classe robotJoint
};
