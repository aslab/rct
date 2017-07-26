/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.functions;

import java.util.HashSet;
import java.util.Set;

import org.aslab.om.ecl.knowledge.KnowledgeBase;
import org.aslab.om.ecl.knowledge.StateAtom;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMfunctionsKB extends KnowledgeBase {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFunction> functions = new HashSet<OMFunction>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFDesign> functionSpecs = new HashSet<OMFDesign>();

	// now attributes that contain the instantaneous state

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMStateObjectives ostate = new OMStateObjectives();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFGrounding> groundings = new HashSet<OMFGrounding>();

	@Override
	public Set<StateAtom> getEstimatedState() {
		// TODO Auto-generated method stub
		return null;
	}

}