package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMPortProfile;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;



// application dependent class that encodes model of the fake laser component

/** 
 * <!-- begin-UML-doc -->
 * class to create the ComponentClass object for the stageros Ros component
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class StageROS extends RosNode {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public StageROS() {
		super("/stageros");
		
		// PORTS
		this.portProfiles.add(
				new OMPortProfile(Directionality.OUT, "/base_scan", "sensor_msgs/LaserScan", this )
		);	
		
		this.deploymentInfo.put("rospackage", "OM_Testbed2");
		this.deploymentInfo.put("launchfile", "stageros.launch");
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
