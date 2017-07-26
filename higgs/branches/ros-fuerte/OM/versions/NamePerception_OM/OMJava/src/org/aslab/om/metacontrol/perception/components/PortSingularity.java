package org.aslab.om.metacontrol.perception.components;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.perception.Singularity;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class PortSingularity extends Singularity {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param connection
	 * @param direction
	 * @param type
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public PortSingularity(Directionality direction, String type, String connection) {
		// begin-user-code
		super();
		this.direction = direction;
		this.type = type;
		this.connectionName = connection;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Directionality direction;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String type;
	
	public String connectionName;

}
