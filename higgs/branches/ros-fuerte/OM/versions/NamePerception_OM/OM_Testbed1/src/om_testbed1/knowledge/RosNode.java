package om_testbed1.knowledge;

import java.util.ArrayList;
import java.util.Iterator;

import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMComponentClass;


/** 
 * <!-- begin-UML-doc -->
 * class&nbsp;to&nbsp;encode&nbsp;the&nbsp;knowledge&nbsp;about&nbsp;a&nbsp;set&nbsp;of&nbsp;ComponentClasses:&nbsp;those&nbsp;that&nbsp;are&nbsp;Ros&nbsp;nodes&nbsp;&nbsp;
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */

public class RosNode extends OMComponentClass {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public RosNode(String name) {
		// begin-user-code
		super(name);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param logEntry
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentStatus getStatusFromLog(ArrayList<String> logEntry) {
		if( logEntry == null)
			return null;
		// begin-user-code
		for (Iterator<String> error = logEntry.iterator(); error.hasNext();) {
			if (error.next().contains("ERROR"))
				return ComponentStatus.ERROR;
		}
		return ComponentStatus.ACTIVE;
		// end-user-code
	}

}