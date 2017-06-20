/**
 * 
 */
package org.aslab.om.metacontrol.value;

import java.util.Iterator;
import java.util.Set;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;



/** 
 * <!-- begin-UML-doc -->
 * implementation of the Difference interface for Component objects
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ComponentDifference implements Difference {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private Set<Difference> differences;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ComponentState reference;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private ComponentState dueValue;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param reference
	 * @param dueValue
	 * @param differences
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentDifference(ComponentState reference,
			ComponentState dueValue, Set<Difference> differences) {
		// begin-user-code
		this.differences = differences;
		this.reference = reference;
		this.dueValue = dueValue;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentState getDueValue() {
		// begin-user-code
		return dueValue;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentState getReference() {
		// begin-user-code
		return reference;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public double getRelativeDiff() {
		// begin-user-code
		// obtain the difference as the average of the different deltas

		double result = 0;

		for (Iterator<Difference> iter = differences.iterator(); iter.hasNext();)
			result = result + iter.next().getRelativeDiff();

		return result / differences.size();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param d
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public boolean equals(Difference d) {
		// begin-user-code
		if (d == null)
			return false;

		if (reference != d.getReference())
			return false;

		if (!(d instanceof ComponentDifference))
			return false;

		// check if all the deltas correspond
		for (Iterator<Difference> iter = differences.iterator(); iter.hasNext();) {
			Difference d1 = iter.next();
			boolean matched = false;
			for (Iterator<Difference> iter2 = ((ComponentDifference) d).differences
					.iterator(); iter2.hasNext();) {
				Difference d2 = iter2.next();
				if (d1.equals(d2)) {
					matched = true;
					break;
				}
			}

			if (!matched) // if no delta in d2 is equal to that in d1 then the differences are not equal
				return false;
		}

		return true;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean wrongConfiguration() {
		// begin-user-code		
		for (Iterator<Difference> i = differences.iterator(); i.hasNext();) {
			Difference d = i.next();
			if (d.getReference() instanceof Parameter
					|| d.getReference() instanceof Port)
				return true;
		}
		return false;
		// end-user-code
	}
	
	/**
	 * for debugging purposes
	 */
	public void print(){
		System.out.printf("Difference \n   - target: %s", getDueValue().getName());
		System.out.printf("\n \t number of differences: %d", differences.size());
		for(Iterator<Difference> iter = differences.iterator();iter.hasNext();){
			iter.next().print();		
		}
			
	}
}