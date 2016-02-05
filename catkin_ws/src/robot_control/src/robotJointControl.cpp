/*
Code for GEI745, ROS pick and place plateform.
Author: Tristan Crossman, Tristan.Crossman@Usherbrooke.ca
License: BSD

Vers: 0.0.1
Date: 13/11/14
*/

#include "robotJointControl.h"

robotJointControl::robotJointControl(ros::NodeHandle* node)
{
	bool init_joint = false;
	bool temp = true;
	XmlRpc::XmlRpcValue list_joint_name;
	if(node->getParam("/robot/joint_list", list_joint_name))
	{
		ROS_ASSERT(list_joint_name.getType() == XmlRpc::XmlRpcValue::TypeArray);
		for (int i = 0; i < list_joint_name.size(); ++i)
			joint_map_[static_cast<std::string>(list_joint_name[i])] = new robotJoint(static_cast<std::string>(list_joint_name[i]), node, 50);
	}
	else
		ROS_ERROR("Get ros_param not found");

	std::map<std::string, robotJoint*>::iterator it;

	while (ros::ok())
	{
		for(it = joint_map_.begin(); it != joint_map_.end(); ++it)
		{
			temp = temp and it->second->initEnd();
			ros::spinOnce();
			if(!it->second->initEnd())
				ROS_INFO("%s", it->second->getName().c_str());
		}
		!temp ? temp = true : init_joint = true ;

		if(init_joint)
		{
			break;
			ROS_INFO("Initialisation end");
		}
	}
}


double robotJointControl::getJoint(std::string joint_name)
{
	std::map<std::string, robotJoint*>::iterator it;
	it = joint_map_.find(joint_name);

	if(it != joint_map_.end())
		return it->second->getJoint();
	else
	{
		ROS_ERROR("Joint name not found !");
		return 0;
	}
}


void robotJointControl::setJoint(std::string joint_name, double joint_send_value)
{
	std::map<std::string, robotJoint*>::iterator it;
	it = joint_map_.find(joint_name);
	if(it != joint_map_.end())
		it->second->setJoint(joint_send_value);
	else
		ROS_ERROR("joint name not found !");
}


void robotJointControl::goalPos(std::string joint_name, double joint_send_value, ros::Duration time_tot, ros::Rate rate)
{
	/*double val_j = getJoint(joint_name);
	double nb_mor = time_tot.toSec()/dt.toSec();
	double j_pos_mor = (joint_send_value - val_j)/nb_mor;
	for(int i = 0; i < nb_mor ; i++)
	{
		val_j += j_pos_mor;
		setJoint(joint_name, val_j);
		dt.sleep();
	}*/ //extrapolation lineaire
	joint_map_[joint_name]->goalPos(joint_send_value, time_tot, rate);
}

//COMPLETEZ LA FONCTION CI DESSOUS DE LA CINEMATIQUE INVERSE
void robotJointControl::IK(double xc, double yc, double zc, double thetac)
{
	double l1 = 0.8;
	double l2 = 0.4;
	double l3 = 0;

	double R = sqrt(xc*xc+yc*yc);
	double beta = acos((R*R-l1*l1-l2*l2)/(-2*l1*l2));
	theta2 = 3.1416 - beta;
	double lambda = atan2(yc,xc);
	double psi = asin((l2*sin(theta2))/R);
	theta1 = lambda - psi;

	ROS_INFO_STREAM("theta2 : " << theta2 << " theta1 : " << theta1);


}
