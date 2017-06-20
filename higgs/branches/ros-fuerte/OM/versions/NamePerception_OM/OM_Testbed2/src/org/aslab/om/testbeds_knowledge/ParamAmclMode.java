package org.aslab.om.testbeds_knowledge;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.metacontrol.knowledge.components.OMParameterProfile;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;





/**
 * @author chcorbato
 * TODO: No reason to have this class and Baudrate, they are equal but for the attributes' values
 */
public class ParamAmclMode extends OMParameterProfile {
	
	public ParamAmclMode(){
		super("mode");
		type = "string";	
	}
	
	/** 
	 * <!-- begin-UML-doc -->
	 * same than for Baudrate
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

		// for baudrate params the difference is either 0 (same baudrate) or 1 (completely different)
		DifferenceImpl diff = new DifferenceImpl();
		diff.reference = p2;
		diff.dueValue = p1.getValue();

		if (p2 == null) {
			diff.computedDiff = 1;
			return diff;
		}

		Integer origin = (Integer) p1.getValue();
		Integer point = (Integer) p2.getValue();		
		if ( origin.equals(point) && p2.getProfile().equals(this))
			return null;
		else
			diff.computedDiff = 1;

		return diff;

		// end-user-code
	}

}
