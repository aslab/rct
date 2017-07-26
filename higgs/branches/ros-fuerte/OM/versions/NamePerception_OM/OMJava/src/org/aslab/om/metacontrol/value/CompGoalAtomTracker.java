/**
 * 
 */
package org.aslab.om.metacontrol.value;

import org.aslab.om.metacontrol.knowledge.components.ComponentState;

/** 
 * <!-- begin-UML-doc -->
 * <p>element&nbsp;to&nbsp;track&nbsp;the&nbsp;achievement&nbsp;of&nbsp;each&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class CompGoalAtomTracker {

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>the&nbsp;actual&nbsp;goal:&nbsp;a&nbsp;specification&nbsp;of&nbsp;a&nbsp;component</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentSpecificationAtom componentSpec;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentState componentValue;
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>If&nbsp;achieved&nbsp;is&nbsp;true&nbsp;then&nbsp;the&nbsp;difference&nbsp;is&nbsp;not&nbsp;recomputed&nbsp;unless&nbsp;some&nbsp;flag&nbsp;is&nbsp;set,&nbsp;i.e.&nbsp;one&nbsp;of&nbsp;a&nbsp;main&nbsp;change&nbsp;in&nbsp;the&nbsp;environment&nbsp;from&nbsp;the&nbsp;perceptive&nbsp;system...&nbsp;or&nbsp;maybe&nbsp;it&nbsp;could&nbsp;be&nbsp;updated&nbsp;at&nbsp;a&nbsp;different&nbsp;rate,&nbsp;just&nbsp;for&nbsp;monitoring&nbsp;purposes&nbsp;but&nbsp;not&nbsp;proactive&nbsp;action&nbsp;generation</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean achieved = new Boolean(false); // achieved and achievementLevel encode the value information

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double achievementLevel = new Integer(0);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentDifference difference; // this encode the difference between the spec and the actual value according to domain metrics

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private boolean error = new Boolean(false);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param definition
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public CompGoalAtomTracker(ComponentSpecificationAtom definition) {
		// begin-user-code
		componentSpec = definition;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference updateEval() {
		// begin-user-code

		// this measures the difference between estimates state and goal with domain metrics
		updateDiff();

		// TODO check for duplication of calls with the previous
		// evaluates the metric distance according to goal spec ------------
		achievementLevel = componentSpec.evaluate(componentValue);

		if (achievementLevel > 0.8)	// TODO this is imlpicit eval: should be explicit
			achieved = true;

		else
			achieved = false;
		//-----------------------------------------------------------------

		return difference;
		// end-user-code
	}

	// compute the metric distance from state to goal
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private void updateDiff() {
		// begin-user-code
		// compute difference (invokes metrics in the metamodel of components)
		// only update to a new object if it has changed
		ComponentDifference dif = ((ComponentState) componentSpec.getSpec()).measure(componentValue);
		if (dif == null) {
			difference = null;
			return;
		}
		else if (dif.equals(difference))
			return;
		else
			difference = dif;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param t
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setCreationTime(long t) {
	}

	// this method encodes when a certain component specification is currently impossible to have in the application
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param error
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setError() {
		// begin-user-code
		this.error = true;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean isError() {
		// begin-user-code
		return error;
		// end-user-code
	}
		
	/**
	 * for debugging
	 */
	public void print(){
		if (difference != null){
			difference.print();
		}
	}
	
}