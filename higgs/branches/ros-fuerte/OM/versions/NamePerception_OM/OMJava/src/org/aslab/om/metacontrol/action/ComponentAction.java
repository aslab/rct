/**
 * 
 */
package org.aslab.om.metacontrol.action;


import org.aslab.om.ecl.action.*;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;
import org.aslab.om.metacontrol.value.ComponentDifference;


/** 
 * <!-- begin-UML-doc -->
 * this class is the internal representation of an action in the ComponentsECL, consisting basically of the
 * action command and attributes with additional info, such as the component spec it addresses (target)
 * and action_list that must be completed before this one is executed.
 * 
 * <p>This class follows the following state machine:</p> * 
 * <img src="doc-files/ComponentAction-1.gif">
 * 
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentAction extends Action {
	
	/**
	 * generic model for component action timeout failure: 3000 millisecs
	 */
	private static final long ACTION_TIMEOUT = 3000;
	
	/** 
	 * <!-- begin-UML-doc -->
	 * number of ever issued action_list (this way a new number is assigned to everyone upon creation)
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private static short num_of_actions = 0;
	
	@Override
	protected short addAction(){
		return num_of_actions++;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private CompGoalAtomTracker target; // the goal atom this action addresses
	
	/** 
	 * <!-- begin-UML-doc -->
	 * This constructor actually encodes the inverse model for action_list on components
	 * <!-- end-UML-doc -->
	 * @param target TODO eliminate? use info from difference?
	 * @param difference a difference about components from which to generate the action
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentAction(CompGoalAtomTracker target, ComponentDifference difference) {
		// begin-user-code
		super();
		this.target = target;
		command = calculateCommand(difference);
		// end-user-code
	}
	
	
	/**
	 * actual implementation inverse model of action_list at the component level
	 * the action command is produced by using the difference
	 * for the moment only LAUNCH and RECONFIGURATION are implemented
	 * and RECONFIGURATION only partially, based on the existence of already prepared launchfiles
	 * with the alternative configuration
	 * @param d a difference at the components level (in between a component spec and an observed component)
	 * @return the
	 */
	private ReconfigurationCommand calculateCommand(ComponentDifference d){
		ReconfigurationCommand c = new ReconfigurationCommand(id);
		
		// case 1: no reference component in the state, or missing -> LAUNCH a new instance
		if (d.getReference() == null
				|| d.getReference().getStatus() == ComponentStatus.MISSING) {

			// launch new instance
			c.type = ComponentActionType.LAUNCH;
			c.arguments.put("rospackage",
					d.getDueValue().getComponentClass()
							.getDeploymentInfo().get("rospackage"));
			c.arguments.put("launchfile",
					d.getDueValue().getComponentClass()
							.getDeploymentInfo().get("launchfile"));
			return c;
		}
		
		// case 2: component in bad status, but no wrong configuration
		//			restart component
		else if (d.getReference().getStatus() == ComponentStatus.ERROR
				&& !d.wrongConfiguration()) {
			c.type = ComponentActionType.RESTART;
			c.arguments.put("rospackage",
					d.getDueValue().getComponentClass()
							.getDeploymentInfo().get("rospackage"));
			c.arguments.put("launchfile",
					d.getDueValue().getComponentClass()
							.getDeploymentInfo().get("launchfile"));
			
			return c;
		}

		// otherwise RECONFIGURE component
		else {
			// TODO : make more general by parsing arguments for the reconfiguration from the differences
			// for the moment it is simplified to pass the same arguments as for LAUNCH: the package
			// and a special launchfile which contains the configuration for this reconfig

			c.type = ComponentActionType.RECONFIGURE;
			c.target = d.getReference().getName();
			c.arguments.put("rospackage", d
					.getReference().getComponentClass().getDeploymentInfo()
					.get("rospackage"));
			c.arguments.put("launchfile", d
					.getReference().getComponentClass().getDeploymentInfo()
					.get("launchfile"));
			return c;
		}
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * @return&nbsp;the&nbsp;target
	 * <!-- end-UML-doc -->
	 * @return the target of this action
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public CompGoalAtomTracker getTarget() {
		// begin-user-code
		return target;
		// end-user-code
	}
	
	/**
	 * for debugging purposes
	 */
	public void print(){
		System.out.printf("Action ID: %d \t %s \n", id, getStatus());
		command.print();
	}
	
	
	/**
	 * processes the feedback received from the PlantAPI about the execution of this action
	 * propagating its consequences to depending actions
	 * @see org.aslab.om.ecl.action.Action#processResult(org.aslab.om.ecl.action.ActionFeedback)
	 */
	@Override
	public ActionResult processResult(ActionFeedback feedback) {
		if( feedback.result == ActionResult.SUCCEEDED )
			setSuccess();
		else if ( feedback.result == ActionResult.FAILED )
			setFailure();
		return feedback.result;
	}

	/** the timeout for component actions consists of the action not reaching a SUCCESS status 
	 * before ACTION_TIMEOUT
	 * this method sets the action in failure in that case
	 * @see org.aslab.om.ecl.action.Action#timeOut()
	 */
	@Override
	public boolean timeOut() {
		if( getStatus() != ActionStatus.SUCCESS &&
				(System.currentTimeMillis() - commanded_time > ACTION_TIMEOUT)
			){
			setFailure();	
			return true;
		}
		return false;
	}
	
	/**
	 * this method encodes the model of actions for components regarding what can be inferred from
	 * their feedback
	 * this is too Ros specific, so it should be moved somewhere else Ros-specific and invoked from here
	 * @param feedback the feedback received for this action
	 */
	public void failureModel(ActionFeedback feedback){
		if( feedback == null )
			throw new NullPointerException("no feedback provided");
		
		// if the action could not be executed
		if( feedback.result == ActionResult.FAILED ){
			setFailure();
			/* TODO improve - we should check the log
			 * for the moment if launch or reconfiguration failed, then:
			 * - the target cannot be achieved and is declared in error
			 * - the component class of the target of the action is unavailable
			 */ 
			if( ((ReconfigurationCommand) this.command).type == ComponentActionType.LAUNCH ||
				((ReconfigurationCommand) this.command).type == ComponentActionType.RECONFIGURE
				){
				this.target.setError();	// TODO this should be done in the evaluation, shouldn't it?
				this.target.componentSpec.getComponentSpec().getComponentClass().setUnavailable();
			}
						
		}
			
	}


}