#!/bin/bash

clear

echo "Launch Rostopic Global."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_global.sh
echo "Launch Rostopic Local."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_local.sh
echo "Launch Rostopic Gps."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_gps.sh
echo "Launch Rostopic Odom."
gnome-terminal -e /home/pmcrivet/ros_workspace/src/arion/launch/Rostopic/rostopic_odom.sh


