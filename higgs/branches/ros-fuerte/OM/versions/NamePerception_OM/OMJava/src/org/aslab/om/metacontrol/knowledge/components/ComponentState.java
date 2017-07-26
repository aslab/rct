package org.aslab.om.metacontrol.knowledge.components;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;
import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.metacontrol.value.ComponentDifference;



/** 
 * <!-- begin-UML-doc -->
 * TODO with no attributes and only abstract method this should be an interface and not a class should be refactored
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class ComponentState extends StateAtom implements Component {

	// method containing the metamodel metrics for a component
	// it supposed that the object whose method is invoked is a component specification, and the argument is an actual component
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param comp
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract ComponentDifference measure(ComponentState comp);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param spec
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract int calculateMatching2Spec(ComponentState spec);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param spec
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract boolean complies(ComponentState spec);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param spec
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract double complianceLevel(ComponentState spec);

}