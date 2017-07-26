package org.aslab.om.metacontrol.action;

import java.util.HashSet;
import java.util.Set;

import org.aslab.om.ecl.action.Action;
import org.aslab.om.ecl.action.ActionFeedback;
import org.aslab.om.ecl.action.ActionResult;
import org.aslab.om.metacontrol.value.CompGoalAtomTracker;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class FunctionalAction extends Action {

	
	/** 
	 * <!-- begin-UML-doc -->
	 * number of ever issued action_list (this way a new number is assigned to everyone upon creation)
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private static short num_of_actions = 0;
	
	@Override
	protected short addAction(){
		return num_of_actions++;
	}
	
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
	public FunctionalAction(Set<CompGoalAtomTracker> a) {
		// begin-user-code
		atoms = a;
		// end-user-code
	}

	@Override
	public ActionResult processResult(ActionFeedback feedback) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean timeOut() {
		// TODO Auto-generated method stub
		return false;
	}

}
