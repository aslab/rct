package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;


public class MissionManager extends RosNode {
	
	public MissionManager() {
		// begin-user-code
		super("/move_base_node");
				
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/move_base/goal", "move_base_msgs/MoveBaseActionGoal", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/move_base/cancel", "actionlib_msgs/GoalID", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/scan", "sensor_msgs/LaserScan", this )
		);		
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/amcl_pose", "geometry_msgs/PoseWithCovarianceStamped", this )
		);	
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/tf", "tf/tfMessage", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/move_base/feedback", "actionlib_msgs/GoalID", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/move_base/status", "actionlib_msgs/GoalID", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/move_base/result", "actionlib_msgs/GoalID", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/pioneer/cmd_vel", "tf/tfMessage", this )
		);
		
		this.deploymentInfo.put("rospackage", "OM_Testbed2");
		this.deploymentInfo.put("launchfile", "mission_manager.launch");
		// end-user-code
	}

}
