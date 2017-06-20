/**
 * 
 */
package org.aslab.om.ecl.knowledge;

import java.util.HashSet;
import java.util.Set;

/** 
 * <!-- begin-UML-doc -->
 * <p>It&nbsp;is&nbsp;the&nbsp;factory&nbsp;responsible&nbsp;for&nbsp;knowledge&nbsp;container&nbsp;and&nbsp;management</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class KnowledgeBase {
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>set&nbsp;containing&nbsp;all&nbsp;the&nbsp;elements&nbsp;in&nbsp;the&nbsp;knowledge&nbsp;database</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<KnowledgeAtom> elements = new HashSet<KnowledgeAtom>();
	
	/** 
	 * <!-- begin-UML-doc -->
	 * <p>access&nbsp;to&nbsp;the&nbsp;container&nbsp;for&nbsp;the&nbsp;long&nbsp;term&nbsp;static&nbsp;knowledge:&nbsp;types</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public StaticModel staticKnowledge;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param elements
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setElements(Set<KnowledgeAtom> elements) {
		// begin-user-code
		this.elements = elements;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<KnowledgeAtom> getElements() {
		// begin-user-code
		return elements;
		// end-user-code
	}
	
	public abstract Set<StateAtom> getEstimatedState();
	
}