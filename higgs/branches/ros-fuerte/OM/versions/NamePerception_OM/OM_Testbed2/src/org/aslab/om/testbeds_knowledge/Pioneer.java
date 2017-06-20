package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;

public class Pioneer extends RosNode {

	public Pioneer() {
		super("/pioneer");
		
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/pioneer/odom", "nav_msgs/Odometry", this )
		);	
		
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/tf", "tf/tfMessage", this )
		);	
		
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/pioneer/cmd_vel", "geometry_msgs/Twist", this )
		);	
		
		this.deploymentInfo.put("rospackage", "OM_Testbed2");
		this.deploymentInfo.put("launchfile", "pioneer.launch");
	}
	
	/** specific recognize method for the perception of stageros
	 * @see org.aslab.om.metacontrol.knowledge.components.OMComponentClass#recognize(org.aslab.om.ecl.perception.Singularity)
	 */
	@Override
	public double recognize(Singularity s){		
		ComponentSingularity sing = (ComponentSingularity) s;
		
		/* TODO: this shall go in a more general class
		 * when the sing is that of missing, the check is softer
		 * although we suppose the instance must have the type name
		 */
		if ( sing.status == ComponentStatus.MISSING ){
			if ( sing.name.equals(this.name) )
				return 1;
			else
				return 0;
		}
	
		// pioneer has 1 port named  odom" (Conditions to identify the singularity)
		if ( !sing.ports.containsKey("odom"))
			return 0;
		 
		else return super.recognize(sing);
	
	}

}
