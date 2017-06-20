/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ComponentClass;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.PortProfile;
import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.perception.components.PortSingularity;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;


/** 
 * <!-- begin-UML-doc -->
 * <!--&nbsp;begin-UML-doc&nbsp;--><br><!--&nbsp;end-UML-doc&nbsp;--><br>@author&nbsp;chcorbato
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMPortProfile extends NamedElement implements PortProfile, Referent {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Directionality directionality;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String type;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMComponentClass owner;
	
	public OMPortProfile(Directionality directionality, String name, String type,
			OMComponentClass owner) {
		super(name);
		this.directionality = directionality;
		this.type = type;
		this.owner = owner;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentClass getOwner() {
		// begin-user-code
		return owner;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public String getName() {
		// begin-user-code
		return name; // TODO return absolute name (add ComponentClass.name)
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public String getQuantityType() {
		// begin-user-code
		return type;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Directionality getDirectionality() {
		// begin-user-code
		return directionality;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * computes the difference between two component ports
	 * <!-- end-UML-doc -->
	 * @param p1 the origin of the measurement
	 * @param p2 the element that is measured against p1
	 * @return the difference p2 - p1
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Port p1, Port p2){	// TODO check port type
		if (p1 == null)
			return null;

		DifferenceImpl diff = new DifferenceImpl();
		diff.reference = p2;
		diff.dueValue = p1.getConnector();

		if (p2 == null) {
			diff.computedDiff = 1;
			return diff;
		}
		
		else if (p1.getConnector() == null)
			return null;
		
		else if ( p1.getConnector() != null
				&&	p1.getConnector().equals(p2.getConnector())
				&& p2.getProfile().equals(this))
			return null;	// TODO create an empty difference instead of returning null
		else
			diff.computedDiff = 1;

		return diff;
		
	}
	
	
	/**
	 * the recognition method for ports
	 * @see org.aslab.om.ecl.perception.Referent#recognize(org.aslab.om.ecl.perception.Singularity)
	 */
	public double recognize(Singularity s) { // method for perception
		// TODO check cast
		PortSingularity sing = (PortSingularity) s;
		
		// check port direction
		if(sing.direction != this.directionality )
			return 0;
		// check quantity type
		else{
			if( !sing.type.equals("unknown") ){	// if the sing has info about the type
				if ( !sing.type.equals(type) )
					return 0;
				else
					return 1;
			}
			else if ( sing.connectionName.contains(type) ){
				return 1;	// this should be modified for a greater probability but no more identification
			}
			// TODO consider more cases in more detail
			else
				return 1;
		}
	}
}