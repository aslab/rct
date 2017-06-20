/**
 * 
 */
package org.aslab.om.ecl.value;

/** 
 * <!-- begin-UML-doc -->
 * <p>interface&nbsp;for&nbsp;an&nbsp;element&nbsp;in&nbsp;an&nbsp;org.aslab.om.ecl&nbsp;that&nbsp;assigns&nbsp;value&nbsp;to&nbsp;others&nbsp;(i.e.&nbsp;a&nbsp;goal,&nbsp;an&nbsp;specification&nbsp;atom)</p><p>it&nbsp;is&nbsp;not&nbsp;the&nbsp;state&nbsp;that&nbsp;is&nbsp;evaluated,&nbsp;but&nbsp;an&nbsp;specification&nbsp;of&nbsp;it</p>
 * NOT IMPLEMENTED
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
@Deprecated
public interface ValueJudge {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method&nbsp;to&nbsp;evaluate&nbsp;if&nbsp;a&nbsp;state&nbsp;is&nbsp;consistent&nbsp;with&nbsp;a&nbsp;specification</p>
	 * <!-- end-UML-doc -->
	 * @param state
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void evaluate(Evaluable state);
}