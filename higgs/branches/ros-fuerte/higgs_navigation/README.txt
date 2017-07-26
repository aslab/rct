Authors: Carlos Hernandez Alberto Gonzalez @ www.aslab.org

This readme gives information about the purpose and usage of higgs_navigation, which describes the plant we are going to control, along with the navigation system implemented.
It also includes different rviz configs for displaying different informations.
It also includes the configuration parameters for our sensors, map and Higgs platform which are used for the navigation implementation.


PURPOSE
=======
This project mainly contains launch files for the usage of Higgs. Which comprehends the pioneer base and the different sensors on Higgs.
Basically launches nodes for the different sensors on-board Higgs and for navigation purposes. 

USAGE
=====

Launch files
	corrected_odometry.launch --
	
	higgs_app_navigation.launch -- Is the main launch file for our hole application. Launches higgs_nav_sys.launch and higgs_rover.launch (details below)
									along with the map server and rviz so you can visualize the data you should be receiving if everything is working properly.
									There are 4 main arguments:
									KINECT (Uses kinect sensor) default:false
									KIN_LOC (Uses kinect for localization) default:false 
									LASER (Uses laser for localization) default:true
									EKF (Improves localization when KIN_LOC true using the compass included in the higgs_arduino_corba_ros) default:false
									RVIZ (used to define our .vcg config for rviz. default:all
										
	higgs_nav_sys.launch -- Is the main lauch file for Higgs navigation system. There are 3 main arguments:
							 KINECT (¿?) default: true
							 KIN_LOC (Uses kinect for localization) default:false
							 EKF (Improves localization when KIN_LOC true using the compass included in the higgs_arduino_corba_ros) default:false
	
	higgs_rover.launch -- Is the main lauch file for our Higgs control system. There are 4 main arguments:
							KINECT (Uses kinect sensor) default:false
							KIN_LOC (Uses kinect for localization) default:false 
							LASER (Uses laser for localization) default:true
							EKF (Improves localization when KIN_LOC true using the compass included in the higgs_arduino_corba_ros) default:false
						   
						   Includes the static tf transformations needed for higgs and its different sensors using /base_link as the reference frame for them.
						   Depending on the value of the different arguments this launch file launches:
						   	(find pioneer_aria)/launch/pioneer.launch --- launch file for pioneer base interface
						   	(find higgs_laser)/launch/laser.launch --- launch file for sicklms200 laser interface
							(find openni_launch)/launch/openni.launch --- launch file for kinect interface
							(find higgs_kinect)/launch/cloudthrottle.launch ---
							(find higgs_kinect)/launch/kinect_obstacles.launch ---
							(find higgs_kinect)/launch/kinect_references.launch ---

Configuration files
	config_nav -- Contains the different configuration files for the sensors, map, navigation...

	config rviz -- Contains different rviz configuration for visualizing different information

Map
	Contains our map files with its configuration parameters.
