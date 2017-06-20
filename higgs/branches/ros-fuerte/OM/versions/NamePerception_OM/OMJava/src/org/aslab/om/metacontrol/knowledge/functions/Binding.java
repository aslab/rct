/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.functions;

import org.aslab.om.metacontrol.knowledge.components.ComponentState;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;
import org.aslab.om.metacontrol.value.ComponentSpecificationAtom;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Binding {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMRole role;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public CompGoalAtomTracker performer;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMFGrounding owner; // the FunctionGrounding the binding pertains to

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param fg
	 * @param r
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Binding(OMFGrounding fg, OMRole r) {
		// begin-user-code
		owner = fg;
		role = r;
		ComponentSpecificationAtom spec = new ComponentSpecificationAtom(
				role.definition);
		performer = new CompGoalAtomTracker(spec);
		// end-user-code
	}

	// the higher the eval, the better the binding
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double eval() {
		// begin-user-code
		return role.definition.complianceLevel((ComponentState) performer.componentSpec.getSpec());
		// end-user-code
	}
}