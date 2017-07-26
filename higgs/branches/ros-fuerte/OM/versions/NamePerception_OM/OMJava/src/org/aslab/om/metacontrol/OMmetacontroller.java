/**
 * 
 */
package org.aslab.om.metacontrol;

import org.aslab.om.ecl.Goal;
import org.aslab.om.metacontrol.knowledge.components.OMcomponentsKB;


/** 
 * <!-- begin-UML-doc -->
 * <p>The OMmetacontroller consists of two control loops, one for maintaining a required state of functions and another a certain state of components (typically that commanded by the loop maintaining the functions)</p><p>It provides a constructor method and methods for controlling the start/stop of the operation of the loops, and enable or disable their ability to actuate on the controlled system.</p>
 * <p>@author chcorbato</p>
 * <!-- end-UML-doc -->
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMmetacontroller {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>the active instance that encapsulates the control loop for components</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ComponentsECL componentsECL;

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>attribute to hold on a reference to the mission of the metacontroller. This may disappear, since probably the mission of the OMmetacontroller will be explicitly coded. Theoretically its mission/goal/objective is to maintain the directivity of its controlled system (plant), that its, the convergence of its behaviour towards its objectives (i.e. the mission of the plant). It will do so by actuating on the plant's structure.</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Goal mission; // TODO eliminate, auxiliary to hold a dumb goal
	
	private OM_KDB knowledge;

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>the active instance that encapsulates the control loop for functions</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private FunctionalECL functionalECL;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private PlantAPI plant;

	/** 
	 * <!-- begin-UML-doc -->
	 * an OMmetacontroller is initialized by giving it:
	 * <!-- end-UML-doc -->
	 * @param m a mission or goal
	 * @param kb the knowledge database
	 * @param p the (domain controller)plant it (meta)controls
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMmetacontroller(Goal m, OM_KDB kb, PlantAPI p) {
		// begin-user-code
		mission = m;
		knowledge = kb;
		plant = p;

		componentsECL = new ComponentsECL((OMcomponentsKB) kb.ckb, plant);
		functionalECL = new FunctionalECL( componentsECL );

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method to initiate the operation of the OMmetacontroller</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void start() {
		// begin-user-code
		//TODO Goal is to be loaded from file? and then set for the functionsECL

		functionalECL.startECL();

		componentsECL.startECL();

		if (mission instanceof FunctionalGoal)
			functionalECL.setGoal(mission);
		else if (mission instanceof ComponentsGoal)
			componentsECL.setGoal(mission);
		else
			System.out.println("invalid mission");
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method to stop the operation of the OMmetacontroller. Its internal state is lost, so to put it back in operation start() must be called (not just enable)</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void stop() {
		// begin-user-code
		functionalECL.stopECL();
		componentsECL.stopECL();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>enable() puts the metacontroller in an state in which it can actuate on its plant</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void enable() {
		// begin-user-code
		componentsECL.startECL();
		functionalECL.startECL();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>this method causes the metacontroller not to be able to actuate on its plant. Apart from that, it operates normally, reading from its sensors and maintaining any internal state it may have.</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void disable() {
		// begin-user-code
		functionalECL.pauseECL();
		componentsECL.pauseECL();
		// end-user-code
	}
	
	/**
	 * for debugging purposes
	 */
	public String getCompEstimatedState(){
		return knowledge.ckb.getEstimatedState().toString();
	}
}