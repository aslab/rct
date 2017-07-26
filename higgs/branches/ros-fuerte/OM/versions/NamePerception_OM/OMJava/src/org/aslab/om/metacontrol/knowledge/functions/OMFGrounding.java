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
public class OMFGrounding {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FGroundingStatus status = FGroundingStatus.OK;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMObjective> realizes = new HashSet<OMObjective>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMObjective> requires = new HashSet<OMObjective>();
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMFDesign realizationType;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Binding> bindings = new HashSet<Binding>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param objective
	 * @param type
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMFGrounding(OMObjective objective, OMFDesign type) {
		// begin-user-code
		realizes.add(objective);
		objective.realizer = this;
		realizationType = type;

		// instantiate here the required objectives (TODO parse parameters)
		for( Iterator<OMFunction> ifun = type.requires.iterator(); ifun.hasNext(); ){
			OMObjective required = new OMObjective(ifun.next(), this);
			this.requires.add(required);
		}

		// produce default component spec from the role and bind them
		for( Iterator<OMRole> irole = realizationType.roles.iterator(); irole
				.hasNext();) {
			Binding b = new Binding(this, irole.next());
			bindings.add(b);
		}
		// end-user-code
	}

	// check internal realisation (roles) (this encodes the internal model for a FGrounding)
	// metamodel, no application-specific model for the moment
	/** 
	 * <!-- begin-UML-doc -->
	 * the propioceptive model for function groundings
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean internalError() {
		// begin-user-code

		for (Iterator<Binding> ibind = bindings.iterator(); ibind.hasNext();) {
			Binding b = ibind.next();
			if (b.performer.isError()) {
				status = FGroundingStatus.ERROR;
				return true;
			}
		}
		return false;
		// end-user-code
	}

	// method that encodes the model for function groundings (it's at the metalevel)
	/** 
	 * <!-- begin-UML-doc -->
	 * perception model for fgs: it integrates info from the external error model (coded here) with 
	 * the already present info from the internalModel
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FGroundingStatus perceptionModel() {
		// begin-user-code
		if (!internalError()) {

			// check external dependencies
			for (Iterator<OMObjective> iter = requires.iterator(); iter
					.hasNext();) {
				OMObjective o = iter.next();

				// as soon as one of the dependencies is unachievable, the fg is in error
				if (o.status() == ObjectiveStatus.UNACHIEVABLE) {
					status = FGroundingStatus.PERMANENT_FAILURE;
					return status;
				} else if (o.status() == ObjectiveStatus.ERROR)
					if (status != FGroundingStatus.ERROR) {
						return status = FGroundingStatus.FAILURE;
					}
				return status;
			}

		}

		return status;
		// end-user-code
	}

	
	/** 
	 * <!-- begin-UML-doc -->
	 * the absolute importance of this fg for the mission
	 * it is weighted sum of the relevances of its realised objectives
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double relevance() {
		// begin-user-code

		// if the fg is not going to work, it is not relevant at all
		if (status == FGroundingStatus.ERROR)
			return 0;

		double aux = 0;
		double obj_relevances = 0;

		for (Iterator<OMObjective> iob = realizes.iterator(); iob.hasNext();) {
			OMObjective ob = iob.next();
			aux = aux + relevance(ob) * ob.relevance();
			obj_relevances = obj_relevances + ob.relevance();
		}
		return aux / obj_relevances;
		// end-user-code
	}

	// importance relative to one of its realized objectives
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param obj
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double relevance(OMObjective obj) {
		// begin-user-code
		if (!realizes.contains(obj))
			return 0;
		else {
			return realizationType.relevance(obj.objectiveType);
		}
		// end-user-code
	}

}