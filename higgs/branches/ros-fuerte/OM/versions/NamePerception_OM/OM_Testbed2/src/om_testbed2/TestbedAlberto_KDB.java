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
import org.aslab.om.testbeds_knowledge.StageROS;
import org.aslab.om.testbeds_knowledge.LaserModel;


/** 
 * <!-- begin-UML-doc -->
 * <p>for&nbsp;the&nbsp;initial&nbsp;creation&nbsp;of&nbsp;the&nbsp;knowledge&nbsp;database&nbsp;and&nbsp;the&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class TestbedAlberto_KDB extends OM_KDB {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public TestbedAlberto_KDB() {
		// begin-user-code

		ckb = new OMcomponentsKB();
		fkb = new OMfunctionsKB();
		fg = new FunctionalGoal();

		//== Components =========================================================================
	
		// create and add component class laser
		OMComponentClass laser = new LaserModel();
		ckb.addComponentClass(laser);
		// create and add component class fake_kinect_laser
		//OMComponentClass fake_kinect_laser = new FakeKinectLaserModel();
		//ckb.addComponentClass(fake_kinect_laser);
		// create and add component class amcl
		//OMComponentClass amcl = new Amcl();
		//ckb.addComponentClass(amcl);
		// create and add component class amcl
		//OMComponentClass move_base = new MoveBase();
		//ckb.addComponentClass(move_base);		
		
		
		// create initial state components and connectors ----------------------------------------
		
		// laser_scan
//		OMComponent laser_comp = new OMComponent(laser);
//		laser_comp.name = "/laser";
//		laser_comp.setParameter("baudrate", 5600);
//		laser_comp.status = ComponentStatus.ACTIVE;
//		ckb.addEstimatedComponent(laser_comp);
		
		// amcl
		//OMComponent amcl_comp = new OMComponent(amcl);
		//amcl_comp.name = "/amcl";
		// TODO params
		//amcl_comp.status = ComponentStatus.ACTIVE;
		//ckb.addEstimatedComponent(amcl_comp);
				
		// connector stageros->fake_laser_scan
		//OMConnector scan = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		//stageros_comp.setPort("/base_scan", scan);
		//fake_laser_comp.setPort("/base_scan", scan);
		//scan.ports.add(stageros_comp.getPort("/base_scan"));
		//scan.ports.add(fake_laser_comp.getPort("/base_scan"));
		
		// connector fake_laser_scan->amcl
		//OMConnector scan2 = new OMConnector("/scan", "sensor_msgs/LaserScan");
		//fake_laser_comp.setPort("/scan", scan2);
		//amcl_comp.setPort("/scan", scan2);
		//scan2.ports.add(fake_laser_comp.getPort("/scan"));
		//scan2.ports.add(amcl_comp.getPort("/scan"));
		

		//== Functions KB ========================================================================

		// Laser readings function ---------------------------------------------------------------
		OMFunction laser_up = new OMFunction();
		laser_up.description = "get laser scans";

		fkb.functions.add(laser_up);

		// design solution fs_scans1 to get laser scans -------------------------------
		OMFDesign fs_scans1 = new OMFDesign();
		laser_up.realisations.add(fs_scans1);
		fkb.functionSpecs.add(fs_scans1);
		fs_scans1.description = "get laserscans with the driver";
		fs_scans1.confidence = 1;
		fs_scans1.solves.add(laser_up);

		// the roles		
		OMRole r1 = new OMRole();
		r1.description = "laser driver";

		OMComponent role_def_driver = new OMComponent(laser);
		role_def_driver.setParameter("baudrate", 5600);
		role_def_driver.status = ComponentStatus.ACTIVE;

		r1.definition = role_def_driver;

		// add role to function specification
		fs_scans1.roles.add(r1);
		
		//OMRole r2 = new OMRole();
		//r2.description = "laser device";

		//OMComponent role_device = new OMComponent(stageros);
		//role_device.status = ComponentStatus.ACTIVE;

		//r2.definition = role_device;
		
		// define connections
		// connector
		//OMConnector role_scan = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		//role_device.setPort("/base_scan", role_scan);
		//role_def_driver.setPort("/base_scan", role_scan);
		//role_scan.ports.add(role_device.getPort("/base_scan"));
		//role_scan.ports.add(role_def_driver.getPort("/base_scan"));

		// add role to function specification
		//fs_scans1.roles.add(r2);
				
		
		// design solution fs_scans_kinect to get laser scans --------------------------------
		//OMFDesign fs_scans_kinect = new OMFDesign();
		//f1.realisations.add(fs_scans_kinect);
		//fkb.functionSpecs.add(fs_scans_kinect);
		//fs_scans_kinect.confidence = 0.8;
		//fs_scans_kinect.description = "get laserscans with the driver";
		//fs_scans_kinect.solves.add(f1);

		// the roles		
		//OMRole r1k = new OMRole();
		//r1k.description = "laser driver";

		//OMComponent role_def_driver_k = new OMComponent(fake_kinect_laser);
		//role_def_driver_k.status = ComponentStatus.ACTIVE;

		//r1k.definition = role_def_driver_k;

		// add role to function specification
		//fs_scans_kinect.roles.add(r1k);
		
		//OMRole r2k = new OMRole();
		//r2k.description = "laser device";

		//OMComponent role_device_k = new OMComponent(stageros);
		//role_device_k.status = ComponentStatus.ACTIVE;

		//r2k.definition = role_device_k;
		
		// define connections
		// connector
		//OMConnector role_scan_k = new OMConnector("/base_scan", "sensor_msgs/LaserScan");
		//role_device_k.setPort("/base_scan", role_scan_k);
		//role_def_driver_k.setPort("/base_scan", role_scan_k);
		//role_scan_k.ports.add(role_device_k.getPort("/base_scan"));
		//role_scan_k.ports.add(role_def_driver_k.getPort("/base_scan"));

		// add role to function specification
		//fs_scans_kinect.roles.add(r2k);
		
		

		// Localization function -----------------------------------------------------------------
		//OMFunction localization = new OMFunction();
		//localization.description = "estimate pose";

		//fkb.functions.add(localization);

		// design solution for localization --------------------------------
		//OMFDesign amcl_loc = new OMFDesign();
		//localization.realisations.add(amcl_loc);
		//amcl_loc.confidence = 0.8;
		//amcl_loc.description = "localization using amcl";
		//amcl_loc.solves.add(localization);
		//amcl_loc.requires.add(f1); // requires to have laser scans
		
		// the roles		
		//OMRole rloc = new OMRole();
		//rloc.description = "amcl node";
		//OMComponent	role_def_localiz_algorithm = new OMComponent(amcl);
		//role_def_localiz_algorithm.status = ComponentStatus.ACTIVE;
		//rloc.definition = role_def_localiz_algorithm;

		// add role to function specification
		//amcl_loc.roles.add(rloc);
		//----------------------------------------------------------------------------------------
		
		
		// Navigation function -----------------------------------------------------------------
		//OMFunction navigation = new OMFunction();
		//navigation.description = "estimate pose";

		//fkb.functions.add(navigation);

		// design solution for navigation --------------------------------
		//OMFDesign ros_nav = new OMFDesign();
		//navigation.realisations.add(ros_nav);
		//ros_nav.confidence = 0.8;
		//ros_nav.description = "navigation using ros stack";
		//ros_nav.solves.add(navigation);
		//ros_nav.requires.add(f1); // requires to have laser scans
		//ros_nav.requires.add(localization); // requires localization function
		
		// the roles		
		//OMRole rnav = new OMRole();
		//rnav.description = "move_base node";
		
		//OMComponent role_def_navigation_algorithm = new OMComponent(move_base);
		//role_def_navigation_algorithm.status = ComponentStatus.ACTIVE;
		//rnav.definition = role_def_navigation_algorithm;

		// add role to function specification
		//ros_nav.roles.add(rnav);
		//----------------------------------------------------------------------------------------
		
		

		//////////////////////////////////////////////////////////////////////
		// Create initial state for the metacontroller
		// = root objectives at the Functional level //////////////////
		OMObjectiveRoot root1 = new OMObjectiveRoot(1); // initial root objective with max relevance 1
		//root1.description = "instance of localization";
		root1.description = "have a laser working";
		root1.objectiveType = laser_up;

		fkb.ostate.objectives.add(root1);

		// Create goals  =====================================================

		// Functional Goal----------------------------
		// put all of the root objectives into the goal for the org.aslab.om.metacontrol
		// the implicit goal is for their status to be OK
		fg.controlled_objectives.add(root1);

		// end-user-code
	}
}
