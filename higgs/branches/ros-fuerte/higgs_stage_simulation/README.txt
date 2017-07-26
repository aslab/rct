author: Carlos Hernandez @ www.aslab.org
last modified: Feb 28 2013
status: works in ROS fuerte

DEPENDENCIES: see the manifest.xml


RATIONALE
=========
Package for simulating higgs with stage. It contains stage configurations files for that,
and launch files to facilitate running the simulation.


LAUNCH FILES
============
+ higgs_stage.launch - launches a stage simulation with higgs in the willow garage

+ higgs_stage_patrol.launch - launches the same simulation than "higgs_stage.launch", but it also
							  launches the navigation system for higgs and the mission_manager for
							  patrolling that willow lab room.

MAPS
====
the files in the "maps" folder are maps for the navigation system, and not for the simulation
+ willow_room.yaml - the map of a room of the Willow Garage
+ sala_completa.yaml - the map of the sala de calculo @ ASLab
+ map.yaml - another map of the room of the Willow garage


STAGE WORLDS
============
the configuration files for stage are in the folder "stage_files"
+ willow-higgs.world - contains a simulation of the Willow Garage with Higgs with the SICK LMS laser
+ willow-higgs-kinect.world - contains a simulation of the Willow Garage with Higgs with the Kinect
+ willow-full.pgm - is the map used to siumlate the Willow Garage in all the simulations