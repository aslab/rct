package org.aslab.om.metacontrol.perception.components;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Connector;
import org.aslab.om.components_functions_metamodel.components.instantaneous_state.Port;
import org.aslab.om.components_functions_metamodel.components.static_knowledge.Directionality;
import org.aslab.om.ecl.knowledge.StateAtom;
import org.aslab.om.ecl.perception.Percept;
import org.aslab.om.ecl.perception.Perceptor;
import org.aslab.om.ecl.perception.Referent;
import org.aslab.om.ecl.perception.Sensor;
import org.aslab.om.ecl.perception.Singularity;
import org.aslab.om.metacontrol.knowledge.components.ComponentState;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMComponent;
import org.aslab.om.metacontrol.knowledge.components.OMComponentClass;
import org.aslab.om.metacontrol.knowledge.components.OMConnector;
import org.aslab.om.metacontrol.knowledge.components.OMPort;
import org.aslab.om.metacontrol.knowledge.components.OMcomponentsKB;




public class ComponentsPerceptor extends Perceptor {
	
	protected Set<Percept> percepts = new HashSet<Percept>();	// TODO find a better name
	
	protected Set<Referent> referents =  new HashSet<Referent>();
		
	private OMcomponentsKB ckb;
		
	public ComponentsPerceptor(Sensor s, OMcomponentsKB k) {
		sensor = s;
		ckb = k;
		percepts.addAll(ckb.getEstimatedState());
	}
	
	/** Defines the basic steps of Ig's perception
	 * @see org.aslab.om.ecl.perception.Perceptor#perceive()
	 */
	@Override
	public void perceive(){
		updateReferents();		
		Set<Singularity> singularities = null;
		try {
			singularities = sensoryPerception();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		cognitivePerception(singularities);	
	}

	/**
	 * uses the components' models to infer the status
	 */
	private void propagateErrors() {
		// begin-user-code
		// update status from internal errors (implicitly removes port in error from connectors)	
		for (Iterator<Percept> i = percepts.iterator(); i.hasNext();) {
			Percept c = i.next();
			c.internalModel();
		}
		
		// eliminate Connectors when all their producing ports are in error
		for (Iterator<Connector> i = ckb.getConnectors().iterator(); i.hasNext();) {
			Connector c = i.next();
			
			if ( !c.hasProviders() ) {
				ckb.deleteConnector(c.getName());
			}
		}
				
		// TODO more complex update of errors according to causality flow (error propagation through ports)
		/*
		for(Iterator<OMComponent> i = getSourceComponents(bunch2update).iterator(); i.hasNext();) {
			OMComponent c = i.next();
			
			OMComponent comp = c;
			while ( comp.getOutputPorts().isEmpty() ) {
				
			}
					
			for(Iterator<OMPort> ip = c.ports.iterator(); ip.hasNext();){
				OMPort p = ip.next();
				if( p.error() ){
					p.connector.ports.remove(p);
				}
				
				else {
					addPortConnector(p);
				}
	
			}
			bunch2update.remove(c);
		}*/
	
		// end-user-code
	}

	// method for the perception spec of the ECL
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param goalState 
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void configSensors() {
		// begin-user-code
		Set<String> observe = new HashSet<String>();
		Set<String> ignore = new HashSet<String>();

		// gather referents to actively observe from the components that match the goal
		//if (kbase.getMission() == null)
		//	return;
		
		// observe the referents 
		for (Iterator<Referent> iter = referents.iterator(); iter.hasNext();) {
			Referent ref = iter.next();
			if ( ref.getName()!=null )
				observe.add( ref.getName() );
			else if (ref instanceof ComponentState )	// TODO replace, because the new Component Class should be a referent
				observe.add( ((ComponentState) ref).getComponentClass().getName()  );
		}

		// TODO
		// ignore those atoms in the state that are not part of the mission
		/*for (Iterator<Percept> iter = percepts.iterator(); iter.hasNext();) {
			ComponentState c = (ComponentState) iter.next();
			if ( !observe.contains(c.getName())){
				String s = c.getName();
				ignore.add(s);
			}
		}*/

		if (!observe.isEmpty() || !ignore.isEmpty()) // do it only if there is something to send
			sensor.configureFilter(observe, ignore);
		// end-user-code
	}

	protected Set<Singularity> sensoryPerception() throws IllegalAccessException {	
		if (sensor == null){
			throw new IllegalAccessError("no sensors");
		}
		
		Object sensing = sensor.getSensing();
		
		if ( !( sensing instanceof Set<?> ) )
			throw new IllegalAccessException("sensors do not return a set");
		
		return (Set<Singularity>) sensing;		
	}

	
	/** 
	 * <!-- begin-UML-doc -->
	 * Main perception method for components
	 * the perception of referents from singularities in the case of components
	 * <!-- end-UML-doc -->
	 * @param sensoryInput
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected void cognitivePerception(Set<Singularity> sensoryInput) {		// update with info from singularities
			
		Map<OMPort, String> inputs = new HashMap<OMPort, String>();	// auxiliary map to gather information on input connections from singularities
		Set<ComponentSingularity> tocheckingoal =  new HashSet<ComponentSingularity>();
		// this is only done if the input is not null
		if ( sensoryInput != null) {
			for (Iterator<Singularity> i = sensoryInput.iterator(); i.hasNext();) {
				ComponentSingularity sing = (ComponentSingularity) i.next();
				Percept identified = identifyComponent(sing);
				if (identified != null) 
					updatePercept(identified, inputs, sing);			// TODO check
				else 
					tocheckingoal.add(sing);				
			}
			// identify with goalReferents
			identifyGoalSpec( tocheckingoal, inputs );
		
		}
		
		// remove connectors with no producers
		for (Iterator<Connector> i = ckb.getConnectors().iterator(); i
				.hasNext();) {
			Connector con = i.next();
			if (!con.hasProviders()) {
				ckb.deleteConnector(con.getName());
			}
		}
		
		// this is only done if the input is not null
		if ( sensoryInput != null) {
			// update connections to input ports
			for(Iterator<OMPort> i = inputs.keySet().iterator(); i.hasNext();) {
				OMPort p = i.next();
				p.setConnector(  ckb.getConnector( inputs.get(p) )   );
			}
		}
		
		propagateErrors();
		
		//////////////////////////////////////////////////////////////////////////////////////////
		//TODO ad-hoc for localization error in Ros navigation (error of amcl detected in move_base log)
		Set<StateAtom> state = ckb.getEstimatedState();
		OMComponent amcl = null;
		OMComponent	move_base = null;

		for( Iterator<StateAtom> iter = state.iterator(); iter.hasNext(); ){
			OMComponent comp = (OMComponent) iter.next();
			if( comp.name==null )
				continue;
			if( comp.name.contains("amcl") )
				amcl = comp;		
			else if( comp.name.contains("move") )
				move_base = comp;
		}
		// check if there is the error message in move_base
		if( amcl== null || move_base==null || move_base.log==null )
			return;
		
		for( Iterator<ArrayList<String>> iter = move_base.log.iterator(); iter.hasNext(); ){
			ArrayList<String> array = iter.next();
			for( Iterator<String> j = array.iterator(); j.hasNext(); ){
				String entry = j.next();
				if( entry.contains("Costmap2DROS") ){	// TODO this shouldn't trigger inmediately, but after some secs
					amcl.status = ComponentStatus.ERROR;
					System.out.println("detected amcl error!!!");
				}
				else if( entry.contains("Aborting") ){
					move_base.status = ComponentStatus.ERROR;
					System.out.println("detected amcl error!!!");
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////
	}
	
	
	private void identifyGoalSpec(Set<ComponentSingularity> sings,	Map<OMPort, String> inputs){
		// TODO
		for( Iterator<ComponentSingularity> ising = sings.iterator(); ising.hasNext(); ){
			ComponentSingularity sing = ising.next();
			ComponentState referent = ckb.getMissingSpec( sing.name );
			
			if( referent != null ){
				OMComponent comp = new OMComponent( ((OMComponent) referent).type );
				// fill new comp with singularity info
				updatePercept(comp, inputs, sing); // TODO check: name is not updated
				ckb.getGoalState().componentMatched(comp, referent);
				ckb.addEstimatedComponent(comp);
			}
		}	
	}
	
	
	@Deprecated
	private void identifyGoals(Set<ComponentSingularity> sings,	Map<OMPort, String> inputs) {
		// TODO - null pointer exception-solve
		if( ckb.getGoalState()==null )
			return;
		if( ckb.getGoalState().getMissingSpecs().isEmpty() )
			return;

		for( Iterator<ComponentSingularity> ising = sings.iterator(); ising.hasNext(); ){
			ComponentSingularity sing = ising.next();
			double recognition = 0;
			ComponentState referent = null;
			for( Iterator<ComponentState> i = ckb.getGoalState().getMissingSpecs().iterator(); i.hasNext();) {
				ComponentState r = i.next();
	
				if ( r.recognize(sing) > recognition ) {
					recognition = r.recognize(sing);
					referent = r;
				}				
			}
			
			if( recognition > 0.3 ){
				OMComponent comp = null;
				comp = new OMComponent( ((OMComponent) referent).type );
				// fill new comp with singularity info
				updatePercept(comp, inputs, sing); // TODO check: name is not updated
				ckb.getGoalState().componentMatched(comp, referent);
			}
		}

	}


	/**
	 * Updates the information encoded in an extant percept from a singularity that has been
	 * identified as corresponding to it
	 * @param percept to be updated with info from sing
	 * @param inputs map with input ports and associated sensed connector's name, so as to add those of this component percept
	 * @param sing the singularity whose information will be used to update the percept 
	 */
	private void updatePercept(Percept percept, Map<OMPort, String> inputs,
			Singularity sing) {
		// update internal component info
		percept.update(sing);
		// up to this line the method is generic for every Explicit Perceptor
		
		// update external output connections
		Map<Port, PortSingularity> identifications = ((OMComponent) percept).identifyPorts( ((ComponentSingularity) sing).ports.values() );
		
		
		for(Iterator<Port> j = identifications.keySet().iterator(); j.hasNext(); ){
			Percept p = (OMPort) j.next();
			PortSingularity ps = identifications.get(p);
			if( ps != null ) {
				p.update(ps); // nothing is done, since there is no dynamic info on ports apart from their external connection
				if(((Port) p).getDirectionality()== Directionality.OUT){							
					OMConnector c = ckb.addConnector(ps.connectionName, ps.type, (Port) p);
					((OMPort) p).setConnector(c);								
				}
				else{// for the moment nothing is done nor to be updated for input ports
					inputs.put((OMPort) p, ps.connectionName); 
				}
			}
		}
	}
	
	/** 
	 * <!-- begin-UML-doc -->
	 * returns the previously estimated component corresponding to the component singularity
	 * this method is a component-specific version of identifyPercept()
	 * <!-- end-UML-doc -->
	 * @param sing the ComponentSingularity that is to be matched to the known components
	 * @return the Component that corresponds to that singularity
	 */
	private Percept identifyComponent(ComponentSingularity sing) {
		return ckb.getEstimatedComponent( sing.name );
	}

	/**
	 * Produces a percept if the singularity corresponded to one of the referents
	 * @param sing
	 * @param inputs
	 * @return the percept as an OMComponent if any
	 */
	@Deprecated
	private OMComponent generatePercept(Singularity sing, Map<OMPort, String> inputs) {
		double recognition = 0;
		Referent referent = null;
		for(Iterator<Referent> i = referents.iterator(); i.hasNext();) {
			Referent r = i.next();
			if ( r.recognize(sing) > recognition ) {
				recognition = r.recognize(sing);
				referent = r;
			}
		}
		if( recognition < 0.3)
			return null;
		
		else {
			OMComponent comp = null;
			if ( referent instanceof OMComponentClass )	// TODO for the moment this is never the case
				comp = new OMComponent( (OMComponentClass) referent);
			else if (referent instanceof OMComponent) {
				comp = new OMComponent( ((OMComponent) referent).type );
			}
			// fill new comp with singularity info
			updatePercept(comp, inputs, sing); // TODO check: name is not updated
			
			return comp;
		}
	}
	

	protected void updateReferents() {
		// if there are new referents we update the filtering configuration of sensors
		if ( referents.addAll( percepts ) || referents.addAll( ckb.getGoalStates() )  )		
			configSensors();
		
	}


}
