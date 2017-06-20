package om_testbed2;



import org.aslab.om.metacontrol.FunctionalGoal;
import org.aslab.om.metacontrol.OM_KDB;
import org.aslab.om.metacontrol.knowledge.components.ComponentStatus;
import org.aslab.om.metacontrol.knowledge.components.OMComponent;
import org.aslab.om.metacontrol.knowledge.components.OMComponentClass;
import org.aslab.om.metacontrol.knowledge.components.OMConnector;
import org.aslab.om.metacontrol.knowledge.components.OMcomponentsKB;
import org.aslab.om.metacontrol.knowledge.functions.OMFDesign;
import org.aslab.om.metacontrol.knowledge.functions.OMFunction;
import org.aslab.om.metacontrol.knowledge.functions.OMObjectiveRoot;
import org.aslab.om.metacontrol.knowledge.functions.OMRole;
import org.aslab.om.metacontrol.knowledge.functions.OMfunctionsKB;
import org.aslab.om.testbeds_knowledge.Amcl;
import org.aslab.om.testbeds_knowledge.FakeKinectLaserModel;
import org.aslab.om.testbeds_knowledge.FakeLaserModel;
import org.aslab.om.testbeds_knowledge.MoveBase;
import org.aslab.om.testbeds_knowledge.Pioneer;
import org.aslab.om.testbeds_knowledge.StageROS;
import org.aslab.om.testbeds_knowledge.LaserModel;


/** 
 * <!-- begin-UML-doc -->
 * <p>for&nbsp;the&nbsp;initial&nbsp;creation&nbsp;of&nbsp;the&nbsp;knowledge&nbsp;database&nbsp;and&nbsp;the&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class TestbedAlberto2_KDB extends OM_KDB {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public TestbedAlberto2_KDB() {
		// begin-user-code

		ckb = new OMcomponentsKB();
		fkb = new OMfunctionsKB();
		fg = new FunctionalGoal();

		//== Components =========================================================================
	
		// create and add component class laser
		OMComponentClass laser = new LaserModel();
		ckb.addComponentClass(laser);
		
		//create and add component class pioneer
		OMComponentClass pioneer = new Pioneer();
		ckb.addComponentClass(pioneer);
		
		//create and add component class amcl
		OMComponentClass amcl = new Amcl();
		ckb.addComponentClass(amcl);
		
		// create initial state components and connectors ----------------------------------------
		
		//We do not give any initial estimation

		//== Functions KB ========================================================================

		// Basic function ---------------------------------------------------------------
		OMFunction ftotal = new OMFunction();
		ftotal.description = "que el sistema funcione";

		fkb.functions.add(ftotal);

		// design solution fd_principal to get laser scans -------------------------------
		OMFDesign fd_principal = new OMFDesign();
		ftotal.realisations.add(fd_principal);
		fkb.functionSpecs.add(fd_principal);
		fd_principal.description = "solucion para que el sistema funcione";
		fd_principal.confidence = 1;
		fd_principal.solves.add(ftotal);

		// r1 = role_laser = laser		
		OMRole r1 = new OMRole();
		r1.description = "laser driver";
		OMComponent role_laser = new OMComponent(laser);
		role_laser.setParameter("baudrate", 5600);
		role_laser.status = ComponentStatus.ACTIVE;
		r1.definition = role_laser;
		fd_principal.roles.add(r1);// add role to function specification
		

		// r2 = role_robot = pioneer
		OMRole r2 = new OMRole();
		r2.description = "el robot";
		OMComponent role_robot = new OMComponent(pioneer);
		role_robot.setParameter("port", "/dev/ttyUSB1");
		role_robot.status = ComponentStatus.ACTIVE;
		r2.definition = role_robot;
		fd_principal.roles.add(r2);// add role to function specification
		
		// r3 = role_loc = amcl		
		OMRole r3 = new OMRole();
		r3.description = "amcl node";
		OMComponent	role_loc = new OMComponent(amcl);
		role_loc.status = ComponentStatus.ACTIVE;
		r3.definition = role_loc;
		fd_principal.roles.add(r3);
		
		
		// define connections
		// connector
		OMConnector role_scan = new OMConnector("/scan", "sensor_msgs/LaserScan");
		role_laser.setPort("/scan", role_scan);
		role_loc.setPort("/scan", role_scan);
		role_scan.ports.add(role_laser.getPort("/scan"));
		role_scan.ports.add(role_loc.getPort("/scan"));


		
		//////////////////////////////////////////////////////////////////////
		// Create initial state for the metacontroller
		// = root objectives at the Functional level //////////////////
		OMObjectiveRoot root1 = new OMObjectiveRoot(1); // initial root objective with max relevance 1
		//root1.description = "instance of localization";
		root1.description = "have a laser working";
		root1.objectiveType = ftotal;

		fkb.ostate.objectives.add(root1);

		// Create goals  =====================================================

		// Functional Goal----------------------------
		// put all of the root objectives into the goal for the org.aslab.om.metacontrol
		// the implicit goal is for their status to be OK
		fg.controlled_objectives.add(root1);

		// end-user-code
	}
}
