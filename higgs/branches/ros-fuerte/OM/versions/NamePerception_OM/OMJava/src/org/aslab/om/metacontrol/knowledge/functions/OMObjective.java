/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.functions;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMObjective {

	/** 
	 * <!-- begin-UML-doc -->
	 * to maintain a static list of all the objectives in the system
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	static protected Set<OMObjective> references = new HashSet<OMObjective>();

	/** 
	 * <!-- begin-UML-doc -->
	 * to identify the objective
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String description;

	/** 
	 * <!-- begin-UML-doc -->
	 * function groundings that depend on the achievement of this objective
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFGrounding> owners = new HashSet<OMFGrounding>();

	/** 
	 * <!-- begin-UML-doc -->
	 * function grounding that addresses this objective: for economy purposes only one is
	 * addressing each objective
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMFGrounding realizer;
	/** 
	 * <!-- begin-UML-doc -->
	 * the function this concreteobjective is an instance of
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMFunction objectiveType;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMObjective() {
		references.add(this);
	}

	public OMObjective(OMFunction function, OMFGrounding requiring) {
		references.add(this);
		objectiveType = function;
		owners.add(requiring);
		description = new String(function.description + " instance");
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * to retrieve all the objectives in the system
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	static public Set<OMObjective> getObjectives() {
		// begin-user-code
		return references;
		// end-user-code
	}

	// encodes the metamodel for evaluation of an objective
	/** 
	 * <!-- begin-UML-doc -->
	 * perception model for objectives, complemented with the propagation...
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ObjectiveStatus status() {
		// begin-user-code
		if (realizer == null)
			return ObjectiveStatus.ERROR;

		// status acording to realisation of the objective
		if (realizer.perceptionModel() == FGroundingStatus.ERROR) {

			// check if there are alternatives
			if (objectiveType.perceptionModel() == FunctionStatus.UNAVAILABLE) {
				return ObjectiveStatus.UNACHIEVABLE;
			} else
				return ObjectiveStatus.ERROR;
		}

		else
			return ObjectiveStatus.ADDRESSED;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * method to propagate the status of objectives (and fgs) in the whole hierarchy
	 * TODO: move responsibilities to decouple propagation in fgs and objs
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void propagateStatus() {
		// begin-user-code
		if (status() == ObjectiveStatus.ADDRESSED) // only go upwards if not ok
			return;

		for (Iterator<OMFGrounding> ifg = owners.iterator(); ifg.hasNext();) {
			OMFGrounding fg = ifg.next();
			if (fg.perceptionModel() != FGroundingStatus.OK)
				for (Iterator<OMObjective> iob = fg.realizes.iterator(); iob
						.hasNext();)
					iob.next().propagateStatus();
		}
		// end-user-code
	}


	/** 
	 * <!-- begin-UML-doc -->
	 * the relevance of an objective only depends upstream (towards root objectives)
	 * the relevance is the same for all the fgs owning it, they critically depend on it
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double relevance() {
		// begin-user-code		
		double aux = 0;
		// TODO think of how to compute: for the moment it is the highest relevance of the FGs that require it
		for (Iterator<OMFGrounding> ifg = owners.iterator(); ifg.hasNext();) {
			OMFGrounding fg = ifg.next();

			if (fg.relevance() > aux)
				aux = fg.relevance();
		}

		return aux;
		// end-user-code
	}

	
	/** 
	 * <!-- begin-UML-doc -->
	 * propagate relevance downstream from root objectives
	 * TODO: move out of this class
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void propagateRelevance() {
		// begin-user-code	
		if (realizer == null)
			return;
		realizer.relevance();
		for (Iterator<OMObjective> iob = realizer.realizes.iterator(); iob
				.hasNext();) {
			OMObjective ob = iob.next();
			if (ob == this) {
				continue;
			}
			ob.relevance();
			ob.propagateRelevance(); //
		}

		// end-user-code
	}

}