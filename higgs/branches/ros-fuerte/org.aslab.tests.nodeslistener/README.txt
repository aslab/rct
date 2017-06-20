Author: Carlos Hernandez @ www.aslab.org
date: Feb 19 2013

INFO
====
This project contains a test to validate the configuration of a rosjava project for fuerte

DOCUMENTATION
=============
More documentation about this project and other projects related to the OM Architecture can be found at:
svn+ssh://chcorbato@software.aslab.upm.es/home/svnroot/people/chcorbato/models/OM_Models/docs


REQUIREMENTS
============
1- System requirements: Ubuntu Lucid 10.04, Ros-fuerte, eclipse, svn
2- rosjava_core: Ros stack for java (rosjava)


COMPILATION
===========

Compilation is a bit complicated:
1) you need to have installed meta_msgs and rosjava_core (the Ros stack for Java)
2) We use gradle to build this rosjava package, the configuration for the build is defined in the build.gradle file
To generate the eclipse documentation we have added this line: apply plugin: 'eclipse'
(for details see http://docs.rosjava.googlecode.com/hg/rosjava_core/html/getting_started.html)

Now build it and create an eclipse configuration for the project:
$ ../rosjava_core/gradlew installApp
$ ../rosjava_core/gradlew eclipse

Now you can work from within eclipse with the projects, just import it to your workspace
(if not already done so), and fix the project properties if needed, for example define the
source folder (/src)

IMPORTANT
=========
remember that each time you change the message types you have to rebuild them:
1. rosmake the package with the definition of the messages
2. rebuild the rosjava_messages package:
 $ roscd rosjava_messages
 $ ../gradlew install


USAGE
=====

To debug the application in eclipse:
-create a Run configuration RosRun
	main class: org.ros.RosRun
	program argument: org.aslab.tests.nodelistener.NodeListener
-use that configuration to run and debug the ros node from eclipse

