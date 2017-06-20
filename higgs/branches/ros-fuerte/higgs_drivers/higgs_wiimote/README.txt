author: Carlos Hernandez @ www.aslab.org
date: March 12 2013
status: compiles and works for ROS fuerte
future works: change the controls to be the joystick in the wii nunchuck,
			  instead of the accelerometers
			  provide ros log info of the operation of the wiimote
			  include visual feedback of the operating status of the wiimote using the leds

DEPENDENCIES: see the manifest.xml


RATIONALE
=========
This package contains a node (higgs_wiimote) that translates joy messages from a wii remote into
velocity commands for higgs


BUILD INSTRUCTIONS
==================
$ roscd higgs_wiimote
$ rosmake
To work with it in eclipse:
$ make eclipse-project

LAUNCHFILES
===========
+ higgs_wii.launch - main launchfile: launches the nodes required to send velocity commands from a 
                      wiimote
                      
+ higgs_wii_example.launch - example of how to include "higgs_wii.launch" in larger launchfiles for
                           your complete robotic system

+ wii_example.launch - example of how to launch the "wiimote_node.py" required to obtain the joystick
					   messages from the wiimote

RUNNING
=======
You need to run it in a computer with Bluetooth. 
Firstly launch in the robot computer (the asus connected to higgs):
$ roslaunch higgs_wiimote higgs_wii.launch
then follow the instructions to pair the wiimote with the computer
and now launch the robot drivers:
$ roslaunch higgs_navigation higgs_rover.launch