/**
 * 
 */
package org.aslab.om.metacontrol.knowledge.components;

import java.sql.Time;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

import javax.swing.text.html.HTMLDocument.HTMLReader.IsindexAction;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Parameter;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ComponentClass;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.ParameterProfile;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.PortProfile;
import org.aslab.om.ecl.perception.Percept;
import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;
import org.aslab.om.metacontrol.perception.components.PortSingularity;
import org.aslab.om.metacontrol.value.ComponentDifference;
import org.aslab.om.metacontrol.value.Difference;
import org.aslab.om.metacontrol.value.DifferenceImpl;



/** 
 * <!-- begin-UML-doc -->
 * <!--&nbsp;begin-UML-doc&nbsp;--><br><!--&nbsp;end-UML-doc&nbsp;--><br>@author&nbsp;chcorbato
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class OMComponent extends ComponentState implements
		Percept {

	public String name;
	
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public OMComponentClass type;
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<OMParameter> parameters = new HashSet<OMParameter>();

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
	public ComponentStatus status = null;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Stack<ArrayList<String>> log = new Stack<ArrayList<String>>();
	
	public Map<String, Object> internal_state =  new HashMap<String, Object>();
	
	
	public OMComponent(OMComponentClass ctype){
		type = ctype;
		name = type.default_instance_name;
		for(Iterator<OMParameterProfile> i = ctype.parameterProfiles.iterator();i.hasNext();){
			parameters.add( new OMParameter(i.next(),this) );
		}
		
		for(Iterator<OMPortProfile> i = ctype.portProfiles.iterator();i.hasNext();){
			ports.add( new OMPort(i.next(),this) );
		}
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Stack<ArrayList<String>> getInternalState() {
		// begin-user-code
		return log;
		// end-user-code
	}

	// method containing the metamodel metrics for a component
	// it supposed that the object whose method is invoked is a component specification, and the argument is an actual component
	/* (non-Javadoc)
	 * @see org.aslab.om.metacontrol.knowledge.components.ComponentState#measure(org.aslab.om.metacontrol.knowledge.components.ComponentReadOnly)
	 */
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param comp
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public ComponentDifference measure(ComponentState comp) {
		// begin-user-code
		Set<Difference> differences = new HashSet<Difference>();
		DifferenceImpl d;

		// if no component in the state to match the spec
		if (comp == null) {
			d = new DifferenceImpl();
			d.reference = null;
			d.dueValue = this;
			d.computedDiff = 1;
			differences.add(d);
			return new ComponentDifference(comp, this, differences);
		}

		else {

			// check name
			if (this.name != null) {
				if (!this.name.equals(comp.getName())) {
					d = new DifferenceImpl();
					d.reference = comp.getName();
					d.dueValue = this.name;
					d.computedDiff = 1;
					differences.add(d);
				}
			}

			// check class(type)
			// TODO there could be a model of differences for types when there is inheritance
			if (this.type != null) {
				if (this.type != comp.getComponentClass()) {
					d = new DifferenceImpl();
					d.reference = comp.getComponentClass();
					d.dueValue = this.type;
					d.computedDiff = 1;
					differences.add(d);
				}
			}

			// check STATUS
			if (this.status != null) {
				if (this.status != comp.getStatus()) {
					d = new DifferenceImpl();
					d.reference = comp.getStatus();
					d.dueValue = this.status;
					d.computedDiff = 1; // TODO compute a proper difference (metric for the status of components)
					differences.add(d);
				}
			}

			// check parameters
			for (Iterator<OMParameter> iter = this.parameters.iterator(); iter
					.hasNext();) {
				Parameter origin = iter.next();
				Parameter point = comp.getParameter(origin.getProfile());

				Difference di = origin.measure(point);

				if (di != null) {
					differences.add(di);
				}
			}

			// check ports
			for (Iterator<OMPort> iter = this.ports.iterator(); iter.hasNext();) {
				Port origin = iter.next();
				Port point = comp.getPort(origin.getProfile());

				Difference di = origin.measure(point);

				if (di != null)
					differences.add(di);
			}

			if (differences.isEmpty())
				return null;
			else
				return new ComponentDifference(comp, this, differences);
		}

		// end-user-code
	}

	// method to test if the OMComponent specification given as argument will comply with that of this OMComponent
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param c
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public boolean complies(ComponentState c) {
		// begin-user-code
		if (measure(c) == null)
			return true;
		else
			return false;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param c
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double complianceLevel(ComponentState c) {
		// begin-user-code
		if (!complies(c))
			return 0;
		else {
			// TODO calculate something, do something smarter
			return 1;
		}
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * the error model for a component is that of its component class, so this method calls that one
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private boolean errorModel() {
		// begin-user-code		
		boolean updated = type.errorModel(this);
		
		return updated;
		// end-user-code
	}

	/* (non-Javadoc)
	 * @see org.aslab.om.metacontrol.knowledge.components.ComponentReferent#identification(org.aslab.om.metacontrol.perception.components.ComponentSingularity)
	 */
	/** 
	 * <!-- begin-UML-doc -->
	 * this contains the model for perception.identification of components
	 * <!-- end-UML-doc -->
	 * @param sing
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public double recognize(Singularity s) {
		// begin-user-code	
		double level = 1;
		
		ComponentSingularity sing = (ComponentSingularity) s;	// TODO check casting
		// check name
		if (this.name != null && sing.name != null
				&& !this.name.equals(sing.name))
			level = level * 0.5;
		
		// check type
		level = level * ((Referent) this.type).recognize(s); // we use the interface to call the more refined recognize method

		return level;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * method for update the information in this component (percept) with that of the singularity sing
	 * <!-- end-UML-doc -->
	 * @param sing singularity whose information is used to update this percept
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void update(Singularity s) {
		// perceptual function to update a referent with a singularity

		ComponentSingularity sing = (ComponentSingularity) s;	// TODO check casting

		// update name
		if (sing.name != null)
			this.name = sing.name;
		
		// special case a component is now missing
		if (sing.status == ComponentStatus.MISSING) {
			this.status = sing.status;
			this.clearState();
			return;
		}

		// update status with the perceived info - we assumed ACTIVE by default in OMRosAPI.rosSing2compSing()
		if (sing.status != null)
			this.status = sing.status;

		// update parameters
		for (Iterator<OMParameter> i = parameters.iterator(); i.hasNext();) {
			OMParameter p = i.next();
			Object v = sing.parameters.get(p.getName());
			if (v != null) {
				this.setParameter(p.getProfile().getName(), v);
			}
		}
		
		// ports are updated in the perceptor code for components
		
		Object a = sing.internalState.get("log");
		if( (a != null) && (a instanceof ArrayList<?>) )
			this.log.add( (ArrayList<String>) a );
		
		// update internal state
		for( Iterator<String> iter = type.getInternalState().iterator(); iter.hasNext(); ){
			String var = iter.next();
			this.internal_state.put(var, sing.internalState.get(var));
		}
		
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private void clearState() {
		// begin-user-code
		// clear parameters values
		for (Iterator<OMParameter> i = parameters.iterator(); i.hasNext();)
			i.next().setValue(null);

		// clear port connections
		for (Iterator<OMPort> i = ports.iterator(); i.hasNext();) {
			OMPort p = i.next();
			if (p.connector != null) {
				p.connector.ports.remove(p);
				p.connector = null;
			}
		}

		// clear log info  TODO clear rest of InternalState

		log.clear();
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
		return name;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param spec
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	@Deprecated
	public int calculateMatching2Spec(ComponentState spec) {
		// begin-user-code

		int score = 2;

		// for the moment the type has to be exactly the same
		// TODO get a quantified similarity for type
		if (this.type != null && spec.getComponentClass() != this.type)
			return 0;

		if (this.name != null && this.name.equals(spec.getName())) // add a point for the name
			score++;

		// check a level of matching ports
		for (Iterator<Port> spi = spec.getPorts().iterator(); spi.hasNext();) {
			Port sp = spi.next();
			for (Iterator<OMPort> cpi = this.ports.iterator(); cpi.hasNext();) {
				Port p = cpi.next();
				if ( // increment the score for each port connected to a similar port
				(sp.getConnector() == p.getConnector())
						&& (sp.getProfile() == p.getProfile()))
					score++;
			}
		}

		return score;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Set<Parameter> getParameters() {
		// begin-user-code
		Set<Parameter> s = new HashSet<Parameter>();
		s.addAll(parameters);
		return s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param profile
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Parameter getParameter(ParameterProfile profile) {
		// begin-user-code
		for (Iterator<OMParameter> iter = parameters.iterator(); iter.hasNext();) {
			Parameter p = iter.next();
			if (p.getProfile() == profile)
				return p;
		}
		return null;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param parametername
	 * @param value
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public boolean setParameter(String parametername, Object value) {
		// begin-user-code
		for (Iterator<OMParameter> iter = parameters.iterator(); iter.hasNext();) {
			OMParameter p = iter.next();
			if (p.getProfile().getName().equals(parametername)) {
				p.setValue(value);
				return true;
			}
		}
		return false;
		// end-user-code
	}
	
	
	public boolean setPort(String portname, OMConnector connector) {
		// begin-user-code
		for (Iterator<OMPort> iter = ports.iterator(); iter.hasNext();) {
			OMPort p = iter.next();
			if (p.getProfile().getName().equals(portname)) {
				p.connector = connector;
				return true;
			}
		}
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
	public ComponentStatus getStatus() {
		// begin-user-code
		return status;
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
	 * @param profile
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public Port getPort(PortProfile profile) {
		// begin-user-code
		for (Iterator<OMPort> iter = ports.iterator(); iter.hasNext();) {
			Port p = iter.next();
			if (p.getProfile() == profile)
				return p;
		}
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
	public ComponentClass getComponentClass() {
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
	public Set<Port> getOutputPorts() {
		// begin-user-code
		Set<Port> s = new HashSet<Port>();
		for (Iterator<OMPort> i = ports.iterator(); i.hasNext();) {
			Port p = i.next();
			if (p.getDirectionality() == Directionality.OUT)
				s.add(p);
		}
		return s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Port> getInputPorts() {
		// begin-user-code
		Set<Port> s = new HashSet<Port>();
		for (Iterator<OMPort> i = ports.iterator(); i.hasNext();) {
			Port p = i.next();
			if (p.getProfile().getDirectionality() == Directionality.IN)
				s.add(p);
		}
		return s;
		// end-user-code
	}

	public OMPort getPort(String portname) {
		// begin-user-code
		for (Iterator<OMPort> iter = ports.iterator(); iter.hasNext();) {
			OMPort p = iter.next();
			if (p.getProfile().getName().equals(portname))
				return p;
		}
		return null;
		// end-user-code
	}

	// for the moment not used?? TODO check
	public Percept identifyPort(PortSingularity sing) {
		for(Iterator<OMPort> i = ports.iterator(); i.hasNext();){
			Percept p = i.next();
			if ( p.recognize(sing) > 0 )
				return p;
		}
		return null;
	}

	/* (non-Javadoc)
	 * @see org.aslab.om.ecl.perception.Percept#internalModel()
	 */
	@Override
	public boolean internalModel() {
		return errorModel();
	}

	public Map<Port, PortSingularity> identifyPorts(
			Collection<PortSingularity> values) {
		// TODO Auto-generated method stub
		Map<Port, PortSingularity> mapping = new HashMap<Port, PortSingularity>();
		for(Iterator<OMPort> i = ports.iterator(); i.hasNext(); ){
			double ident = 0.3;	// minimal value to have a matching
			PortSingularity matched = null;
			OMPort p = i.next();
			for(Iterator<PortSingularity> j = values.iterator(); j.hasNext();) {
				PortSingularity s = j.next();
				if ( p.identification(s) > ident ) {
					matched = s;
					ident = p.identification(s);
				}
				
			}
			mapping.put(p, matched);			
		}	
		
		return mapping;
	}
	
	@Override
	public String toString(){
		StringBuilder description =  new StringBuilder();
		description.append("--------------------------\n");
		description.append("Component\n");
		description.append("name:\t" + name);
		description.append("\n type:\t" + type.getName());
		description.append("\n status:\t" + status);
		description.append("\n parameters:\n");
		for(Iterator<OMParameter> iter = parameters.iterator(); iter.hasNext();){
			description.append("\t" + iter.next().toString() + "\n");
		}
		description.append("\n ports:\n");
		for(Iterator<OMPort> iter = ports.iterator(); iter.hasNext();){
			description.append("\t" + iter.next().toString() + "\n");
		}
		
		description.append("--------------------------\n");
		return description.toString();
		
	}

	@Override
	public void setTime(Time t) {
		// TODO Auto-generated method stub
		timestamp = t;
	}

}