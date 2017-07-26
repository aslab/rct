package org.aslab.om.ecl.action;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */

/**
 * @author chcorbato
 *
 */
/**
 * @author chcorbato
 *
 */
public abstract class Action {
	
	/** 
	 * <!-- begin-UML-doc -->
	 * the identificator for the action, it is unique for a certain type of action (in the children of this)
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected short id;
	
	public Command command;
	
	/**
	 * the creation time of the action in millisecs
	 */
	protected long creation_time = 0;
	
	/**
	 * the time in millisecs when the action was sent to the actuator
	 */
	protected long commanded_time = 0;
	
	/** 
	 * <!-- begin-UML-doc -->
	 * upon creation, the number of ever issued action_list is incremented and 
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Action() {
		// begin-user-code
		creation_time = System.currentTimeMillis();
		id = addAction();	// assigns action id by incrementing the number of these actions (in children)
		// end-user-code
	}
	
	protected abstract short addAction();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return the unique identifier of the action
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public short getId() {
		// begin-user-code
		return id;
		// end-user-code
	}
	
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ActionStatus status = ActionStatus.PENDING; // to be updated by the actuator
	
	public ActionStatus getStatus() {
		return status;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * the action_list that must be completed before this one can be executed
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Action> required = new HashSet<Action>(); // action_list that need to be completed before this is executed

	protected Set<Action> requiring = new HashSet<Action>();
	
	public abstract ActionResult processResult(ActionFeedback feedback);
	
	public void addDependency(Action a){
		status = ActionStatus.WAITING;
		required.add(a);
		a.requiring.add(this);
	}
	
	private void removeRequired(Action a){
		required.remove(a);
		if ( required.isEmpty() && status == ActionStatus.WAITING )
			status = ActionStatus.PENDING;
	}
	
	/**
	 * set the action in SUCCESS status and propagates that to the requiring actions,
	 * by removing this one from their required
	 */
	protected void setSuccess(){
		status = ActionStatus.SUCCESS;
		for (Iterator<Action> iter = requiring.iterator(); iter.hasNext();){
			iter.next().removeRequired(this);
		}
	}
		
	/**
	 * set the action in FAILURE status and propagates that to the requiring actions
	 */
	protected void setFailure(){
		status = ActionStatus.FAILURE;
		for (Iterator<Action> iter = requiring.iterator(); iter.hasNext();){
			iter.next().setFailure();
		}
	}
	

	/**
	 * @return true if the action is pending (ready to be executed)
	 */
	public boolean isPending(){
		if ( status == ActionStatus.PENDING )
			return true;
		else
			return false;
	}
	
	/**
	 * <!-- begin-UML-doc -->
	 * this method encodes the model of the action regarding the time it takes to execute (i.e.)
	 * to be called from failureModel(), so as to include the timeOut in the action model of failure
	 * <!-- end-UML-doc -->
	 * @return true if the action has timed out
	 */
	protected abstract boolean timeOut();
	
	/**
	 * if the action is WAITING he method sets its status to PROCESSING and returns the commands
	 * otherwise it does nothing and returns null
	 * @return the command of the action
	 */
	public Command execute(){
		if ( status == ActionStatus.PENDING ){
			status = ActionStatus.PROCESSING;
			commanded_time = System.currentTimeMillis();
			return command;
		}
		else
			return null; // TODO raise exception??
	}

	
}
