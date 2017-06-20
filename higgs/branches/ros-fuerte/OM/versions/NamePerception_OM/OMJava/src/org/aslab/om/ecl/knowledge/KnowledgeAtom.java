/**
 * 
 */
package org.aslab.om.ecl.knowledge;

import java.io.Serializable;
import java.sql.Time;

/** 
 * <!-- begin-UML-doc -->
 * <p>a&nbsp;piece&nbsp;of&nbsp;knowledge</p><p>its&nbsp;ID&nbsp;is&nbsp;unique&nbsp;in&nbsp;a&nbsp;KnowledgeDatabase</p>
 * all knowledge must be serializable
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class KnowledgeAtom implements Serializable {
	/**
	 * attribute because of being Serializable, not used
	 */
	private static final long serialVersionUID = 1L;

	/** 
	 * <!-- begin-UML-doc -->
	 * For the moment not used (is it really necessary? we have the Java object ID)
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Integer ID; // TODO manage and use this attribute
	
	/**
	 * the latest timestamp this knowledge atom was updated
	 */
	protected Time timestamp = new Time(System.currentTimeMillis());
}