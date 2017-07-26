/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;


import java.util.HashSet;
import java.util.Set;

import org.aslab.om.ecl.knowledge.SystemState;

/** 
 * <!-- begin-UML-doc -->
 * <p>object&nbsp;<b>container</b>&nbsp;<b></b>to&nbsp;access&nbsp;a&nbsp;definition&nbsp;of&nbsp;components&nbsp;of&nbsp;a&nbsp;system:</p><p>it&nbsp;can&nbsp;be&nbsp;the&nbsp;systems&nbsp;state,&nbsp;the&nbsp;an&nbsp;specification&nbsp;of&nbsp;components&nbsp;for&nbsp;a&nbsp;goal...</p><p>is&nbsp;it&nbsp;necessary&nbsp;to&nbsp;add&nbsp;an&nbsp;attribute&nbsp;to&nbsp;directly&nbsp;access&nbsp;connectors?</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
// TODO : determine its utility, for the moment not used
public class OMStateComponents extends SystemState {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMComponent> components = new HashSet<OMComponent>();
}