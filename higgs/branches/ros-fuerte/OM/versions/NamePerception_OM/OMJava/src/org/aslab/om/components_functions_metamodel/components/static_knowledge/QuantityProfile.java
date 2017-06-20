/**
 * 
 */
package org.aslab.om.components_functions_metamodel.components.static_knowledge;

/** 
 * <!-- begin-UML-doc -->
 * <p>generalizes&nbsp;the&nbsp;concepts&nbsp;of&nbsp;ParameterProfile&nbsp;and&nbsp;InternalStateProfileAtom,&nbsp;which&nbsp;are&nbsp;by&nbsp;a&nbsp;profile&nbsp;for&nbsp;a&nbsp;quantity</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public interface QuantityProfile {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>semantically&nbsp;relevant</p><p>not&nbsp;just&nbsp;for&nbsp;element&nbsp;identification&nbsp;in&nbsp;the&nbsp;model,&nbsp;but&nbsp;domain&nbsp;name</p>
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getName();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void getQuantityType();
}