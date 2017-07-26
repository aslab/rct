/**
 * this package contains knowledge elements for instances of OM_KDB, that is, models of components, functions, etc
 */
package om_testbed1.knowledge;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.metacontrol.knowledge.components.OMParameterProfile;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;


/** 
 * <!-- begin-UML-doc -->
 * class to create the ParameterProfile baudrate
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Baudrate extends OMParameterProfile {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Baudrate() {
		// begin-user-code
		super("baudrate");
		type = "baud";
		// end-user-code
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