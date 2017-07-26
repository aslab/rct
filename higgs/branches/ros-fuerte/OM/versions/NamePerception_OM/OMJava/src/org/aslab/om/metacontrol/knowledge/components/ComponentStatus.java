/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public enum ComponentStatus {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>component&nbsp;alive&nbsp;but&nbsp;not&nbsp;participating&nbsp;in&nbsp;any&nbsp;function</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	INACTIVE,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>component&nbsp;alive&nbsp;and&nbsp;participating&nbsp;in&nbsp;some&nbsp;functions</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	ACTIVE,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>component&nbsp;doesn't&nbsp;work&nbsp;as&nbsp;expected,&nbsp;reason&nbsp;unknown&nbsp;(internal&nbsp;error&nbsp;o&nbsp;input&nbsp;failure)</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	FAULT,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>component&nbsp;doesn't&nbsp;working&nbsp;because&nbsp;of&nbsp;internal&nbsp;error</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	ERROR,

	/** 
	 * <!-- begin-UML-doc -->
	 * the component is not perceived as existing
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	MISSING,

}