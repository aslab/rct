package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;



// application dependent class that encodes model of the fake laser component

/** 
 * <!-- begin-UML-doc -->
 * class to create the object corresponding to the ComponentClass fake_kinect
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class FakeKinectLaserModel extends RosNode {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FakeKinectLaserModel() {
		super("/fake_kinect_scan_node");
		
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.IN, "/base_scan", "sensor_msgs/LaserScan", this )
		);		
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/scan", "sensor_msgs/LaserScan", this )
		);	
		
		this.deploymentInfo.put("rospackage", "OM_Testbed2");
		this.deploymentInfo.put("launchfile", "fake_kinect_laser.launch");
		// end-user-code
	}
	
	
	/** specific recognize method for the perception of fake kinect
	 * @see org.aslab.om.metacontrol.knowledge.components.OMComponentClass#recognize(org.aslab.om.ecl.perception.Singularity)
	 */
	@Override
	public double recognize(Singularity s){
		ComponentSingularity sing = (ComponentSingularity) s;
		
		/* TODO: this shall go in a more general class
		 * when the sing is that of missing, the check is softer
		 * although we suppose the instance must have the type name
		 * see the final return comment
		 */
		if ( sing.status == ComponentStatus.MISSING ){
			if ( sing.name.equals(this.name) )
				return 1;
			else
				return 0;
		}
		
		// the faked kinect has no parameters
		if( !sing.parameters.isEmpty() )
			return 0;
		
		// the faked kinect has this two ports
		if ( !sing.ports.containsKey("/base_scan") ||
				!sing.ports.containsKey("/scan")	)
			return 0;
				
		return 1; // TODO maybe here call the super.recognize()
	}

}
