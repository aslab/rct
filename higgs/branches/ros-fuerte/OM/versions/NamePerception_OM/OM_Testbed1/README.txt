Author: Carlos Hernandez @ www.aslab.org

This readme gives information on the purpose and usage of this Java eclipse project

PURPOSE
=======
This project contains classes for the testbed1 of the OM project.
You can find more information about this project at:
svn+ssh://software.aslab.upm.es/home/svnroot/people/chcorbato/models/OM_Models/docs/

It is a basic test of the OM_Java/src/org.aslab.om.metacontrol.OMmetacontroller Java class that implements an OM metacontroller
It is connected to the FakedRosAPI that provides a dumb simulation for 

USAGE
=====
the classes of this project are in the om_testbed1 java package:
- FreeEvolutionTest is the class for the testbed1 application
- FakedRosAPI provides a dumb simulation of the monitoring and reconfiguring infrastructure for the Ros platform.
- Testbed1_KDB provides an initialization for the knowledge database with the knowledge (including functional goal and initial state) of the metacontroller

change Testbed1_KDB constructor for giving different initial conditions




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

