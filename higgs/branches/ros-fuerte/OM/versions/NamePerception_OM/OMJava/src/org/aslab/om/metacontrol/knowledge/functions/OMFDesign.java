/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.functions;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.metacontrol.knowledge.components.ComponentClassStatus;


/** 
 * <!-- begin-UML-doc -->
 * <p>contains&nbsp;the&nbsp;knowledge&nbsp;to&nbsp;compute&nbsp;the&nbsp;status&nbsp;of&nbsp;the&nbsp;grounding&nbsp;from&nbsp;the&nbsp;status&nbsp;of&nbsp;the&nbsp;bindings</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMFDesign {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String description;

	/** 
	 * <!-- begin-UML-doc -->
	 * this represents the confidence that this design, when correctly implemented, will realise its functions
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double confidence = new Integer(1); // this represents the confidence that this design, when correctly implemented, will realise its functions

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFunction> solves = new HashSet<OMFunction>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMFunction> requires = new HashSet<OMFunction>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMRole> roles = new HashSet<OMRole>();
	

	/** 
	 * <!-- begin-UML-doc -->
	 * this method encodes the perception model for FunctionSpecifications, which is an error model
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public FDesignStatus errorModel() {
		
		//TODO : internal - this requires an analysis of the availability of components for certain roles... uuuf
		for(Iterator<OMRole> i = roles.iterator(); i.hasNext();) {
			if( i.next().definition.getComponentClass().getStatus() == ComponentClassStatus.UNAVAILABLE)
				return FDesignStatus.UNREALISABLE;
		}

		if (requires == null) // TODO check why requires is null!! I've initialized it!!
			return FDesignStatus.REALISABLE;

		// external dependencies
		if (!requires.isEmpty()) {
			// if any of the required functions is not available, this fspec is unrealisable
			for (Iterator<OMFunction> irequired = requires.iterator(); irequired
					.hasNext();) {
				if (irequired.next().perceptionModel() == FunctionStatus.UNAVAILABLE)
					return FDesignStatus.UNREALISABLE;
			}
		}

		return FDesignStatus.REALISABLE;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * this would correspond to the evaluation model of functions, which is in the type (FSpec)
	 * rather than the instances (FGrounding), despite it applies to the later
	 * relevance of a fspec with respect to a f is relative to the rest of fspec of that f (it is a normalized value)
	 TODO : consider utility of this : maybe OMFunction.relevance(OMFDesign) is enough
	 * <!-- end-UML-doc -->
	 * @param f the Function the relative relevance is computed for
	 * @return the computed relevance
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double relevance(OMFunction f) {
		if (!solves.contains(f))
			return 0;
		else {
			double aux = 0;

			for (Iterator<OMFDesign> ifspec = f.realisations.iterator(); ifspec
					.hasNext();) {
				OMFDesign spec = ifspec.next();
				if (spec.errorModel() == FDesignStatus.REALISABLE)
					aux = aux + f.failureProb(spec);
			}

			if (aux <= 0)
				return 1;
			else
				return f.failureProb(this) / aux;
		}
	}
}