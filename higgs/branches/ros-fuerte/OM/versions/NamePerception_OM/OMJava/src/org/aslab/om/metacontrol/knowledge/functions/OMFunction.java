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
public class OMFunction {

	/** 
	 * <!-- begin-UML-doc -->
	 * description of the function: i.e. "self localise"
	 * for the moment it is in natural language with the sole purpose of identifying functions
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String description;
	/** 
	 * <!-- begin-UML-doc -->
	 * set of FunctionSpecifications that can perform this function
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFDesign> realisations = new HashSet<OMFDesign>();

	/** 
	 * <!-- begin-UML-doc -->
	 * perception model of functions: it is a model of availability (equivalent to the error model for instances)
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FunctionStatus perceptionModel() {//TODO: rename to Availability() ?
		// begin-user-code
		int num_realisations = 0;

		for (Iterator<OMFDesign> ifspec = realisations.iterator(); ifspec
				.hasNext();) {
			OMFDesign spec = ifspec.next();
			if (spec.errorModel() != FDesignStatus.UNREALISABLE) {
				num_realisations++;
			}
		}

		if (num_realisations == 0) {
			return FunctionStatus.UNAVAILABLE;
		} else {
			return FunctionStatus.AVAILABLE;
		}
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * returns the conditioned probability of not achieving a function when the given fspec is not available
	 * <!-- end-UML-doc -->
	 * @param spec
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double failureProb(OMFDesign spec) {
		// begin-user-code

		if (!realisations.contains(spec))
			return 0;

		else
			return failureProb() / (1 - spec.confidence);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * returns the probability of not achieving the function (for internal use to calculate the conditioned
	 * failure prob when a certain FSpec is not realisable)
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private double failureProb() {
		// begin-user-code
		double n = 1;
		for (Iterator<OMFDesign> ifspec = realisations.iterator(); ifspec
				.hasNext();) {
			OMFDesign spec = ifspec.next();
			if (spec.errorModel() == FDesignStatus.REALISABLE)
				n = n * (1 - spec.confidence);
		}
		return n;
		// end-user-code
	}

}