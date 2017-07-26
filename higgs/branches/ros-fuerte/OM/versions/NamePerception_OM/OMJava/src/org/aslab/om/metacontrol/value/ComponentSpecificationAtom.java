/**
 * 
 */
package org.aslab.om.metacontrol.value;

import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.ecl.value.SpecificationAtom;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;



/** 
 * <!-- begin-UML-doc -->
 * <p>minimal&nbsp;unit&nbsp;to&nbsp;express&nbsp;a&nbsp;requirement/constraint&nbsp;in&nbsp;an&nbsp;org.aslab.om.ecl.&nbsp;A&nbsp;goal&nbsp;is&nbsp;a&nbsp;set&nbsp;of&nbsp;SpecificationAtoms</p><p>to&nbsp;implement&nbsp;the&nbsp;Evaluable&nbsp;interface&nbsp;it&nbsp;needs:</p><p>-&nbsp;NO&nbsp;mission&nbsp;related&nbsp;metrics&nbsp;->&nbsp;this&nbsp;go&nbsp;in&nbsp;the&nbsp;goal</p><p>-&nbsp;domain&nbsp;metrics</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentSpecificationAtom extends SpecificationAtom {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>influence&nbsp;of&nbsp;this&nbsp;specAtom&nbsp;on&nbsp;the&nbsp;goal&nbsp;it&nbsp;is&nbsp;part&nbsp;of</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double weight = new Integer(1); // in between 0...1 (1 by default)	// internal encoding evaluation info or constraints
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>knowledge&nbsp;element,&nbsp;state&nbsp;one,&nbsp;this&nbsp;specification&nbsp;is&nbsp;about</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ComponentState spec;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param definition
	 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentSpecificationAtom(ComponentState definition) {
		// begin-user-code
		spec = definition;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>this&nbsp;method&nbsp;shall&nbsp;call&nbsp;the&nbsp;one&nbsp;of&nbsp;the&nbsp;type&nbsp;of&nbsp;the&nbsp;</p>
	 * <!-- end-UML-doc -->
	 * @param comp
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double evaluate(StateAtom comp) {
		ComponentState component = (ComponentState) comp;
		// begin-user-code
		ComponentDifference d = spec.measure(component);
		if (d == null)
			return 1;
		else
			return 1 - d.getRelativeDiff() * weight;
		// end-user-code
	}

	@Override
	public StateAtom getSpec() {
		return spec;
	}
	
	public ComponentState getComponentSpec() {
		return spec;
	}
	
	
}