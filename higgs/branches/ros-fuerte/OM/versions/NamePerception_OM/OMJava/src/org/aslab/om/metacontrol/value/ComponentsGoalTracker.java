/**
 * 
 */
package org.aslab.om.metacontrol.value;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.metacontrol.ComponentsGoal;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentsGoalTracker {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<CompGoalAtomTracker> goalAtoms = new HashSet<CompGoalAtomTracker>(); // set of all the goal atoms in the current Goal

	private Map<String, ComponentState> missingSpecs = new HashMap<String, ComponentState>();
	
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<CompGoalAtomTracker> errorSignal = new HashSet<CompGoalAtomTracker>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<CompGoalAtomTracker> still2address = new HashSet<CompGoalAtomTracker>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double achievementLevel = new Integer(0); // to have an overall data about progress towards the goal

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<ComponentState> missingAtoms = new HashSet<ComponentState>(); // goal atoms for which there is no component in the spec

	public Set<ComponentState> getMissingSpecs() {
		return missingAtoms;
	}


	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<ComponentState> matchedComponents = new HashSet<ComponentState>(); // for perceptual filtering purposes, so as not to try to match them again

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	// public Set<OMComponentClass> componentClasses = new HashSet<OMComponentClass>();
	
	private Set<ComponentState> specs = new HashSet<ComponentState>();

	public Set<ComponentState> getMatchedComponents() {
		return matchedComponents;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param g
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentsGoalTracker(ComponentsGoal g) {
		goalAtoms = g.atoms;

		// the atoms are a goal since now
		for (Iterator<CompGoalAtomTracker> ic = goalAtoms.iterator(); ic.hasNext();){
			CompGoalAtomTracker comp = ic.next();
			comp.setCreationTime(System.currentTimeMillis());
			ComponentState state = comp.componentSpec.getComponentSpec();
			specs.add(state);
			missingAtoms.add(state);
			missingSpecs.put( state.getName(), state );
		}

	}

	// this method encodes the evaluation of the ECL
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void updateEval() {
		// begin-user-code
		double result = 0;

		// erase the deltas from previous update

		for (Iterator<CompGoalAtomTracker> iter = goalAtoms.iterator(); iter
				.hasNext();) {
			CompGoalAtomTracker atom = iter.next();

			atom.updateEval(); // implicitly compute the domain metric differences and then evaluate them

			if (!atom.achieved) {
				if (errorSignal.add(atom))
					still2address.add(atom);
			} else {
				errorSignal.remove(atom);
				still2address.remove(atom);
			}

			result = result + atom.achievementLevel;
		}

		// TODO for the moment we return an average
		achievementLevel = result / goalAtoms.size();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<CompGoalAtomTracker> get2address() {
		// begin-user-code
		Set<CompGoalAtomTracker> s = new HashSet<CompGoalAtomTracker>();
		s.addAll(still2address);
		still2address.clear();
		return s;
		// end-user-code
	}

	/**
	 * for debugging, prints the Difference entries that require an action (still2address)
	 */
	public void print() {
		System.out.println("-- Differences ------------------------");
		for (Iterator<CompGoalAtomTracker> iter = still2address.iterator(); iter.hasNext();) {
			iter.next().print();
		}
		System.out.println("---------------------------------------");
		System.out.println();
		
	}
	
	/**
	 * Removes the atom from the list of those for which an action has not been produced (still2address)
	 * @param atom the goal atom that is addressed
	 * @return true if the atom was not addressed, false it it was previously
	 */
	public boolean addressed( CompGoalAtomTracker atom ){
		return still2address.remove(atom);
	}
	
	
	/** Associates a spec with a component. As a result the spec is also removed from the missingSpecs map
	 * @param comp
	 * @param spec
	 * @return
	 */
	public boolean componentMatched( ComponentState comp, ComponentState spec ){
		for( Iterator<CompGoalAtomTracker> iter = goalAtoms.iterator(); iter.hasNext(); ){
			CompGoalAtomTracker atom = iter.next();
			if( atom.componentSpec.getSpec() == spec ){
				atom.componentValue = comp;
				break;
			}
		}
		
		return missingSpecs.remove(spec.getName())!=null ||	matchedComponents.add(spec);
	}
	
	public ComponentState getMissingSpec(String name){
		return missingSpecs.get(name);
	}

	public Set<ComponentState> getStateSpecs() {
		Set<ComponentState> states = new HashSet<ComponentState>(specs);
		return states;
	}


}