package org.aslab.om.metacontrol.action;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.aslab.om.ecl.action.ActionStatus;
import org.aslab.om.ecl.action.Command;



/** 
 * <!-- begin-UML-doc -->
 * class to encode the information in the scope of the components actuator
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class ReconfigurationCommand extends Command{

	/** 
	 * <!-- begin-UML-doc -->
	 * which command this is: kill a component, launch it, reconfigure it...
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ComponentActionType type;
	
	public String target;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ActionStatus status = ActionStatus.WAITING; // to be updated by the actuator

	
	/** 
	 * <!-- begin-UML-doc -->
	 * the arguments or parameters for the command
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Map<String, Object> arguments = new HashMap<String, Object>();

	/** 
	 * <!-- begin-UML-doc -->
	 * upon creation, the number of ever issued command is incremented and 
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ReconfigurationCommand(short id) {
		super(id);
	}

	/**
	 * for debugging purposes
	 */
	public void print() {
		switch (type) {
		case KILL: {
			System.out.println("\t kill component");
			break;
		}

		case LAUNCH: {
			System.out.println("\t launch component");
			break;
		}

		case RECONFIGURE: {
			System.out.println("\t reconfigure component");
			break;
		}

		case RESET: {
			System.out.println("\t reset component");
			break;
		}

		case RESTART: {
			System.out.println("\t restart component");
			break;
		}
		}
		
		// print each argument with its value (if the value is printable)
		for(Iterator<String> iter = arguments.keySet().iterator(); iter.hasNext();){
			String arg = iter.next();
			System.out.println("\t \t" + arg + " :\t" + arguments.get(arg));
		}
		
	}

}
