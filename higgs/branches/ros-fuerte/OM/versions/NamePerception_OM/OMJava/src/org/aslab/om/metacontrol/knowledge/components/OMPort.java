/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;

import java.sql.Time;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Component;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.PortProfile;
import org.aslab.om.ecl.perception.Percept;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.perception.components.PortSingularity;
import org.aslab.om.metacontrol.value.Difference;



/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMPort implements Port, Percept {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param profile
	 * @param omComponent 
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMPort(OMPortProfile profile, OMComponent component) {
		// begin-user-code
		super();
		this.profile = profile;
		owner = component;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private OMPortProfile profile;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMConnector connector;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentState owner;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean error = new Boolean(false); // a port can be in error or not, two states

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param point
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Difference measure(Port point) {
		// begin-user-code
		return this.profile.measure(this, point);
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public String getConnector() {
		// begin-user-code
		if(connector == null)
			return null;
		else
			return connector.getName();
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Component getOwner() {
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
	public PortProfile getProfile() {
		// begin-user-code
		return profile;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public boolean error() {
		// begin-user-code
		return error;
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
		return profile.getDirectionality();
		// end-user-code
	}

	@Override
	public double recognize(Singularity s) { // method for perception
		// TODO check cast
		PortSingularity sing = (PortSingularity) s;
		
		// check port direction
		if(sing.direction != this.getDirectionality())
			return 0;
		// check quantity type
		if(!sing.type.equals("unkown")){	// if the sing has info about the type
			if ( !sing.type.equals(this.getProfile().getQuantityType()))
				return 0;
		}
		else if ( sing.connectionName.contains(this.getProfile().getName()) ){
			return 1;
		}
		// TODO consider more cases in more detail
		else
			return 1;
		return 1;
	}
	
	public double identification(Singularity s) { // method for perception
		// TODO check cast
		PortSingularity sing = (PortSingularity) s;
		double identification = 1;
		
		// check port direction
		if(sing.direction != this.getDirectionality())
			identification =  identification - 0.3;
		// check quantity type
		if ( !sing.type.equals(this.getProfile().getQuantityType()))
			identification =  identification - 0.3;
		if ( sing.connectionName.equals(this.getProfile().getName()) )
			return identification;
		// TODO consider more cases in more detail
		else {
			identification = identification - 0.3;
			if ( sing.connectionName.startsWith( this.getProfile().getName() ) )
				identification = identification + 0.1;
			if ( sing.connectionName.endsWith( this.getProfile().getName() ) )
				identification = identification + 0.1;
		}
		return identification;
	}

	@Override
	public void update(Singularity s) {
		// TODO check cast		
	}

	public void setConnector(OMConnector connector) {
		this.connector = connector;
	}

	@Override
	public boolean internalModel() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getName() {
		if(profile.getName() == null)
			return "";
		else
			return profile.getName();
	}
	
	/**
	 * for debugging purposes
	 */
	@Override
	public String toString(){
		StringBuilder description =  new StringBuilder();
		description.append(profile.getName() + ":\t");
		if(profile.getDirectionality() == Directionality.IN)
			description.append("<-- ");
		else if (profile.getDirectionality() == Directionality.OUT)
			description.append("--> ");
		else
			description.append("<-> ");
		description.append("connector: " + getConnector());
		if(error)
			description.append("\n \t status: ERROR");
		else
			description.append("\n \t status: OK");

		return description.toString();
	}

	@Override
	public void setTime(Time t) {
		// TODO Auto-generated method stub
		
	}
	
}