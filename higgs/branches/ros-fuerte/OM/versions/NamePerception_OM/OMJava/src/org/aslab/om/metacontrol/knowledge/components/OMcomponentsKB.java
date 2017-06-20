/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;


import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Connector;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.knowledge.KnowledgeBase;
import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.ecl.perception.Percept;
import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.metacontrol.ComponentsGoal;
import org.aslab.om.metacontrol.action.ComponentAction;
import org.aslab.om.metacontrol.action.Reconfiguration;
import org.aslab.om.metacontrol.action.ReconfigurationCommand;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;
import org.aslab.om.metacontrol.perception.components.PortSingularity;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;
import org.aslab.om.metacontrol.value.ComponentsGoalTracker;




/** 
 * <!-- begin-UML-doc -->
 * <p><b>container</b>&nbsp;for&nbsp;the&nbsp;knowledge&nbsp;at&nbsp;the&nbsp;components&nbsp;level:</p><p>it&nbsp;consists&nbsp;of&nbsp;types:</p><ul><li><p>component&nbsp;classes</p></li><li><p>quantity&nbsp;types</p></li></ul><p>parameter&nbsp;and&nbsp;port&nbsp;profiles&nbsp;are&nbsp;part&nbsp;of&nbsp;the&nbsp;definition&nbsp;of&nbsp;each&nbsp;component&nbsp;class</p><p></p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMcomponentsKB extends KnowledgeBase {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMParameterProfile> paramProfiles = new HashSet<OMParameterProfile>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	//public QuantityProfile quantities;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Map<String, OMComponent> estimatedState = new HashMap<String, OMComponent>();
	
	/**
	 * contains the known classes of components
	 */
	private Set<OMComponentClass> knowledge =  new HashSet<OMComponentClass>();

	public Set<OMComponentClass> getComponentClasses() {
		return knowledge;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Map<String, OMConnector> connectors = new HashMap<String, OMConnector>();

	/**
	 * encapsulates the knowledge about actions of this loop and their state
	 * TODO maybe move to the kdb
	 */
	private Reconfiguration action_plan;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ComponentsGoalTracker goalState;

	public Set<Connector> getConnectors() {
		Set<Connector> s = new HashSet<Connector>();
		s.addAll(connectors.values());
		return s;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMcomponentsKB() {
		// begin-user-code
		super();
		// TODO Auto-generated method stub

		// end-user-code
	}

	// Factory methods ==========================================

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMComponentClass newComponentClass(String name) {
		// begin-user-code
		OMComponentClass c = new OMComponentClass(name);
		elements.add(c);
		//componentClasses.add(c);
		return c;
		// end-user-code
	}

	// "Inverse" Factory methods =================================
	// these are to be called with any element created with a constructor

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void addParameterProfile(OMParameterProfile p) {
		// begin-user-code
		elements.add(p);
		paramProfiles.add(p);
		// end-user-code
	}

	// ============================================================

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param name
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMParameterProfile getParamProfile(String name) {
		// begin-user-code

		for (Iterator<OMParameterProfile> i = paramProfiles.iterator(); i
				.hasNext();) {
			OMParameterProfile prof = i.next();
			if (prof.name.equals(name))
				return prof;
		}

		return null;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param c
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void addComponentClass(OMComponentClass c) {
		// begin-user-code
		elements.add(c);
		knowledge.add(c);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param c
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void addEstimatedComponent(OMComponent c) {
		// begin-user-code
		estimatedState.put(c.getName(), c);
		// end-user-code
	}


	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private void addPortConnector(OMPort p) {
		// begin-user-code
		OMConnector c = connectors.get(p.getProfile().getName());
		if (c == null) {
			OMConnector c1 = addConnector(p.getProfile().getName(), p.getProfile().getQuantityType(), p);
			p.connector = c1;
		} else if (p.connector == null) {
			p.connector = c;
			c.ports.add(p);
		}
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<StateAtom> getEstimatedState() {
		// begin-user-code
		Set<StateAtom> s = new HashSet<StateAtom>();
		s.addAll( estimatedState.values() );
		return s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param portp
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void addPortProfile(OMPortProfile portp) {
		// begin-user-code
		elements.add(portp);
		// TODO add to profiles??
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param set
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMComponent> getSourceComponents(Set<OMComponent> set) {
		// begin-user-code
		Set<OMComponent> s = new HashSet<OMComponent>();
		for (Iterator<OMComponent> i = set.iterator(); i.hasNext();) {
			OMComponent c = i.next();
			if (c.getInputPorts().isEmpty() && !c.getOutputPorts().isEmpty())
				s.add(c);
		}
		return s;
		// end-user-code
	}


	public OMConnector addConnector(String name, String type, Port provider) {
		OMConnector c;
		if ( connectors.containsKey(name) )
			c = connectors.get(name);
		else{
			c = new OMConnector(name, type);
			connectors.put(name, c);
		}
		c.addPort(provider);
		return c;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param con
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void deleteConnector(String cname) {
		// begin-user-code
		OMConnector c = connectors.remove(cname);
		c.deleteConnector(); // remove all references
		// end-user-code
	}

	public OMConnector getConnector(String name) {
		return connectors.get(name);
	}
	
	/**
	 * @param goalState the goalState to set
	 */
	public void setGoal(ComponentsGoal g) {
		this.goalState = new ComponentsGoalTracker(g);  // TODO inform the evaluation?
		action_plan = new Reconfiguration();	// TODO inform the control about this
		matchGoal2Estimation();
	}


	/**
	 * @return the goalState
	 */
	public ComponentsGoalTracker getGoalState() {
		return goalState;
	}
	
	
	/**
	 * for debugging
	 */
	public void printEstimatedState(){
		System.out.println(estimatedState);
	}
	
	/**
	 * for debugging
	 */
	public void printGoal(){
		for (Iterator<CompGoalAtomTracker> ia = goalState.goalAtoms.iterator(); ia.hasNext();) {
			System.out.println("\t"
			+ ((ComponentState) ia.next().componentSpec.getSpec()).getComponentClass()
					.getName());
		}
		System.out.println("    ");
	}
	
	
	/**
	 * @return true if there is an action_plan, false otherwise
	 */
	public boolean actions(){
		if( action_plan == null)
			return false;
		else if( action_plan.action_list.isEmpty() )
			return false;
		else
			return true;
		
	}
	
	public Collection<ComponentAction> getActions(){
		return action_plan.action_list.values();
	}
	
	public void updatePlan(){
		action_plan.updatePlan();
	}
	
	public Set<CompGoalAtomTracker> get2address(){
		return goalState.get2address();
	}
	
	public void addAction(ComponentAction action){
		action_plan.addAction(action);
	}
	
	public Set<ReconfigurationCommand> nextCommands(){
		return action_plan.process();
	}
	
	private void matchGoal2Estimation() {
		for( Iterator<String> iter = estimatedState.keySet().iterator(); iter.hasNext(); ){
			String name = iter.next();
			ComponentState matchSpec = goalState.getMissingSpec( name );
			
			if( matchSpec != null )
				goalState.componentMatched( estimatedState.get(name), matchSpec );
		}
		
	}
	
	
	// this method fills in the data structure to maintain the evaluation of the goal against the incoming estimated states
	// is to be invoked again when a new goal is injected or there is a major perceptive change
	// STATUS: done 2nd version
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Deprecated
	public void matchSpecs2State() {
		// begin-user-code

		// if no missing specs to match, do nothing
		if (goalState.getMissingSpecs().size() == 0)
			return;

		// this is the state of components as perceived, and we want to pair each component with each one of the
		// goal atoms if possible

		for (Iterator<StateAtom> comp = getEstimatedState().iterator(); comp
				.hasNext();) {
			ComponentState state = (ComponentState) comp.next();
			ComponentState candidate = null;
			int score = 0;

			for (Iterator<ComponentState> iter = goalState.getMissingSpecs()
					.iterator(); iter.hasNext();) {
				ComponentState atom = iter.next();

				// we use the domain metric difference to obtain the matching level
				if (state.calculateMatching2Spec(atom) > score) {
					candidate = atom;
					score = state
							.calculateMatching2Spec(atom);
				}

			}

			// now see if the best match is acceptable
			if (score > 1) {
				goalState.componentMatched(state, candidate);
			}

		}

		// end-user-code
	}

	public void updateEval(){
		goalState.updateEval();
	}
	
	
	/**
	 * @see ComponentsGoalTracker.addressed()
	 * @param atom
	 * @return
	 */
	public boolean addressed(CompGoalAtomTracker atom){
		return goalState.addressed(atom);
	}

	public void printActions() {
		action_plan.print();
		
	}

	public ComponentState getMissingSpec(String name) {
		if( goalState==null )
			return null;
		
		return goalState.getMissingSpec(name);
	}

	public Percept getEstimatedComponent(String name) {
		if( estimatedState==null )
			return null;
		
		return estimatedState.get(name);
	}

	public Set<ComponentState> getGoalStates() {
		if( goalState==null )
			return new HashSet<ComponentState>();
		return goalState.getStateSpecs();
	}
}