/**
 * Provides the classes necessary to create an OM org.aslab.om.metacontrol
 */
package org.aslab.om.metacontrol;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.ecl.ECL;
import org.aslab.om.ecl.Goal;
import org.aslab.om.metacontrol.action.FunctionalAction;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;
import org.aslab.om.metacontrol.knowledge.functions.Binding;
import org.aslab.om.metacontrol.knowledge.functions.FDesignStatus;
import org.aslab.om.metacontrol.knowledge.functions.OMFDesign;
import org.aslab.om.metacontrol.knowledge.functions.OMFGrounding;
import org.aslab.om.metacontrol.knowledge.functions.OMObjective;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;
import org.aslab.om.metacontrol.value.FunctionalGoalTracker;


/** 
 * <!-- begin-UML-doc -->
 * <p>Implementation of a control loop for functions</p>
 * <p>The activity diagram for this class looks as follows</p>
 * <img src ="doc-files/FunctionalECL-1.gif">
 * <!-- end-UML-doc -->
 * @author chcorbato
 */
public class FunctionalECL extends ECL {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private FunctionalGoalTracker goalState;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMFGrounding> fgroundings = new HashSet<OMFGrounding>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMFGrounding> faults = new HashSet<OMFGrounding>(); // is this actually the state?

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param k
	 * @param lowerLoop
	 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	//by default the loop of the  functional org.aslab.om.ecl has a period of 5 secs
	public FunctionalECL(ComponentsECL lowerLoop) {
		// begin-user-code
		super("Functional ECL", lowerLoop, lowerLoop);
		tstep = 5000; // loop period 5 secs

		// for debugging
		System.out.println("=== Functional loop starts =====================");

		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param g
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void setGoal(Goal g) {
		// begin-user-code
		goalState = new FunctionalGoalTracker(
				((FunctionalGoal) g).controlled_objectives);
		goal = g;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void control() {

		if ( goalState.errorSignal.isEmpty() )  // if no error do nothing
			return;
		
		// generate a design solution for them
		Set<OMFGrounding> new_groundings = generateReqDesign(goalState.errorSignal);

		//add the groundings to those extant (update structure to perceive the state)
		fgroundings.addAll(new_groundings);
		
		// produce the action necessary to ground the new complete design solution
		FunctionalAction action = generateComponentsSpec(fgroundings);

		// execute action by sending to components org.aslab.om.ecl
		{
		if (action.atoms.isEmpty()) // if no content for the action, do not execute it
			return;
		// for debugging
		printAction(action);

		actuator.executeAction(action);
		}
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * The perception process takes as sensory input the feedback of the Components Goal from the ComponentsECL, and updates from it the functional state of the domain control system, eventually the state of achievement of the objectives.
The Components Goal feedback is the updated state of the Components Specifications in the Component Goal, which is produced by the evaluation at the Components ECL.
	 * <p><a href="doc-files/OMFunctionsMetamodel-Perception.html"> Perception model at the function level</a> -- here is a schematic account of the rules that form the perception model for functions (objectives, functions, function grounding and function specifications)</p>
	 * <p>The following image shows an example of the upstream propagation of errors</p>
	 * <img src="doc-files/FunctionalECL-2.gif">
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void perceive() {
		// begin-user-code	
		if (sensor == null)
			return;
		// update internal status of groundings
		// the lower components loop updates the status of the atoms that are the performers in the bindings

		faults = updateFGInternalStatus();

		// propagate faults in the tree of fg and objectives
		updateHierarchyStatus(faults);

		// end-user-code
	}

	// returns the set of fgroundings that are in internal error (faulty)
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMFGrounding> updateFGInternalStatus() {
		// begin-user-code		

		Set<OMFGrounding> faults = new HashSet<OMFGrounding>();
		// the performers in the bindings have been updated in the ECL
		for (Iterator<OMFGrounding> ifg = fgroundings.iterator(); ifg.hasNext();) {
			OMFGrounding fg = ifg.next();
			if (fg.internalError())
				faults.add(fg);
		}
		return faults;
		// end-user-code
	}

	// updates status by propagating faults so as to have all failures
	// this can be improved / simplified / optimized
	/** 
	 * <!-- begin-UML-doc -->
	 * updates status by propagating faults so as to have all failures
	 * <!-- end-UML-doc -->
	 * @param faults
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private void updateHierarchyStatus(Set<OMFGrounding> faults) {
		// begin-user-code
		for (Iterator<OMFGrounding> ifg = faults.iterator(); ifg.hasNext();) {
			for (Iterator<OMObjective> iob = ifg.next().realizes.iterator(); iob
					.hasNext();) {
				iob.next().propagateStatus();
			}
		}
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>The Evaluation process in the Function Loop does not follow the ECl Explicit Evaluation pattern, since no metrics for the domain of functions have been developed.
The ECL evaluation process in the Functions Loop consists of the downstream propagation of the relevance of objectives, from the topmost root objectives (i.e. systems requirements) downwards to the bottom functions in the hierarchy tree of functions and objectives.</p>
	 * <p><a href="doc-files/OMFunctionsMetamodel-Evaluation.html"> Evaluation model at the function level</a> -- here is a schematic account of the rules that form the evaluation model for functions (objectives, functions, function grounding and function specifications)</p>
	 * <p>The following image shows an example of this downstream propagation of relevances</p>
	 * <img src="doc-files/FunctionalECL-3.gif">
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void evaluate() {
		goalState.updateEval();
	}

	// method that provides the best set of function specifications that solve a certain set of objectives
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param objectives
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@SuppressWarnings("unused")
	@Deprecated
	private Set<OMFDesign> functions2ground(Set<OMObjective> objectives) {
		// begin-user-code
		Set<OMFDesign> design = new HashSet<OMFDesign>();

		for (Iterator<OMObjective> iob = objectives.iterator(); iob.hasNext();) {
			OMFDesign faux = null;
			double aux = 0;
			for (Iterator<OMFDesign> ifs = iob.next().objectiveType.realisations
					.iterator(); ifs.hasNext();) {
				OMFDesign fs = ifs.next();
				if (fs.errorModel() == FDesignStatus.REALISABLE && fs.confidence > aux) {
					faux = fs;
					aux = fs.confidence;
				}//if
			}//for
			design.add(faux);
		}//for

		return design;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * grounds the appropriate function for this objective
	 * <!-- end-UML-doc -->
	 * @param objective
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private OMFGrounding obtainBestSolution(OMObjective objective) {
		// begin-user-code		
		OMFDesign faux = null;
		double aux = 0;
		for (Iterator<OMFDesign> ifs = objective.objectiveType.realisations
				.iterator(); ifs.hasNext();) {
			OMFDesign fs = ifs.next();
			if (fs.errorModel() == FDesignStatus.REALISABLE && fs.confidence > aux) {
				faux = fs;
				aux = fs.confidence;
			}//if
		}//for

		OMFGrounding solution = new OMFGrounding(objective, faux);

		return solution;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * instantiate all the fgroundings requires to address an objective
	 * <!-- end-UML-doc -->
	 * @param objective
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMFGrounding> generateCompleteSolution(OMObjective objective) {
		// begin-user-code
		Set<OMFGrounding> design = new HashSet<OMFGrounding>();

		OMFGrounding faux = obtainBestSolution(objective);
		design.add(faux);

		// continue to design solutions for the sub-objectives
		if (!faux.requires.isEmpty()) {
			for (Iterator<OMObjective> io = faux.requires.iterator(); io
					.hasNext();) {
				design.addAll(generateCompleteSolution(io.next()));
			}
		}
		return design;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * obtain the fgroundings required
	 * <!-- end-UML-doc -->
	 * @param objectives
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<OMFGrounding> generateReqDesign(Set<OMObjective> objectives) {
		// begin-user-code
		Set<OMFGrounding> design = new HashSet<OMFGrounding>();

		for (Iterator<OMObjective> iob = objectives.iterator(); iob.hasNext();) {
			OMObjective ob = iob.next();
			fgroundings.remove( ob.realizer ); // remove previous realizer of the objective, which was in error
			design.addAll( generateCompleteSolution(ob) );
		}

		return design;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * method pertaining to the control of functions
	 * <!-- end-UML-doc -->
	 * @param design
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private FunctionalAction generateComponentsSpec(Set<OMFGrounding> design) {
		// begin-user-code

		// put all the needed bindings coming from the different fgroundings
		Set<Binding> bindings = new HashSet<Binding>();
		for (Iterator<OMFGrounding> ifg = design.iterator(); ifg.hasNext();) {
			bindings.addAll(ifg.next().bindings);
		}

		// algorithm that reduces the component specs by merging the required roles
		for (Iterator<Binding> ib = bindings.iterator(); ib.hasNext();) {
			Binding b = ib.next();

			for (Iterator<Binding> jb = bindings.iterator(); jb.hasNext();) {
				Binding c = jb.next();
				if (c != b) {
					if (c.performer.componentSpec.getComponentSpec()
							.complies(b.performer.componentSpec.getComponentSpec())) { // if b.performer can perform c.performer, replace
						c.performer = b.performer;
					}
				}
			}
		}

		// now retrieve the Component specs that remain in the bindings
		Set<CompGoalAtomTracker> componentAtoms = new HashSet<CompGoalAtomTracker>();
		for (Iterator<Binding> ib = bindings.iterator(); ib.hasNext();) {
			componentAtoms.add(ib.next().performer);
		}

		// return action with the atoms
		return new FunctionalAction(componentAtoms);
		// end-user-code
	}


	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param action
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private void printAction(FunctionalAction action) {
		// begin-user-code
		System.out.println("--> Functional Action:");
		for (Iterator<CompGoalAtomTracker> ia = action.atoms.iterator(); ia
				.hasNext();) {
			System.out.println("\t"
					+ ((ComponentState) ia.next().componentSpec.getSpec()).getComponentClass()
							.getName());
		}
		System.out.println("    ");
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * the goal is set to null, more should be done
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	protected void resetInternalState() {
		// begin-user-code
		// TODO complete
		goal = null;

		// end-user-code
	}
}