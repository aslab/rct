/**
 * 
 */
package org.aslab.om.components_functions_metamodel.components.instantaneous_state;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.ParameterProfile;
import org.aslab.om.metacontrol.value.Difference;


/** 
 * <!-- begin-UML-doc -->
 * <p>represent&nbsp;a&nbsp;configurable&nbsp;property&nbsp;of&nbsp;a&nbsp;component</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public interface Parameter {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Object getValue();

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>just&nbsp;an&nbsp;ID&nbsp;for&nbsp;identification&nbsp;of&nbsp;the&nbsp;element&nbsp;in&nbsp;the&nbsp;model</p><p>not&nbsp;semantically&nbsp;relevant</p>
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getName();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ParameterProfile getProfile();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Component getOwner();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param point
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Parameter point);
}