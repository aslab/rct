/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ComponentClass;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ParameterProfile;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class OMParameterProfile extends NamedElement implements
		ParameterProfile {
	public OMParameterProfile(String name2) {
		super(name2);
		// TODO Auto-generated constructor stub
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String type;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentClass owner;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentClass getOwner() {
		// begin-user-code
		return owner;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public String getName() {
		// begin-user-code
		return name;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Object getQuantityType() {
		// begin-user-code
		return type;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!--&nbsp;begin-UML-doc&nbsp;--><br><!--&nbsp;end-UML-doc&nbsp;--><br>@param&nbsp;value2&nbsp;<br>@param&nbsp;value&nbsp;<br>@!generated&nbsp;"UML&nbsp;to&nbsp;Java&nbsp;(com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 * <!-- end-UML-doc -->
	 * @param origin
	 * @param point
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Parameter origin, Parameter point) {
		// begin-user-code
		// this is actually a general method for every profile for evaluable objects
		if (origin == null)
			return null;
		else if (point == null) {
			DifferenceImpl v = new DifferenceImpl();
			v.computedDiff = 1;
			v.dueValue = origin.getValue();
			v.reference = point;
			return v;
		} else
			return new DifferenceImpl(); // empty difference
		// end-user-code
	}
}