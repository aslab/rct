package org.aslab.om.ecl.action;

/** 
 * <!-- begin-UML-doc -->
 * class to encode the information in the scope of the actuator
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class Command {

	/** 
	 * <!-- begin-UML-doc -->
	 * the identificator integer of the action that corresponds to this command
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected short actionID;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return the unique identifier of the ReconfigurationCommand
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public short getId() {
		// begin-user-code
		return actionID;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * upon creation, the identificator of the action is passed to the command 
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Command(short id) {
		actionID = id;
	}
	
	/**
	 * for debugging purposes
	 */
	public abstract void print();


}
