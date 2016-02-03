 /*
Code for GEI745, ROS pick and place plateform.
Author: Tristan Crossman, Tristan.Crossman@Usherbrooke.ca
License: BSD

Vers: 0.0.1
Date: 13/11/14
*/

#include "robotJoint.h"

robotJoint::robotJoint(std::string joint_name, ros::NodeHandle* node, int rate)
{
	robot_joint_name_ = joint_name;
	std::ostringstream joint_name_command_;
	std::ostringstream joint_name_state_;
	
	joint_name_command_ << "/robot/" << robot_joint_name_.c_str() << "_position_controller/command";
	joint_name_state_ << "/robot/" << robot_joint_name_.c_str() << "_position_controller/state";
	
	rate_ = rate;
	stop_thread_ = false;
	first_msg = false;
	
	joint_pub_ = node->advertise<std_msgs::Float64>(joint_name_command_.str().c_str(), 1000);
	joint_sub_ = node->subscribe(joint_name_state_.str().c_str(), 1000, &robotJoint::robotCallback, this);
}

robotJoint::~robotJoint()
{
	//mutex_.lock();
	stop_thread_ = true;
	//mutex_.unlock();
}

double robotJoint::getJoint()
{
	return joint_value_;
}

std::string robotJoint::getName()
{
	return robot_joint_name_.c_str();
}

void robotJoint::setJoint(double joint_send_value)
{
	//mutex_.lock(); //prevent multiple threads
	send_value_ = joint_send_value;
	//mutex_.unlock();
	ROS_INFO("Joint %s just send: %f", robot_joint_name_.c_str(), joint_send_value);
}

//Utile?
bool robotJoint::initEnd()
{
	return first_msg;
}

void robotJoint::robotCallback(const control_msgs::JointControllerState::ConstPtr& msg_in)
{
	joint_value_ = msg_in->set_point;
	if(!first_msg)
	{
		send_value_ = joint_value_;
		thread_pub_ = new boost::thread(&robotJoint::pubThread, this, rate_);
		first_msg = true;
		ROS_DEBUG("Start thread");
	}
}

void robotJoint::pubThread(int rate)
{
	bool kill_me = false;
	ros::Rate loop_rate(rate);
	while (ros::ok())
	{
		//mutex_.lock();
		msg_out_.data = send_value_;
		kill_me = stop_thread_;
		//mutex_.unlock();
	
		joint_pub_.publish(msg_out_);
		
		ros::spinOnce();
		
		loop_rate.sleep();
		
		if(kill_me)
			break;
	}
}

void robotJoint::goalPos(double j_val, ros::Duration tf, ros::Rate rate)
{
	thread_goal_ = new boost::thread(&robotJoint::cubic_trajectory, this, j_val, tf, rate);
}

//COMPLETEZ LA FONCTION PERMETTANT DE GENERER UNE TRAJECTOIRE POLYNOMIALE CUBIQUE
void robotJoint::cubic_trajectory(double j_fin, ros::Duration tf, ros::Rate rate)
{
}
