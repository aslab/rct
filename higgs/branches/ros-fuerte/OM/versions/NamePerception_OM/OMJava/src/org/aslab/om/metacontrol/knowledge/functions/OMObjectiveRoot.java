package org.aslab.om.metacontrol.knowledge.functions;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMObjectiveRoot extends OMObjective {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private double relevance; // 0-1 relative importance of this objective for the system to achieve its whole mission
								// the sum of the relevances of all the root objectives must be 1
								// this attribute is of an hypothetical evaluation interface
								// TODO: move to FunGoalAtomTracker

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param r
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMObjectiveRoot(double r) {
		// begin-user-code
		super();
		relevance = r;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public double relevance() {
		// begin-user-code
		return relevance;
		// end-user-code
	}

}
