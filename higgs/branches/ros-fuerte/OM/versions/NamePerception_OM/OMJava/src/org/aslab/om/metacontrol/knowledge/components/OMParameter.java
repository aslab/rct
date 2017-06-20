/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;


import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ParameterProfile;
import org.aslab.om.ecl.knowledge.KnowledgeAtom;
import org.aslab.om.metacontrol.value.Difference;



/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMParameter extends KnowledgeAtom implements Parameter {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Object value;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMParameterProfile profile;

	public OMParameter(OMParameterProfile pprofile, OMComponent component) {
		super();
		profile = pprofile;
		owner = component;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * @param value the value to set
	 * <!-- end-UML-doc -->
	 * @param value
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setValue(Object value) {
		// begin-user-code
		this.value = value;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Component owner;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param param
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Parameter param) {
		// begin-user-code
		return this.profile.measure(this, param);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Object getValue() {
		// begin-user-code
		return value;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ParameterProfile getProfile() {
		// begin-user-code
		return profile;
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
		return profile.getName();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Component getOwner() {
		// begin-user-code
		return owner;
		// end-user-code
	}
	
	@Override
	public String toString(){
		if (value != null)
			return profile.getName() + ":\t" + value.toString();		
		else
			return profile.getName();
	}
}