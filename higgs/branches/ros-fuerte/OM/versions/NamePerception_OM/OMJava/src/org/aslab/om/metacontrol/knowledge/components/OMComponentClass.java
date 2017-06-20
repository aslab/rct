/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.components_functions_metamodel.components.static_knowledge.ComponentClass;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ParameterProfile;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.PortProfile;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.QuantityProfile;
import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;
import org.aslab.om.metacontrol.perception.components.PortSingularity;


/** 
 * <!-- begin-UML-doc -->
 * <!--&nbsp;begin-UML-doc&nbsp;--><br><!--&nbsp;end-UML-doc&nbsp;--><br>@author&nbsp;chcorbato
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMComponentClass extends NamedElement implements ComponentClass,
		InternalErrorModel, Referent {
	public OMComponentClass(String name2) {
		super(name2);
		default_instance_name = name2;
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMParameterProfile> parameterProfiles = new HashSet<OMParameterProfile>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMPortProfile> portProfiles = new HashSet<OMPortProfile>();
	
	private Map<String, QuantityProfile> internal_state_profile = new HashMap<String, QuantityProfile>(); 

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public InternalErrorModel errorModel; // model containing the specifics of a component class to evaluate a component instance

	
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Map<String, String> deploymentInfo = new HashMap<String, String>();
	
	private ComponentClassStatus status = ComponentClassStatus.AVAILABLE;
	
	public String default_instance_name;

	/** 
	 * <!-- begin-UML-doc -->
	 * @return the deploymentInfo
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Map<String, String> getDeploymentInfo() {
		// begin-user-code
		return deploymentInfo;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
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
	public Set<PortProfile> getPortProfiles() {
		// begin-user-code
		Set<PortProfile> s = new HashSet<PortProfile>();
		s.addAll(portProfiles);
		return s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<String> getInternalState() {
		return internal_state_profile.keySet();
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * this method codes a default model of errors of the component class
	 * <!-- end-UML-doc -->
	 * @param c
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public boolean errorModel(OMComponent c) {
		// begin-user-code
		boolean change = false;
		// input ports update status
		for (Iterator<OMPort> i = c.ports.iterator(); i.hasNext();) {
			OMPort p = i.next();
			if (p.error && p.getDirectionality() == Directionality.IN) {
				c.status = ComponentStatus.FAULT;
				change = true;
			}
		}

		// status from log information
		if (!c.log.isEmpty()) {
			ComponentStatus aux = getStatusFromLog(c.log.firstElement());
			if (aux != null) {
				c.status = aux;
				change = true;
			}
		}

		// ouput ports updated from status
		for (Iterator<OMPort> i = c.ports.iterator(); i.hasNext();) {
			OMPort p = i.next();
			if (c.status != ComponentStatus.ACTIVE
					&& p.getDirectionality() == Directionality.OUT) {
				p.error = true;
				change = true;
			}
		}

		return change;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param log
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentStatus getStatusFromLog(ArrayList<String> log) {
		// begin-user-code	
		//this method shall be overriden by specific component classes
		return null;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Set<ParameterProfile> getParameterProfiles() {
		// begin-user-code
		Set<ParameterProfile> s = new HashSet<ParameterProfile>();
		s.addAll(parameterProfiles);
		return s;
		// end-user-code
	}

	@Override
	public ComponentClassStatus getStatus() {
		return status;
	}

	@Override
	public void setUnavailable() {
		status = ComponentClassStatus.UNAVAILABLE;
	}

	/**
	 * recognition method for component classes
	 * @see org.aslab.om.ecl.perception.Referent#recognize(org.aslab.om.ecl.perception.Singularity)
	 * @throws NullPointerException if the Singularity parameter is null
	 */
	@Override
	public double recognize(Singularity s) {
		
		if(s == null)
			throw new NullPointerException("singularity is null");
		
		double level = 1;
		ComponentSingularity cs = (ComponentSingularity) s;
		
		// check parameters -- TODO check that this works
		if( !recognizeParams(cs) )
			return 0;
		
		// check ports -- TODO check that this works
		if( !recognizePorts(cs) )
			return 0;
				
		return level;
	}
	
	
	/**
	 * Method to check if a ComponentSingularity could correspond to this ComponentClass accroding to its parameters
	 * @param sing a ComponentSingularity
	 * @return true if sing contains parameters with the same names than those defined by this ComponentClass
	 */
	private boolean recognizeParams(ComponentSingularity sing){
		for( Iterator<ParameterProfile> i = this.getParameterProfiles().iterator(); i.hasNext();){
			String name = i.next().getName();
			if( !sing.parameters.containsKey(name) )
				return false;
		}
		return true;
	}
	
	/**
	 * Method to check if a ComponentSingularity could correspond to this ComponentClass according to its ports
	 * @param sing a ComponentSingularity
	 * @return true if sing contains ports with the same names than those defined by this ComponentClass
	 */
	private boolean recognizePorts(ComponentSingularity sing){
		for( Iterator<PortProfile> i = this.getPortProfiles().iterator(); i.hasNext();){
			OMPortProfile p = (OMPortProfile) i.next();			
			
			Iterator<PortSingularity> j = sing.ports.values().iterator();
			while(j.hasNext()){
				PortSingularity ps = j.next();
				if ( p.recognize(ps) > 0.5)
					break;
				if ( !j.hasNext() )	// if no more portprofiles and still none with that name
					return false;	// strict 
			}
		}
		return true;
	}
	
	

}