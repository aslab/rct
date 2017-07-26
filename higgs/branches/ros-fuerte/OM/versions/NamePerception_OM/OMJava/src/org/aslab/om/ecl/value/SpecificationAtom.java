/**
 * 
 */
package org.aslab.om.ecl.value;

import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;


// deprecated class replaced by ComponentSpecificationAtom for this concrete implementation, it could be the seed for an org.aslab.om.ecl generalisation of that class

/** 
 * <!-- begin-UML-doc -->
 * NOT IMPLEMENTED - for the moment replaced by ComponentSpecificationAtom for this concrete implementation, it could be the seed for an org.aslab.om.ecl generalisation of that class
 * <p>minimal&nbsp;unit&nbsp;to&nbsp;express&nbsp;a&nbsp;requirement/constraint&nbsp;in&nbsp;an&nbsp;org.aslab.om.ecl.&nbsp;A&nbsp;goal&nbsp;is&nbsp;a&nbsp;set&nbsp;of&nbsp;SpecificationAtoms</p><p>to&nbsp;implement&nbsp;the&nbsp;Evaluable&nbsp;interface&nbsp;it&nbsp;needs:</p><p>-&nbsp;NO&nbsp;mission&nbsp;related&nbsp;metrics&nbsp;->&nbsp;this&nbsp;go&nbsp;in&nbsp;the&nbsp;goal</p><p>-&nbsp;domain&nbsp;metrics</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class SpecificationAtom {

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>this&nbsp;method&nbsp;shall&nbsp;call&nbsp;the&nbsp;one&nbsp;of&nbsp;the&nbsp;type&nbsp;of&nbsp;the&nbsp;</p>
	 * <!-- end-UML-doc -->
	 * @param comp
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract double evaluate(StateAtom comp);
	
	public abstract StateAtom getSpec();
}