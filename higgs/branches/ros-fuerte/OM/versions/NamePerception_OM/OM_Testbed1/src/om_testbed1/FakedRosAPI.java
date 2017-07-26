/**
 * package that contains the Testbed1 for the OM project. The plant is simulated, and no sensing
 * information enters the OMmetacontroller. Since the initial state of components does not match
 * the functional requirements given as goal, an action is generated to reconfigure the baudrate
 * of a fake_laser component (which actually does not exist)
 */
package om_testbed1;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.ecl.action.ActionFeedback;
import org.aslab.om.metacontrol.PlantAPI;
import org.aslab.om.metacontrol.action.ReconfigurationCommand;
import org.aslab.om.metacontrol.perception.components.ComponentSingularity;



/** 
 * <!-- begin-UML-doc -->
 * this class is a dumb simulation of the OMRosAPI class, providing sensing and acting connection for an OMmetacontroller
 * <!-- end-UML-doc -->
 * @author chcorbato
 */
public class FakedRosAPI extends PlantAPI {
	
	private Set<ComponentSingularity> sensoryBuffer = new HashSet<ComponentSingularity>();

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	public void clearBuffer() {
		// TODO Auto-generated method stub
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @return
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	@Override
	protected Set<ComponentSingularity> getComponentSensing() {
		return sensoryBuffer;
	}


	@Override
	public void configureFilter(Set<String> o, Set<String> i) {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void executeReconfiguration(Set<ReconfigurationCommand> reconfiguration) {
		// TODO add more complex simulation of action_list
		
		// for debugging purpose
		System.out.println("action command:");
		for(Iterator<ReconfigurationCommand> iter = reconfiguration.iterator(); iter.hasNext();){
			iter.next().print(); 
		}
	}

	@Override
	public Map<Short, ActionFeedback> getFeedback() {
		return new HashMap<Short, ActionFeedback>();
	}
	
}