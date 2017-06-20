package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;


public class Amcl extends RosNode {
	
	public Amcl() {
		super("/amcl");
		
		// for the moment it is better not to put this "virtual" parameter
		//this.parameterProfiles.add(new ParamAmclMode());
		
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/scan", "sensor_msgs/LaserScan", this )
		);
		
		this.portProfiles.add(
				new OMPortProfile(Directionality.INOUT, "/tf", "tf/tfMessage", this )
		);

		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/tf", "tf/tfMessage", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/amcl_pose", "geometry_msgs/PoseWithCovarianceStamped", this )
		);	
		
		this.deploymentInfo.put("rospackage", "OM_Testbed2");
		this.deploymentInfo.put("launchfile", "amcl.launch");
	}

}
