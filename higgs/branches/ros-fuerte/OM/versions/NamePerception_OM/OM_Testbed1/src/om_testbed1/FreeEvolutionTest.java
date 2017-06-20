/**
 * 
 */
package om_testbed1;

import java.util.Scanner;

import org.aslab.om.metacontrol.OM_KDB;
import org.aslab.om.metacontrol.OMmetacontroller;

/** 
 * <!-- begin-UML-doc -->
 * <p>class&nbsp;for&nbsp;<b>testing&nbsp;</b>purposes&nbsp;&nbsp;that&nbsp;contains&nbsp;a&nbsp;main&nbsp;method&nbsp;and&nbsp;necessary&nbsp;assets&nbsp;to&nbsp;test&nbsp;the&nbsp;implementation&nbsp;of&nbsp;the&nbsp;metacontroller,&nbsp;in&nbsp;a&nbsp;case&nbsp;in&nbsp;which&nbsp;it&nbsp;is&nbsp;connected&nbsp;to&nbsp;no&nbsp;plant,&nbsp;but&nbsp;works&nbsp;departing&nbsp;from&nbsp;a&nbsp;given&nbsp;model&nbsp;of&nbsp;the&nbsp;plant,&nbsp;a&nbsp;certain&nbsp;initial&nbsp;state&nbsp;of&nbsp;it,&nbsp;and&nbsp;a&nbsp;given&nbsp;goal.&nbsp;It&nbsp;is&nbsp;expected&nbsp;to&nbsp;produce&nbsp;the&nbsp;necessary&nbsp;action&nbsp;to&nbsp;direct&nbsp;the&nbsp;plant&nbsp;towards&nbsp;the&nbsp;goal</p>
 * <!-- end-UML-doc -->
 * @author chcorbato
 */
public class FreeEvolutionTest {

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	static OMmetacontroller metacontrol;

	/** 
	 * <!-- begin-UML-doc -->
	 * application thread: the metacontroller is created and initialized by populating its knowledge with
	 * an instance of Testbed1_KDB and connecting it to an instance of FakedRos API. Then it is run, allowing
	 * to stop, resume, etc. through the keyboard
	 * <!-- end-UML-doc -->
	 * @param args
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public static void main(String[] args) {
		// begin-user-code
		
		// initialization
		FakedRosAPI faked_ros_system = new FakedRosAPI();
		OM_KDB kdb = new Testbed1_KDB();

		// create a goal from that state and insert that as default in the creation of the metacontroller
		metacontrol = new OMmetacontroller(kdb.fg, kdb,
				faked_ros_system);
		
		// running the system
		metacontrol.start();

		System.out.println("k - kill demo\n"
				+ "p - pause execution of metacontroller\n"
				+ "r - restart the metacontroller\n"
				+ "s - resume execution of the metacontroller\n"
				+ "c - print components estimated state\n");
		Scanner input = new Scanner(System.in);

		while (true) {
			switch (input.next().charAt(0)) {
			case 'c':
				System.out.println(metacontrol.getCompEstimatedState());
				break;
			case 'k':
				System.out.println("Demo ended");
				metacontrol.stop();
				return;
			case 'p':
				metacontrol.disable();
				System.out.println("org.aslab.om.metacontrol paused");
				break;
			case 'r':
				metacontrol.stop();
				metacontrol.start();
				System.out.println("org.aslab.om.metacontrol restarted");
				break;
			case 's':
				metacontrol.enable();
				System.out.println("org.aslab.om.metacontrol resumed");
				break;
			}
		}
		// end-user-code
	}
}