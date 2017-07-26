/*
   Authors
        Carlos Hernandez	@ ASLab - UPM    www.aslab.org
	Francisco J. Arjonilla @ ASLab - UPM    www.aslab.org

   Parameters:
   	   for published transformation frames and default values
		odom_frame "odom"
		base_frame "/base_footprint"

*/

#include <sstream>
#include <stdio.h>
#include <math.h>
#include <Aria.h>

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Range.h"
#include "tf/tf.h"
#include "tf/transform_datatypes.h"

#include <tf/transform_broadcaster.h>


class ActionPause : public ArAction
{
public:
  // constructor, sets myMaxSpeed and myStopDistance
  ActionPause(double time);
  // destructor. does not need to do anything
  virtual ~ActionPause(void) {};
  // called by the action resolver to obtain this action's requested behavior
  virtual ArActionDesired *fire(ArActionDesired currentDesired);
protected:
  double pauseTime;
  ArActionDesired myDesired;
};

ActionPause::ActionPause(double time) :
  ArAction("Pause")
{
  pauseTime = time;
  myDesired.reset();
}

ArActionDesired *ActionPause::fire(ArActionDesired currentDesired)
{
  ros::Duration(pauseTime).sleep();
  return &myDesired;
}


class PioneerNode
{
  public:
    PioneerNode(ros::NodeHandle n);
    virtual ~PioneerNode();
    
  public:
    int Setup();
    void cmdvel_cb( const geometry_msgs::TwistConstPtr &);
    void spin();
    void publish();

  protected:
    ros::NodeHandle n;
    ros::Publisher pose_pub;
    ros::Publisher sonar_pub;
    ros::Subscriber cmdvel_sub;	// to receive velocity command
    // ros::Subscriber maxvel_sub;	// to receive set up of max velocity

    tf::TransformBroadcaster broadcaster;

    ros::Time current_time;
    ros::Time veltime;          // probably to eliminate

    // node parameters
    std::string serial_port;
    std::string baud_rate;
    bool sonar_active;
    std::string odom_frame;
    std::string base_frame;
    bool tf_broadcast;

    ArSimpleConnector *conn;
    ArRobot *robot;
    ArSonarDevice* sonar;
    ActionPause *pause;
    nav_msgs::Odometry odom;
    sensor_msgs::Range sonar_readings;
    ArPose pos;
    ArFunctorC<PioneerNode> myPublishCB;
};

PioneerNode::PioneerNode(ros::NodeHandle nh) :
  myPublishCB(this, &PioneerNode::publish)
{
  // read in config options
  n = nh;

  // !!! ASLab default port is /dev/ttyUSB0, and default baud rate is 57600
  n.param( "port", serial_port, std::string("/etc/higgs/devices/higgs_dev") );
  n.param( "baudRate", baud_rate, std::string("57600") );
  n.param( "sonar", sonar_active, true );
  n.param( "odom_frame", odom_frame, std::string("odom") );
  n.param( "base_frame", base_frame, std::string("base_footprint") );
  n.param( "tf_odom_broadcast", tf_broadcast, true );

  ROS_INFO( "using serial port: [%s]", serial_port.c_str() );

  // advertise published topics
  pose_pub = n.advertise<nav_msgs::Odometry>("odom",1000);
  if (sonar_active)
      sonar_pub = n.advertise<sensor_msgs::Range>("sonar",1000);

  // subscribe to topics
  cmdvel_sub = n.subscribe( "cmd_vel", 1, (boost::function < void(const geometry_msgs::TwistConstPtr&)>) boost::bind( &PioneerNode::cmdvel_cb, this, _1 ));
  
  veltime = ros::Time::now();
}

PioneerNode::~PioneerNode()
{
  if(sonar_active){
	  robot->comInt(ArCommands::SONAR, 0);
  	  robot->remRangeDevice(sonar);
  }
  delete sonar;

  robot->stopRunning();
  robot->waitForRunExit();
  Aria::shutdown();
}

int PioneerNode::Setup()
{
  ArArgumentBuilder *args;
  args = new ArArgumentBuilder();
  args->add("-rp"); //pass robot's serial port to Aria
  args->add(serial_port.c_str());
  args->add("-rb");
  args->add(baud_rate.c_str());
  args->add("-rlpr"); //log received packets
  args->add("-rlps"); //log sent packets
  args->add("-rlvr"); //log received velocities
  conn = new ArSimpleConnector(args);

  ArLog::init(ArLog::File, ArLog::Verbose, "aria.log", true);

  robot = new ArRobot();
  pause = new ActionPause(4e-3);
  if (sonar_active){
	  sonar = new ArSonarDevice();
	  robot->addRangeDevice(sonar);
	  sonar->setRobot(robot);
  }

  // Connect to the robot
  if (!conn->connectRobot(robot)) {
    ArLog::log(ArLog::Terse, "rotate: Could not connect to robot! Exiting.");
    return 1;
  }

  // ASLab
  // set max-velocities
  robot->setRotVelMax(28.65); // 0.5 rad/s
  robot->setTransVelMax(250);
  robot->setAbsoluteMaxTransAccel(1000);
  robot->setAbsoluteMaxRotAccel(180);

  ROS_INFO("Max acc: %f \n",robot->getAbsoluteMaxTransAccel());
  ROS_INFO("Max rot_acc: %f \n",robot->getAbsoluteMaxRotAccel());

  // Enable the motors
  robot->enableMotors();
  //robot->comStrN(ArCommands::SAY, "\50\6\50\18\50\6\50\18\50\30\50\42", 12);

  // enable sonar if ROS parameter set so
  if(sonar_active)
	  robot->comInt(ArCommands::SONAR, 1);
  else
	  robot->comInt(ArCommands::SONAR, 0);

  ROS_INFO(robot->areMotorsEnabled()?"Motors enabled": "Motors not enabled");
  ROS_INFO(robot->areSonarsEnabled() ? "Sonars enabled" : "Sonars not enabled");
  ROS_INFO("Number of sonars: %i\n", robot->getNumSonar());
  robot->addSensorInterpTask("PublishingTask", 100, &myPublishCB);
//  robot->addAction(pause, 10);
  robot->runAsync(true);

  return 0;
}

void PioneerNode::spin()
{
    while( n.ok() )
      {
	if(sonar_active) 
	  {
	    for (int i = 0; i < robot->getNumSonar(); i++)
		if (robot->isSonarNew(i))
		  {
		    current_time = ros::Time::now();
		    sonar_readings.header.stamp = current_time;
		    std::ostringstream frame_id;
		    frame_id << "sonar" << i;
		    sonar_readings.header.frame_id = frame_id.str().c_str();
		    sonar_readings.radiation_type = sensor_msgs::Range::ULTRASOUND;
		    sonar_readings.min_range = 0.05;
		    sonar_readings.max_range = 10.;
		    sonar_readings.range = (float)robot->getSonarRange(i) / 1000;
		    sonar_pub.publish(sonar_readings);
		  }
	  }

	ros::spinOnce();
      }
}

void PioneerNode::publish()
{
	current_time = ros::Time::now();

	//  robot->lock();
	pos = robot->getPose();
	//  robot->unlock();
	odom.header.stamp = current_time;
	odom.header.frame_id = odom_frame;

	// get orientation
	geometry_msgs::Quaternion orientation = tf::createQuaternionMsgFromYaw(pos.getTh()*M_PI/180);

	// get position
	odom.pose.pose.position.x = pos.getX()/1000;
	odom.pose.pose.position.y = pos.getY()/1000;
	odom.pose.pose.position.z = 0.0;
	odom.pose.pose.orientation = orientation;
	// covariances
	/* 						    0.025, 0.0, 0.0, 0.0, 0.0, 0.0,  ////[x, y, z, x, y, z]
		 	 	 	 	 	 	0.0, 0.025, 0.0, 0.0, 0.0, 0.0,
		 	 	 	 	 	 	0.0, 0.0, 1e-6, 0.0, 0.0, 0.0,
		 	 	 	 	 	 	0.0, 0.0, 0.0, 1e-6, 0.0, 0.0,
		 	 	 	 	 	 	0.0, 0.0, 0.0, 0.0, 1e-6, 0.0,
		 	 	 	 	 	 	0.0, 0.0, 0.0, 0.0, 0.0, 0.2                  */
	odom.pose.covariance[0] = odom.pose.covariance[7] = 0.025;
	odom.pose.covariance[14] = odom.pose.covariance[21] = odom.pose.covariance[28] = 1e-6;
	odom.pose.covariance[35] = 0.2;

	odom.pose.covariance[1] = odom.pose.covariance[2] = odom.pose.covariance[3] =
		odom.pose.covariance[4] = odom.pose.covariance[5] = odom.pose.covariance[6] = 0.0;
	odom.pose.covariance[8] = odom.pose.covariance[9] = odom.pose.covariance[10] =
		odom.pose.covariance[11] = odom.pose.covariance[12] = odom.pose.covariance[13] = 0.0;
	odom.pose.covariance[15] = odom.pose.covariance[16] = odom.pose.covariance[17] =
		odom.pose.covariance[18] = odom.pose.covariance[19] = odom.pose.covariance[20] = 0.0;
	odom.pose.covariance[22] = odom.pose.covariance[23] = odom.pose.covariance[24] =
		odom.pose.covariance[25] = odom.pose.covariance[26] = odom.pose.covariance[27] = 0.0;
	odom.pose.covariance[29] = odom.pose.covariance[30] = odom.pose.covariance[31] =
		odom.pose.covariance[32] = odom.pose.covariance[33] = odom.pose.covariance[34] = 0.0;


	// get velocity
	odom.twist.twist.linear.x = robot->getVel()/1000;
	odom.twist.twist.angular.z = robot->getRotVel()*M_PI/180;

	// covariances
						/*   0.01, 0.0, 0.0, 0.0, 0.0, 0.0,   //[vx, vy, vz, wx, wx, wz]
							 0.0, 0.01, 0.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 1e-6, 0.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 1e-6, 0.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 1e-6, 0.0,
							 0.0, 0.0, 0.0, 0.0, 0.0, 0.03          */
	odom.twist.covariance[0] = odom.twist.covariance[7] = 0.01;
	odom.twist.covariance[14] = odom.twist.covariance[21] = odom.twist.covariance[28] = 1e-6;
	odom.twist.covariance[35] = 0.03;

	odom.twist.covariance[1] = odom.twist.covariance[2] = odom.twist.covariance[3] =
		odom.twist.covariance[4] = odom.twist.covariance[5] = odom.twist.covariance[6] = 0.0;
	odom.twist.covariance[8] = odom.twist.covariance[9] = odom.twist.covariance[10] =
		odom.twist.covariance[11] = odom.twist.covariance[12] = odom.twist.covariance[13] = 0.0;
	odom.pose.covariance[15] = odom.pose.covariance[16] = odom.pose.covariance[17] =
		odom.twist.covariance[18] = odom.twist.covariance[19] = odom.twist.covariance[20] = 0.0;
	odom.twist.covariance[22] = odom.twist.covariance[23] = odom.twist.covariance[24] =
		odom.twist.covariance[25] = odom.twist.covariance[26] = odom.twist.covariance[27] = 0.0;
	odom.twist.covariance[29] = odom.twist.covariance[30] = odom.twist.covariance[31] =
		odom.twist.covariance[32] = odom.twist.covariance[33] = odom.twist.covariance[34] = 0.0;
  
	// publish odometry
	pose_pub.publish(odom);
	//ROS_INFO("rcv: %f %f %f", position.header.stamp.toSec(), (double) position.twist.twist.linear.x, (double) position.twist.twist.angular.z);


	// odometry tf published only if parameter set different than 0
	// tf from frame odom.header.frame_id to base_frame
	if( tf_broadcast ){
		tf::Quaternion odomQ;
		tf::quaternionMsgToTF(orientation, odomQ);
		broadcaster.sendTransform(
			tf::StampedTransform(
				tf::Transform(odomQ, tf::Point(pos.getX()/1000, pos.getY()/1000, 0.0)),
				odom.header.stamp, odom_frame, base_frame)
		);
	}


  ros::Duration(1e-3).sleep();
}

void
PioneerNode::cmdvel_cb( const geometry_msgs::TwistConstPtr &msg)
{
  veltime = ros::Time::now();
  //ROS_INFO( "new speed: [%0.2f,%0.2f](%0.3f)", msg->linear.x*1e3, msg->angular.z, veltime.toSec() );

//  robot->lock();
  robot->setVel(msg->linear.x*1e3);
  robot->setRotVel(msg->angular.z*180/M_PI);
//  robot->unlock();
  //ROS_INFO("snd: %f %f %f", veltime.toSec(), (double) msg->linear.x, (double) msg->angular.z);
}


int main( int argc, char** argv )
{
  ros::init(argc,argv, "pioneer");
  ros::NodeHandle n(std::string("~"));
  Aria::init();

  PioneerNode *node = new PioneerNode(n);

  if( node->Setup() != 0 )
  {
    printf( "setup failed... \n" );
    return -1;
  }

  node->spin();

  delete node;

  printf( "\nQuitting... \n" );
  return 0;
  
}
