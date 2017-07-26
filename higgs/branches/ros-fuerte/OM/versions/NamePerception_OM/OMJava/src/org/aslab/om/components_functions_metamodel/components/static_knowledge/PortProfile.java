/**
 * 
 */
package org.aslab.om.components_functions_metamodel.components.static_knowledge;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.metacontrol.value.Difference;


/** 
 * <!-- begin-UML-doc -->
 * <p>to&nbsp;define&nbsp;each&nbsp;port&nbsp;a&nbsp;class&nbsp;of&nbsp;components&nbsp;may&nbsp;have</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public interface PortProfile {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentClass getOwner();

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>semantically&nbsp;relevant</p>
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getName();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getQuantityType();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Directionality getDirectionality();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param omPort
	 * @param point
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Port omPort, Port point); // move to port state interface
}