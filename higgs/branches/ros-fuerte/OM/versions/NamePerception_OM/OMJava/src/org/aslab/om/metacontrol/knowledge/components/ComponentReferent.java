package org.aslab.om.metacontrol.knowledge.components;

import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public interface ComponentReferent extends Referent {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param sing
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	// this contains the model for perception.identification of components
	public boolean identification(ComponentSingularity sing);

}