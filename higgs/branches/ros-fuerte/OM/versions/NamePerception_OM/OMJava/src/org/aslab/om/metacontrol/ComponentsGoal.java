package org.aslab.om.metacontrol;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.ecl.Goal;
import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentsGoal extends Goal {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<CompGoalAtomTracker> atoms = new HashSet<CompGoalAtomTracker>();
	

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentsGoal(Set<CompGoalAtomTracker> a) {
		// begin-user-code
		atoms = a;
		// end-user-code
	}
	
	public Set<StateAtom> getStateSpec(){
		Set<StateAtom> s =  new HashSet<StateAtom>();
		
		for(Iterator<CompGoalAtomTracker> i = atoms.iterator(); i.hasNext();){
			s.add( i.next().componentSpec.getSpec() );
		}
		
		return s;
	}
}
