/**
 * 
 */
package org.aslab.om.metacontrol;

import java.util.Map;
import java.util.Set;

import org.aslab.om.ecl.action.ActionFeedback;
import org.aslab.om.ecl.action.Actuator;
import org.aslab.om.ecl.perception.Sensor;
import org.aslab.om.metacontrol.action.ReconfigurationCommand;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;


/** 
 * <!-- begin-UML-doc -->
 * <p>This&nbsp;abstract&nbsp;class&nbsp;is&nbsp;the&nbsp;sensing&nbsp;and&nbsp;acting&nbsp;interfaces&nbsp;for&nbsp;the&nbsp;org.aslab.om.metacontrol&nbsp;with&nbsp;the&nbsp;system&nbsp;or&nbsp;plant&nbsp;&nbsp;it&nbsp;controls.</p><p>This&nbsp;class&nbsp;actually&nbsp;represents&nbsp;a&nbsp;contract&nbsp;for&nbsp;the&nbsp;developer&nbsp;using&nbsp;the&nbsp;OMJava&nbsp;library,&nbsp;so&nbsp;as&nbsp;to&nbsp;connect&nbsp;an&nbsp;instance&nbsp;of&nbsp;OMmetacontroller&nbsp;with&nbsp;the&nbsp;system&nbsp;to&nbsp;(meta-)control</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class PlantAPI implements Sensor, Actuator {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Object getSensing() {
		// begin-user-code
		return getComponentSensing();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void executeAction(Object a) {
		// TODO check action type and rise an exception if not appropriate
		if (a != null )
			executeReconfiguration((Set<ReconfigurationCommand>) a);
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	abstract protected Set<ComponentSingularity> getComponentSensing();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	abstract protected void executeReconfiguration(Set<ReconfigurationCommand> a);
	
	abstract public Map<Short, ActionFeedback> getFeedback();


}