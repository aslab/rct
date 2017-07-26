/**
 * 
 */
package org.aslab.om.metacontrol.value;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;

/** 
 * <!-- begin-UML-doc -->
 * <p>implementation&nbsp;class&nbsp;to&nbsp;structure&nbsp;the&nbsp;matching&nbsp;of&nbsp;components&nbsp;and&nbsp;specs&nbsp;to&nbsp;see&nbsp;if&nbsp;the&nbsp;components&nbsp;estimated&nbsp;state&nbsp;complies&nbsp;with&nbsp;the&nbsp;goal&nbsp;(specification)</p><p></p><p>similar&nbsp;to&nbsp;CompGoalAtomTracker&nbsp;class,&nbsp;but&nbsp;the&nbsp;third&nbsp;attribute&nbsp;is&nbsp;for&nbsp;internal&nbsp;use&nbsp;in&nbsp;the&nbsp;matching.&nbsp;For&nbsp;the&nbsp;moment&nbsp;we&nbsp;will&nbsp;use&nbsp;the&nbsp;CompGoalAtomracker</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Matching {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public CompGoalAtomTracker matchingSpec;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Component comp2bind2spec;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double matchingScore = new Integer(0);
}