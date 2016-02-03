#!/bin/bash

clear

echo "Launch Rostopic Local."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_local.sh
echo "Launch Rostopic Imu."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_imu.sh
echo "Launch Rostopic Odom."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_odom.sh


