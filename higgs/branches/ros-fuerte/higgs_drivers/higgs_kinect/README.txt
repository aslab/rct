Authors: Carlos Hernandez Alberto Gonzalez @ www.aslab.org

This readme gives information on the purpose and usage of higgs_kinect

PURPOSE
=======
This project contains mainly launch files for the usage of the kinect device sensor on higgs.
Basically launches kinect nodes for different purposes.

USAGE
=====
cloudthrottle.launch--
kinect_full.launch--
kinect_obstacles.launch--
kinect_openni.launch--
kinect_references.launch--
kinect_servo.launch--



TEST OUTPUT
===========

with the conditions given in Testbed1_KDB:

** Console *************************************************************************************
=== Component loop starts =====================
=== Functional loop starts =====================
k - kill demo
p - pause execution of metacontroller
r - restart the metacontroller
s - resume execution of the metacontroller
c - print components estimated state

--> Functional Action:
	/fake_laser_scan_node
    
==> New Goal ComponentLoop:
	/fake_laser_scan_node
    
action command:
	 kill component
	 	runtimeName :	/fake_laser_scan_node
action command:
	 launch component
	 	rospackage :	OM_Testbed2
	 	launchfile :	fake_laser_wrong.launch
	 	
*************************************************************************************************
explanation:
1- debug printings of the metacontroller initialization, indicating that both loops start running
2- instructions to interact with the application with the keyboard
3- indication that the functional loop has commanded an action
	this is because it detects a root objective for which there is no function instantiated, so it
	computes a design by selecting one appropriate to the objective in the KD
4- indication that the previous action has been received by the Component Loop as its new goal
5- commands sent by the Component Loop to the FakedRosAPI
	this is because the initial state of components (given in the KD, and which is the current 
	estimation because no sensing input is sent by FakedRosAPI) does not match the goal. The final
	state is the same, because the commanded actions only produce a printout. But no further 
	actions are taken nor the situation scales to the Functional Loop because the Component Loop
	knows that there is an error signal but it is addressed by actions that are still processing,
	since no feedback is received of either success or failure.
	I should add something in the Control Loop to address this impass, using maybe the derivative of
	the error signal or its integral.

