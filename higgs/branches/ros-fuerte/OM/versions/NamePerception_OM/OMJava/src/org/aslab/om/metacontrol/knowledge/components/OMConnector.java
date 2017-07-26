package org.aslab.om.metacontrol.knowledge.components;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Connector;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;


/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMConnector implements Connector {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String name;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMPort> ports = new HashSet<OMPort>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String quantityType;

	public OMConnector(String name, String type) {
		this.name = name;
		this.quantityType =type;
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
		return name;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Set<Port> getPorts() {
		// begin-user-code
		Set<Port> s = new HashSet<Port>();
		s.addAll(ports);
		return s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Object getQuantityType() {
		// begin-user-code
		return quantityType;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public boolean hasProviders() {
		// begin-user-code
		for (Iterator<OMPort> i = ports.iterator(); i.hasNext();) {
			Port p = i.next();
			if (p.getDirectionality() == Directionality.OUT
				&& !p.error()  )
				return true;
		}

		return false;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void deleteConnector() {
		for (Iterator<OMPort> i = ports.iterator(); i.hasNext();) {
			OMPort p = i.next();
			if (p.getDirectionality() != Directionality.OUT)
				p.connector = null;
			ports.remove(p);
		}
		// end-user-code
	}
	
	public void addPort(Port p){
		// TODO check cast
		ports.add((OMPort) p);
	}


}
