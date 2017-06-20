/**
 * 
 */
package org.aslab.om.metacontrol.value;

/** 
 * <!-- begin-UML-doc -->
 * implementation of the Difference interface for objects in the domain of Components
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class DifferenceImpl implements Difference {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Object reference;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Object dueValue;
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>(baseValue&nbsp;-&nbsp;dueValue)/&nbsp;baseValue&nbsp;if&nbsp;possible&nbsp;to&nbsp;compute&nbsp;given&nbsp;the&nbsp;domain&nbsp;metrics&nbsp;for&nbsp;these&nbsp;types&nbsp;of&nbsp;values</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double computedDiff;

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

		else if (reference != d.getReference())
			return false;

		else if (dueValue != null && 
				dueValue.equals(d.getDueValue()))
			return true;
		
		else if (dueValue == null && d.getDueValue() == null)
			return true;

		else
			return false;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Object getReference() {
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
	public Object getDueValue() {
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
	public double getRelativeDiff() {
		// begin-user-code
		return computedDiff;
		// end-user-code
	}

	@Override
	public void print() {
		// TODO Auto-generated method stub
	}

}