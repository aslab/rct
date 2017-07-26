/**
 * 
 */
package org.aslab.om.metacontrol;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.ecl.ECL;
import org.aslab.om.ecl.Goal;
import org.aslab.om.ecl.action.ActionFeedback;
import org.aslab.om.ecl.action.Actuator;
import org.aslab.om.ecl.perception.Sensor;
import org.aslab.om.metacontrol.action.ComponentAction;
import org.aslab.om.metacontrol.action.FunctionalAction;
import org.aslab.om.metacontrol.knowledge.components.OMcomponentsKB;
import org.aslab.om.metacontrol.perception.components.ComponentsPerceptor;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;


/** 
 * <!-- begin-UML-doc -->
 * <p>Implementation of a control loop for components</p>
 * <p>The ComponentsECL follows the operation schema in the ECL</p>
 * <p> @see org.aslab.om.ecl.ECL ECL<p>
 * <p>detailed description of {@linkplain org.aslab.om.ecl.perception.ExplicitPerception perception}, {@linkplain #evaluate() evaluation} and {@linkplain #control() control}</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentsECL extends ECL implements Sensor, Actuator {
	
	/**
	 * The ComponentsECL uses the PlantAPI as proprioception, since it provides action feedback
	 */
	private PlantAPI proprioceptor;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private OMcomponentsKB kdb;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param k
	 * @param plant TODO
	 * @param s
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentsECL(OMcomponentsKB k, PlantAPI plant) {
		// begin-user-code
		super("Components ECL", plant, plant);
		perceptor = new ComponentsPerceptor(plant, k);
		proprioceptor = plant;
		kdb = k;

		// for debugging
		System.out.println("=== Component loop starts =====================");
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void executeAction(Object a) {
		// begin-user-code
		// TODO code a proper action_list server ala ros?
		ComponentsGoal g = new ComponentsGoal(((FunctionalAction) a).atoms);
		setGoal(g);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Object getSensing() {
		// begin-user-code
		return kdb.getGoalState();

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param g
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public synchronized void setGoal(Goal g) {
		
		//TODO cleanly end loop thread and launch new one
		
		ComponentsGoal goalComp = (ComponentsGoal) g;

		// clean up internal state
		kdb.setGoal(goalComp);
		
		goal = goalComp;
		
		// Debug
		//System.out.println("==> New Goal for ComponentLoop:");
		//kdb.printGoal();		
		// end debug
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void perceive() {
		// begin-user-code
		perceptor.perceive();

		// for debugging
		//kdb.printEstimatedState();

		// this method processes the feedback from the PlantAPI
		proprioception();

		// TODO: other perception, like prediction
		
		// end-user-code
	}

	/**
	 * Method that retrieves the extant feedback from the PlantAPI corresponding buffer
	 * and processes it to:
	 * - identify to which action each entry in the buffer corresponds to
	 * - execute any model available for that feedback
	 * 
	 * it also executes any action model not depending of feedback, such as timeouts (still ToDo)
	 */
	private void proprioception() {
		if ( !kdb.actions() )
			return;
		
		Map<Short, ActionFeedback> feedback = proprioceptor.getFeedback();
		
		// TODO maybe move this to Reconfiguration?
		for (Iterator<ComponentAction> iter = kdb.getActions().iterator(); iter.hasNext();){
			ComponentAction action = iter.next();
					
			// obtain the feedback entry corresponding to this action if any and process it
			ActionFeedback afb = feedback.get(action.getId());
			if( afb != null ){				
				//System.out.println(" ---- GOT FEEDBACK -----");
				// process the feedback in terms of the status of actions in the action_plan
				action.processResult(afb);
				
				// here the error model for actions is used, e.g. to infer if a component class is no longer available 
				action.failureModel(afb);
			}

			action.timeOut();	// update action status according to timeout model
			
		}
		
	}

	// updates the level of achievement of the goal in the tracker structure
	// STATUS: under work 1st version
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>the evaluation method for the Components ECL follows this activity diagram</p>
	 * <img src="doc-files/ComponentsECL-1.gif">
	 * @throws NullPointerException when attribute goalState is null (loop has no goal)
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void evaluate() {
		// begin-user-code
		if (kdb.getGoalState() == null) // do not evaluate if there is no goal
			throw new NullPointerException("there is no goal");
		// compare state with goalInteger
		//kdb.matchSpecs2State(); // match components specs in the goal with perceived components in the state
		
		// evaluation is implemented within the ComponentsGoalTracker class
		kdb.updateEval();

		//goalState.print();
		
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>the control method for the Components ECL follows this activity diagram</p>
	 * <img src="doc-files/ComponentsECL-2.gif">
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void control() {
		
		kdb.updatePlan();

		// produce action_list for new differences and add to the current reconfiguration action
		for (Iterator<CompGoalAtomTracker> iter = kdb.get2address()
				.iterator(); iter.hasNext();) {
			CompGoalAtomTracker atom = iter.next();
			
			ComponentAction action = computeAction(atom);
			if( action!=null ){
				kdb.addAction(action);	// the action is added
				kdb.addressed(atom);	// the atom is set as addressed, since there is an action for it
			}
		}
		
		// for debugging each cycle the current plan of actions is printed
		if( kdb.actions() ){
			kdb.printActions();
		}	

		// execute new action_list		
		actuator.executeAction( kdb.nextCommands() );

	}
	

	/**
	 * calculates the action required to address a goal atom by invoking the inverse model
	 * encoded in the domain action constructor
	 * @param goalAtom the atom of goal for which an action is to be computed
	 * @return
	 */
	private ComponentAction computeAction(CompGoalAtomTracker goalAtom){

		ComponentAction action = new ComponentAction(goalAtom, goalAtom.difference);

		return action;
	}
	

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	protected void resetInternalState() {
		// begin-user-code
		goal = null;
		// TODO complete

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void clearBuffer() {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param o
	 * @param i
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void configureFilter(Set<String> o, Set<String> i) {
		// begin-user-code
		// TODO Auto-generated method stub

		// end-user-code
	}

}