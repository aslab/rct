author: Carlos Hernandez @ www.aslab.org
last modified: Feb 28 2013


RATIONALE
=========
This eclipse project contains all the assets needed for the OM Testbed2


CONTENTS:
=========
* src/om_testbed2 : a java package containing classes for metacontroller knowledge in the OM testbed2
* rosnodes : python Ros nodes required for the testbed2 application
* launch : Ros launch files for the different OM testbed2 scenarios

REQUIREMENTS:
=============
The following ASLab packages are needed
OMJava
OMRosDrivers_py
OMRosMetacontrol

And the following ROS dependencies:
stageros package
navigation stack


om_testbed java package
-----------------------
Compilation is a bit complicated:
1) you need to have installed OMJava and rosjava (the Ros stack for Java)
2) We use gradle to build this rosjava package, the configuration for the build is defined in the build.gradle file
To generate the eclipse configuration we have added this line: apply plugin: 'eclipse'
(for details see http://docs.rosjava.googlecode.com/hg/rosjava_core/html/getting_started.html)

Now build it and create an eclipse configuration for the project:
$ ../rosjava_core/gradlew install
$ ../rosjava_core/gradlew eclipse

Now you can work from within eclipse with the projects, just import it to your workspace
(if not already done so), and fix the project properties:
 -define the source folder (/src)
 -add OMJava as a referenced project project in the Java Build Path in the project properties.


rosnodes/initial_pose.py
------------------------
Ros node that initializes the localization system (/amcl node) by sending a message with the initial position of the robot in the scenario


launch directory contains Ros launch files for the different testbeds
---------------------------------------------------------------------
+ testbed2a.launch
+ testbed2b.launch
+ testbed2ac.launch
these files launch the metacontrol I/O and the corresponding testbed control system.

There are launchfiles named application_system_testbedXX.launch, that launch the control system of each testbed

+ higgs_nav_sys.launch
	launches the ROS navigation stack nodes configured for the higgs stage simulation

There are other atomic launchfiles to be used by the metacontrol to launch each of the nodes if they have to:
(these files have a similar version in the corresponding ROS package, but these copies are for the OM metacontroller to use?) - CH not sure about this, have to check with the java classes

+ fake_kinect_laser.launch
	launches the simulated kinect driver to obtain scans (the kinect as a laser)
	
+ fake_laser.launch
	launches the simulated laser driver. It needs that there exists the empty file OM_Testbed2/aux/laser_port to run (the file simulates the mount point)
	
+ initial_pose.launch

+ mission_manager.launch

+ move_base.launch

+ stageros.launch
	to launch the stageros simulation with the world file (rospackage higgs_stage_sim)/stage_files/willow-higgs.world
	It has one argument VISUAL to allow to display the stage GUI
	so if 
	$ roslaunch OM_Testbed2 stageros.launch
	no GUI is displayed
	but with:
	$ roslaunch OM_Testbed2 stageros.launch VISUAL:="-"
	the stage GUI is displayed


RUNNING the testbeds
--------------------
To run any of the testbeds:
0 Required packages: OMJava, OMRosDrivers_py, OMRosMetacontrol
1 Use roslaunch command to launch the desired testbed
2 Execute the OMRosMetacontrol from Eclipse (see OMRosMetacontrol/README.txt)

To make the fake_laser node fail permanently, just remove the OM_Testbed2/aux/laser_port file

