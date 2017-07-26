package om_testbed1;

import om_testbed1.knowledge.FakeLaserModel;

import org.aslab.om.metacontrol.FunctionalGoal;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMComponent;
import org.aslab.om.metacontrol.knowledge.components.OMComponentClass;
import org.aslab.om.metacontrol.knowledge.components.OMcomponentsKB;
import org.aslab.om.metacontrol.knowledge.functions.OMFDesign;
import org.aslab.om.metacontrol.knowledge.functions.OMFunction;
import org.aslab.om.metacontrol.knowledge.functions.OMObjectiveRoot;
import org.aslab.om.metacontrol.knowledge.functions.OMRole;
import org.aslab.om.metacontrol.knowledge.functions.OMfunctionsKB;


/** 
 * <!-- begin-UML-doc -->
 * <p>for&nbsp;the&nbsp;initial&nbsp;creation&nbsp;of&nbsp;the&nbsp;knowledge&nbsp;database&nbsp;and&nbsp;the&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Testbed1_KDB extends org.aslab.om.metacontrol.OM_KDB {

	/** 
	 * <!-- begin-UML-doc -->
	 * constructor for the testbed1
	 * change the code here to try variants: e.g. different initial state
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Testbed1_KDB() {
		// begin-user-code

		ckb = new OMcomponentsKB();
		fkb = new OMfunctionsKB();
		fg = new FunctionalGoal();

		//== Components ==============================================
	
		// create and add component class fake_laser
		OMComponentClass fake_laser = new FakeLaserModel();
		ckb.addComponentClass(fake_laser);
		
		// create initial state components and connectors				
		// fake_laser_scan
		OMComponent fake_laser_comp = new OMComponent(fake_laser);
		fake_laser_comp.name = "/fake_laser_scan_node";
		fake_laser_comp.setParameter("baudrate", 19200);
		fake_laser_comp.status = ComponentStatus.ACTIVE;
		ckb.addEstimatedComponent(fake_laser_comp);	
				
		//== Functions KB =======================================

		OMFunction f1 = new OMFunction();
		f1.description = "get laser scans";

		fkb.functions.add(f1);

		// design solution fs_scans1 to get laser scans ---------
		OMFDesign fs_scans1 = new OMFDesign();
		fs_scans1.description = "get laserscans with the driver";
		fs_scans1.confidence = 1;
		fs_scans1.solves.add(f1);

		// the roles		
		OMRole r1 = new OMRole();
		r1.description = "laser driver";

		OMComponent role_def_driver = new OMComponent(fake_laser);
		role_def_driver.setParameter("baudrate", 5600);
		role_def_driver.status = ComponentStatus.ACTIVE;

		r1.definition = role_def_driver;

		// add role to function specification
		fs_scans1.roles.add(r1);
				
		
		//////
		f1.realisations.add(fs_scans1);
		
		fkb.functionSpecs.add(fs_scans1);
				
		//----------------------------------------------------------

		//////////////////////////////////////////////////////////////////////
		// Create initial state for the metacontroller
		// = root objectives at the Functional level //////////////////
		OMObjectiveRoot root1 = new OMObjectiveRoot(1); // initial root objective with max relevance 1
		root1.description = "instance of f1";
		root1.objectiveType = f1;

		fkb.ostate.objectives.add(root1);

		// Create goals  =====================================================

		// Functional Goal----------------------------
		// put all of the root objectives into the goal for the org.aslab.om.metacontrol
		// the implicit goal is for their status to be OK
		fg.controlled_objectives.add(root1);

		// end-user-code
	}
}
