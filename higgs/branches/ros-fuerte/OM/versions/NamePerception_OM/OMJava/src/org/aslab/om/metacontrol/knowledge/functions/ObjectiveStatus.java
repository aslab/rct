package org.aslab.om.metacontrol.knowledge.functions;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public enum ObjectiveStatus {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>this&nbsp;value&nbsp;is&nbsp;assigned&nbsp;by&nbsp;the&nbsp;perception&nbsp;of&nbsp;functions&nbsp;when&nbsp;a&nbsp;function&nbsp;grounding&nbsp;is&nbsp;pursuing&nbsp;this&nbsp;objective&nbsp;and&nbsp;it&nbsp;is&nbsp;in&nbsp;a&nbsp;OK&nbsp;status</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	ADDRESSED, /** 
				 * <!-- begin-UML-doc -->
				 * <p>when&nbsp;there&nbsp;is&nbsp;no&nbsp;FunctionSpecification&nbsp;available&nbsp;to&nbsp;instantiate&nbsp;into&nbsp;a&nbsp;valid&nbsp;FGorunding&nbsp;to&nbsp;fulfill&nbsp;that&nbsp;objective</p>
				 * <!-- end-UML-doc -->
				 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
				 */
	UNACHIEVABLE, //no extant function grounding has been able to achieve it

	/** 
	 * <!-- begin-UML-doc -->
	 * currently NOT USED
	 * this is the OK status -> actually maybe the OK is just the addressed one
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	ACHIEVED, // 

	/** 
	 * <!-- begin-UML-doc -->
	 * current grounding has failed to achieve the objective, but other may do
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	ERROR

}
