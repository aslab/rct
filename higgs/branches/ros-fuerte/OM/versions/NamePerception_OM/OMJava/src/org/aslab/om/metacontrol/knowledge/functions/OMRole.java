/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.functions;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;
import org.aslab.om.metacontrol.knowledge.components.OMComponent;
import org.aslab.om.metacontrol.value.Difference;



/** 
 * <!-- begin-UML-doc -->
 * <p>contains&nbsp;the&nbsp;information&nbsp;to&nbsp;compute&nbsp;if&nbsp;the&nbsp;binding&nbsp;is&nbsp;ok</p><p>the&nbsp;definition&nbsp;of&nbsp;an&nbsp;OMRole&nbsp;is&nbsp;sent&nbsp;from&nbsp;the&nbsp;FunctionalECL&nbsp;to&nbsp;the&nbsp;ComponentsECL&nbsp;as&nbsp;a&nbsp;goal</p><p>the&nbsp;feedback&nbsp;for&nbsp;that&nbsp;goal&nbsp;would&nbsp;be&nbsp;the&nbsp;performer&nbsp;associated&nbsp;to&nbsp;that&nbsp;Role&nbsp;through&nbsp;the&nbsp;Binding</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMRole {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String description;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentState definition;

	// encodes the evaluation metamodel of roles (for the moment no specific model at the application level)
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param performer
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean complies(ComponentState performer) {
		// begin-user-code
		Difference d = definition.measure(performer);
		if (d.getRelativeDiff() == 0)
			return true;
		else
			return false;
		// end-user-code
	}
}