import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.CORBA.portable.ObjectImpl;
import org.omg.CORBA.ORB;

import higgs.*;
import java.lang.management.*;
import java.util.*;
import java.util.regex.*;
import java.io.*;

/**
 * 
 * @author Marcos Salom
 * @author Francisco Jesús Arjonilla
 *         <p>
 *         The CORBA servant.
 *         Creation and publication of the servant. Synchronization with arduinoProcessing.
 *         </p>
 */

class ArduinoImpl extends ArduinoPOA {

	private ORB orb;

	public void setORB(ORB orb_val) {
		orb = orb_val;
	}

	
	public void TurnOn(Device dev)
	{
		if (dev == Device.DevWrist)
			mainClass.lista_de_ordenes.add(new orden(6,38));
		else if (dev == Device.DevLaser)
			mainClass.lista_de_ordenes.add(new orden(6,37));
		else if (dev == Device.DevCamera)
			mainClass.lista_de_ordenes.add(new orden(6,36));
		else if (dev == Device.DevGPS)
			mainClass.lista_de_ordenes.add(new orden(6,35));
		else if (dev == Device.DevServo)
			mainClass.lista_de_ordenes.add(new orden(6,33));
		else if (dev == Device.DevSensors)
			mainClass.lista_de_ordenes.add(new orden(6,32));
	}
	public void TurnOff(Device dev)
	{
		if (dev == Device.DevWrist)
			mainClass.lista_de_ordenes.add(new orden(7,38));
		else if (dev == Device.DevLaser)
			mainClass.lista_de_ordenes.add(new orden(7,37));
		else if (dev == Device.DevCamera)
			mainClass.lista_de_ordenes.add(new orden(7,36));
		else if (dev == Device.DevGPS)
			mainClass.lista_de_ordenes.add(new orden(7,35));
		else if (dev == Device.DevServo)
			mainClass.lista_de_ordenes.add(new orden(7,33));
		else if (dev == Device.DevSensors)
			mainClass.lista_de_ordenes.add(new orden(7,32));
	}
	
	/**
	 * Method that sets the new PID's setpoint
	 * 
	 * @param referencia: New setpoint
	 * 
	 */
	public void cambiarReferencia(double referencia) {

		// Execution_Thread.orden.cambiar_inclinacion((float)(referencia));
		mainClass.orden.cambiar_inclinacion((float) (referencia));
	}
	
	public double getReference(){
		return mainClass.orden.leer_vector_corba(19);
	}

	/**
	 * Switches ON a digital pin in the Arduino board
	 * 
	 * @param pin to be switched ON
	 *           
	 */
	public void encenderPin(short pin) {

		// Execution_Thread.orden.cambiar_orden(6,pin);
		mainClass.lista_de_ordenes.add(new orden(6, pin));
	}

	/**
	 * Switches OFF a digital pin in the Arduino board
	 * 
	 * @param pin to be switched OFF
	 *            
	 */
	public void apagarPin(short pin) {

		// Execution_Thread.orden.cambiar_orden(7,pin);
		mainClass.lista_de_ordenes.add(new orden(7, pin));
	}

	/**
	 * Enables or disables the PID controller
	 */
	public void activarPid() {

		// Execution_Thread.orden.cambiar_orden(4,0);
		mainClass.lista_de_ordenes.add(new orden(4, 0));
	}

	/**
	 * @return Runs the start up for the Potentiometer to work properly
	 */
	public void inicializarIncl() {

		// Execution_Thread.orden.cambiar_orden(5,0);
		mainClass.lista_de_ordenes.add(new orden(5, 0));
	}

	/**
	 * Method that returns the readings from the v/i sensor for the
	 * motor batteries.
	 */
	public iv_data iv_motors()
	{
		iv_data ret = new iv_data();
		ret.current = (double)mainClass.orden.leer_vector_corba(7);
		ret.volts = (double)mainClass.orden.leer_vector_corba(8);
		ret.current *= 5. / 1024.;
		ret.current /= 0.17647; // i = (u/Ganancia)/R = u/(17.647*0.01)
		ret.volts *= 5. / 1024.;
		ret.volts /= 0.2275; // u+ = u/(factor de reducción)
		ret.volts -= 0.14; // Error estático del operacional.
		return ret;
	}

	/**
	 * Method that returns the readings from the v/i sensor for the
	 * instrumentation batteries.
	 */
	public iv_data iv_instrumentation()
	{
		iv_data ret = new iv_data();
		ret.current = (double)mainClass.orden.leer_vector_corba(4);
		ret.volts = (double)mainClass.orden.leer_vector_corba(5);
		ret.current *= 5. / 1024.;
		ret.current *= 2; // i = (u/Ganancia)/R = u/(10*0.05)
		ret.volts *= 5. / 1024.;
		ret.volts /= 0.1998; // u+ = u/(factor de reducción)
		ret.current -= 0.9; // Error estático del diferencial.
		ret.volts -= 0.14; // Error estático del operacional.
		return ret;
	}

	/**
	 * Method that returns the readings from the vaio internal
	 * batteries.
	 * In this case the volts indicate the charge status,
	 * being 0 empty and 1 fully charged.
	 * current indicates the expected remaining time of
	 * current charge, in seconds.
	 */
	public iv_data iv_vaio()
	{
		iv_data ret = new iv_data();
		try {
			String line;
			String full = "";
			String[] cmd = {"acpi", "-b"};
			Process p = Runtime.getRuntime().exec(cmd);
			BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			while ((line = input.readLine()) != null) {
				full += line;
			}
			input.close();

			Scanner s = new Scanner(full);
			s.findInLine("\\s*Battery 0: [Dis]{0,3}[cC]harging, (\\d+)%, (\\d+):(\\d+):(\\d+) ");
			MatchResult result = s.match();
			ret.volts = Double.valueOf(result.group(1)).doubleValue() / 100;
			ret.current = Double.valueOf(result.group(2)).doubleValue() * 3600;
			ret.current += Double.valueOf(result.group(3)).doubleValue() * 60;
			ret.current += Double.valueOf(result.group(4)).doubleValue();
			s.close(); 
		}
		catch (Exception err) {
			err.printStackTrace();
		}

		return ret;
	}

	/**
	 * Method that returns the value of the Compass' readings.
	 * The compass must be connected to pin 25.
	 * The return value is between 0 and 2*pi.
	 */
	public double brujula()
	{
		double ret = (double)mainClass.orden.leer_vector_corba(16);
		ret *= (2. * 3.14159269);
		ret /= 360.;
		return ret;
	}

	/**
	 * Method that returns the value of the accelerometers' readings.
	 * X axis must be connected to pin 8 and Y axis to pin 11.
	 * Positive X is nose up.
	 * Positive Y is tilt right.
	 */
	public void acelerometro (org.omg.CORBA.DoubleHolder x, org.omg.CORBA.DoubleHolder y)
	{
		x.value = mainClass.orden.leer_vector_corba(9);
		x.value -= 563;
		x.value *= 5./(0.42*1024.);

		y.value = mainClass.orden.leer_vector_corba(12);
		y.value -= 544;
		y.value *= 5./(0.42*1024.);
	}

	/**
	 * Method that returns the value of the potentiometer's reading. Sensor must
	 * be connected to the analog pin 5 of the Arduino board.
	 * 
	 * @return Value of potentiomerer's reading using the formula:
	 */
	public double potenciometro() {
		return mainClass.orden.leer_vector_corba(6);
	}
}

// comentar hasta aqui!!!!

/**
 * 
 * @author Marcos Salom
 *         <p>
 *         This class is the CORBA servant, is the one that must be launched to
 *         execute the whole program.
 *         </p>
 *         Execution command is in the "doc" folder.
 */
public class mainClass {
	public static Command orden = new Command();
	static arduinoProcessing interfaz = new arduinoProcessing();
	public static LinkedList lista_de_ordenes = new LinkedList();

	static public void main(String args[]) {
		//NOGUI interfaz.main(new String[] { "arduinoProcessing" });

		try {
			// create and initialize the ORB
			ORB orb = ORB.init(args, null);

			// get reference to rootpoa & activate the POAManager
			POA rootpoa = POAHelper.narrow(orb
					.resolve_initial_references("RootPOA"));
			rootpoa.the_POAManager().activate();

			// create servant and register it with the ORB
			ArduinoImpl arduinoImpl = new ArduinoImpl();
			arduinoImpl.setORB(orb);

			// get object reference from the servant
			org.omg.CORBA.Object ref = rootpoa
				.servant_to_reference(arduinoImpl);
			Arduino href = ArduinoHelper.narrow(ref);

			// get the root naming context
			// Naming_Service invokes the name service
			
			String name_service = "Naming_Service";
			
			org.omg.CORBA.Object objRef = orb
				.resolve_initial_references(name_service);
			// Use NamingContextExt which is part of the Interoperable
			// Naming Service (INS) specification.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

			// bind the Object Reference in Naming
			String name = "Arduino";
			NameComponent path[] = ncRef.to_name(name);
			ncRef.rebind(path, href);

			String processID=ManagementFactory.getRuntimeMXBean().getName();
			String ArduinoPID = processID.substring(0,processID.indexOf("@"));
			orden.writeProcessID(ArduinoPID);
			//System.out.println("Arduino PID: "+ArduinoPID);
			/*System.out.println("Arduino PID: "+Double.parseDouble(ArduinoPID));
			  System.out.println("Arduino PID: "+Double.toString(Double.parseDouble(ArduinoPID)));
			  System.out.println("Arduino PID: "+Double.toString(Double.parseDouble(ArduinoPID)).concat("."));
			  System.out.println("Arduino PID: "+(Double.toString(Double.parseDouble(ArduinoPID)).concat(".")).substring(0, (Double.toString(Double.parseDouble(ArduinoPID)).concat(".")).indexOf(".")));*/
			System.out.println("ArduinoServer ready and waiting ...");

			// wait for invocations from clients
			orb.run();
		}

		catch (Exception e) {

			System.err.println("ERROR: " + e);
			e.printStackTrace(System.out);
		}

		System.out.println("ArduinoServer Exiting ...");
		System.exit(0); // Ensure the process terminates in case the serial port event thread is still running.
	}

}
