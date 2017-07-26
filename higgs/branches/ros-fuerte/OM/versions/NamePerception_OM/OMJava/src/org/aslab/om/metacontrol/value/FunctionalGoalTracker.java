package org.aslab.om.metacontrol.value;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.metacontrol.knowledge.functions.OMObjective;
import org.aslab.om.metacontrol.knowledge.functions.OMObjectiveRoot;
import org.aslab.om.metacontrol.knowledge.functions.ObjectiveStatus;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class FunctionalGoalTracker {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<FunGoalAtomTracker> goalAtoms = new HashSet<FunGoalAtomTracker>(); // set of all the goal atoms in the current Goal

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMObjective> errorSignal = new HashSet<OMObjective>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param objectives
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FunctionalGoalTracker(Set<OMObjectiveRoot> objectives) {
		// begin-user-code
		for (Iterator<OMObjectiveRoot> i = objectives.iterator(); i.hasNext();) {
			goalAtoms.add(new FunGoalAtomTracker(i.next()));
		}
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * assign value to objectives by propagating relevance downstream from the roots
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void updateEval() {
		// assign value to objectives by propagating downstream from the roots
		for (Iterator<FunGoalAtomTracker> i = goalAtoms.iterator(); i.hasNext();) {
			i.next().functionalSpec.propagateRelevance();
		}
		// obtain the objectives to fix
		errorSignal = objectives2fix();
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * objectives to fix are those that are in error and that have relevance not zero
	 * comment: I'm not sure the rule for adding an objective to the fix list is correct,
	 * only terminal objectives should be added right?
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMObjective> objectives2fix() {
		// begin-user-code		
		Set<OMObjective> objectives = OMObjective.getObjectives(); // TODO: obtain objectives from the kb
		Set<OMObjective> ob2fix = new HashSet<OMObjective>();

		for (Iterator<OMObjective> iob = objectives.iterator(); iob.hasNext();) {
			OMObjective ob = iob.next();
			if( (ob.relevance() > 0) && (ob.status()==ObjectiveStatus.UNACHIEVABLE) ){
				System.out.printf("--- There is no way to realize:\n \t -instance of obj: %s \n", ob.objectiveType.description);
			}
			if ((ob.relevance() > 0) && (ob.status() == ObjectiveStatus.ERROR)) {
				ob2fix.add(ob);
			}
		}
		return ob2fix;
		// end-user-code
	}

}
