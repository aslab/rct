package org.aslab.om.ecl.action;

/** 
 * <!-- begin-UML-doc -->
 * enumeration to define the set of possible states for a command sent to the actuators
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public enum ActionStatus {
	/** 
	 * <!-- begin-UML-doc -->
	 * the action cannot be executed because it has some required actions
	 * <!-- end-UML-doc -->
	 */
	WAITING,
	
	/** 
	 * <!-- begin-UML-doc -->
	 * the actuator is performing the action
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	PROCESSING,
	
	/** 
	 * <!-- begin-UML-doc -->
	 * the action has been successfully executed
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	SUCCESS,
	
	/** 
	 * <!-- begin-UML-doc -->
	 * the action could not be executed by the actuator
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	FAILURE,
	
	/** 
	 * <!-- begin-UML-doc -->
	 * the action is ready to be executed
	 * <!-- end-UML-doc -->
	 */
	PENDING
}
