package om_testbed2;

import org.aslab.om.metacontrol.FunctionalGoal;
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
import org.aslab.om.testbeds_knowledge.FakeKinectLaserModel;
import org.aslab.om.testbeds_knowledge.FakeLaserModel;
import org.aslab.om.testbeds_knowledge.StageROS;



/** 
 * <!-- begin-UML-doc -->
 * <p>for&nbsp;the&nbsp;initial&nbsp;creation&nbsp;of&nbsp;the&nbsp;knowledge&nbsp;database&nbsp;and&nbsp;the&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Testbed2b_KDB extends org.aslab.om.metacontrol.OM_KDB {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Testbed2b_KDB() {
		// begin-user-code

		ckb = new OMcomponentsKB();
		fkb = new OMfunctionsKB();
		fg = new FunctionalGoal();

		//== Components ==============================================
	
		// create and add component class stageros
		OMComponentClass stageros = new StageROS();
		ckb.addComponentClass(stageros);
		// create and add component class fake_laser
		OMComponentClass fake_laser = new FakeLaserModel();
		ckb.addComponentClass(fake_laser);
		// create and add component class fake_kinect_laser
		OMComponentClass fake_kinect_laser = new FakeKinectLaserModel();
		ckb.addComponentClass(fake_kinect_laser);

		
		// create initial state components and connectors
		
		// stageros
		OMComponent stageros_comp = new OMComponent(stageros);
		stageros_comp.name = "/stageros";
		stageros_comp.status = ComponentStatus.ACTIVE;
		ckb.addEstimatedComponent(stageros_comp);
		
		// fake_laser_scan
		OMComponent fake_laser_comp = new OMComponent(fake_laser);
		fake_laser_comp.name = "/fake_laser_scan_node";
		fake_laser_comp.setParameter("baudrate", 5600);
		fake_laser_comp.setParameter("port", "/usr/local/ros-aslab-electric/OM_Testbed2/aux/laser_port");
		fake_laser_comp.status = ComponentStatus.ACTIVE;
		ckb.addEstimatedComponent(fake_laser_comp);	
				
		// connector
		OMConnector scan = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		stageros_comp.setPort("/base_scan", scan);
		fake_laser_comp.setPort("/base_scan", scan);
		scan.ports.add(stageros_comp.getPort("/base_scan"));
		scan.ports.add(fake_laser_comp.getPort("/base_scan"));

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
		
		OMRole r2 = new OMRole();
		r2.description = "laser device";

		OMComponent role_device = new OMComponent(stageros);
		role_device.status = ComponentStatus.ACTIVE;

		r2.definition = role_device;
		
		// define connections
		// connector
		OMConnector role_scan = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		role_device.setPort("/base_scan", role_scan);
		role_def_driver.setPort("/base_scan", role_scan);
		role_scan.ports.add(role_device.getPort("/base_scan"));
		role_scan.ports.add(role_def_driver.getPort("/base_scan"));

		// add role to function specification
		fs_scans1.roles.add(r2);
		
		//////
		f1.realisations.add(fs_scans1);
		
		fkb.functionSpecs.add(fs_scans1);
		
		// design solution fs_scans1 to get laser scans --------------------------------
		OMFDesign fs_scans_kinect = new OMFDesign();
		fs_scans_kinect.confidence = 0.8;
		fs_scans_kinect.description = "get laserscans with the driver";
		fs_scans_kinect.solves.add(f1);

		// the roles		
		OMRole r1k = new OMRole();
		r1k.description = "laser driver";

		OMComponent role_def_driver_k = new OMComponent(fake_kinect_laser);
		role_def_driver_k.status = ComponentStatus.ACTIVE;

		r1k.definition = role_def_driver_k;

		// add role to function specification
		fs_scans_kinect.roles.add(r1k);
		
		OMRole r2k = new OMRole();
		r2k.description = "laser device";

		OMComponent role_device_k = new OMComponent(stageros);
		role_device_k.status = ComponentStatus.ACTIVE;

		r2k.definition = role_device_k;
		
		// define connections
		// connector
		OMConnector role_scan_k = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		role_device_k.setPort("/base_scan", role_scan_k);
		role_def_driver_k.setPort("/base_scan", role_scan_k);
		role_scan_k.ports.add(role_device_k.getPort("/base_scan"));
		role_scan_k.ports.add(role_def_driver_k.getPort("/base_scan"));

		// add role to function specification
		fs_scans_kinect.roles.add(r2k);
		
		//////
		f1.realisations.add(fs_scans_kinect);
		
		fkb.functionSpecs.add(fs_scans_kinect);

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
