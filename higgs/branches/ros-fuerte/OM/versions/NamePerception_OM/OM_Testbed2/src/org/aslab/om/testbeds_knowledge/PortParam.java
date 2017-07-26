package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.metacontrol.knowledge.components.OMParameterProfile;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;

public class PortParam extends OMParameterProfile {

	public PortParam() {
		super("port");
		type = "string";
	}

	
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param p1
	 * @param p2
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Parameter p1, Parameter p2) {
		// begin-user-code

		if (p1 == null)
			return null;

		// for string the difference is either 0 or 1
		DifferenceImpl diff = new DifferenceImpl();
		diff.reference = p2;
		diff.dueValue = p1.getValue();

		if (p2 == null) {
			diff.computedDiff = 1;
			return diff;
		}

		String origin = (String) p1.getValue(); // TODO: should be converted to String
		if( origin==null )
			return null;
		String point = (String) p2.getValue();	// TODO: should be converted to String	
		if ( origin.equals(point) && p2.getProfile().equals(this))
			return null;
		else
			diff.computedDiff = 1;

		return diff;

		// end-user-code
	}
}
