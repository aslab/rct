/**
 * 
 */
package org.aslab.om.metacontrol.action;

/** 
 * <!-- begin-UML-doc -->
 * <p>defines&nbsp;the&nbsp;names&nbsp;of&nbsp;the&nbsp;action&nbsp;primitives&nbsp;at&nbsp;the&nbsp;component&nbsp;level</p><p>still&nbsp;to&nbsp;precisely&nbsp;define&nbsp;which&nbsp;ones</p><p>see&nbsp;<a&nbsp;href="http://www.evernote.com/shard/s22/sh/1ca418df-ff49-429d-8a1d-bf3214f3b110/67a24c2ecf2bf4a37b740b96626ec6ac"&nbsp;rel="">evernote</a></p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public enum ComponentActionType {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>deploys,&nbsp;initializes&nbsp;and&nbsp;starts&nbsp;a&nbsp;component</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	LAUNCH,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>stops,&nbsp;deactivates&nbsp;and&nbsp;removes&nbsp;a&nbsp;component</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	KILL,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>change&nbsp;the&nbsp;configuration&nbsp;of&nbsp;a&nbsp;component</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	RECONFIGURE,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>re-launches&nbsp;the&nbsp;component&nbsp;with&nbsp;the&nbsp;current&nbsp;configuration</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	RESTART,
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>puts&nbsp;the&nbsp;component&nbsp;in&nbsp;the&nbsp;default&nbsp;configuration&nbsp;(the&nbsp;fabric&nbsp;one,&nbsp;not&nbsp;necessarily&nbsp;the&nbsp;one&nbsp;we&nbsp;want&nbsp;it&nbsp;to&nbsp;operate&nbsp;with)</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	RESET,

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	SELFTEST
	// makes the component given in the arg to run any available self-test which will publish that info in the ComponentsECL sensory channel
	// suggested by R
}