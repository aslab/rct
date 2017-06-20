package om_testbed1.knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;



// application dependent class that encodes model of the fake laser component

/** 
 * <!-- begin-UML-doc -->
 * class to create the ComponentClass object for the Gazebo component
 * <!-- end-UML-doc -->
 * @author agonzamart
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class GazeboROS extends RosNode {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public GazeboROS() {
		super("/Pioneer3AT_Gazebo");
		
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/Pionner3AT/pose", "nav_msgs/Odometry", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/tf", "tf/tfMessage", this )
		);
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/Pionner3AT/cmd_vel", "unknown type", this )
		);
		
		this.deploymentInfo.put("rospackage", "OM_Testbed1");
		this.deploymentInfo.put("launchfile", "/pioneer3at gazebo.launch");
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
	
		// stageros has 1 parameter named "baudrate"
		if ( !sing.parameters.containsKey("base_watchdog_timeout") ||
				sing.parameters.size() != 1	)
			return 0;
		
		else return super.recognize(sing);
	
	}

}
