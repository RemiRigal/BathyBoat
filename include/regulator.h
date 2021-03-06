#ifndef _REGULATOR_H
#define _REGULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <boost/algorithm/string.hpp>

#include "ros/ros.h"

// Quaternions
#include "tf/tf.h"
#include "tf2/LinearMath/Quaternion.h"

// FSM states
#include "../include/state.h" 

// Messages
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64MultiArray.h"
#include "BathyBoatNav/robot_state.h"
#include "BathyBoatNav/robot_target.h"

// Services


class Regulator{

	public: 
		Regulator();
	    virtual ~Regulator();
		void RunContinuously();
    
	private: 
		ros::NodeHandle Handle;

		// Simulation
		bool isSimulation;

		// Robot state variables
		State state;
		double x[3];
		double roll, pitch, yaw;
		double linear_speed[3];
		double angular_speed[3];

		// Robot target variables
		bool isLine;
		double x_target[3];
		double roll_target, pitch_target, yaw_target;
		double x_target_appoint[3];
		tf::Quaternion q_target_appoint;
		double linear_speed_target[3];
		double angular_speed_target[3];

		// Robot state
		ros::Subscriber robot_state_sub;
		void updateRobotState(const BathyBoatNav::robot_state::ConstPtr& msg);

		// Target
		ros::Subscriber robot_target_sub;
		void updateRobotTarget(const BathyBoatNav::robot_target::ConstPtr& msg);

		// Command
		double u_yaw, speed_bar;
		double full_left;
		ros::Publisher command_pub;
		void updateCommandMsg();
		void computeFixes();

		// Debug command
		ros::Publisher debug_pub;

		// PID
		double P, I;
		double k_P, k_I, k_D;
};

#endif