package org.aslab.om.metacontrol;

import java.util.HashSet;
import java.util.Set;

import org.aslab.om.ecl.Goal;
import org.aslab.om.metacontrol.knowledge.functions.OMObjectiveRoot;



/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class FunctionalGoal extends Goal {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMObjectiveRoot> controlled_objectives = new HashSet<OMObjectiveRoot>();
}
