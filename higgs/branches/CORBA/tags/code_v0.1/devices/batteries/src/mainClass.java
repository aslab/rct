import higgs.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.CORBA.ORB;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;



class CurrentMonitorImpl extends CurrentMonitorPOA {

	private ORB orb;

	/**
	 * Finishes execution
	 */
	public void salida() {
		mainClass.datos.salida();
	}

	public void setORB(ORB orb_val) {
		orb = orb_val;
	}
	
	/**
	 * If flag=1, starts the monitoring
	 * If flag=0, ends the monitoring
	 */
	public void flag(short flag) {
		// mainClass.datos.escribir_flag(flag);
		if (flag == 1)
			mainClass.datos.timeStart();
		else
			mainClass.datos.timeStop();
	}
	/**
	 * Returns the value of the current's average
	 * @return Current's average
	 */
	public double iPromedio() {
		return mainClass.datos.leer_I_promedio();
	}

	/**
	 * Returns the value of the total measurement's duration
	 * @return Current's average
	 */
	public double tiempo() {
		return mainClass.datos.leer_t_total();
	}
}

/**
 * 
 * @author Marcos Salom
 *         <p>
 *         CORBA server that implements the interface declared in the
 *         <i>BatteryModel.idl</i> file
 *         </p>
 */
class BatteryModelImpl extends BatteryModelPOA {

	private ORB orb;

	public void setORB(ORB orb_val) {
		orb = orb_val;
	}

	/**
	 * Returns 1 if the batteries are discharged
	 * 
	 * @return 1 if the batteries are discharged
	 */
	public boolean error() {
		return (baterias.error_consumo == 1);
	}

	/**
	   * 
	   */
	public void reiniciarVector() {
		baterias.reiniciar_vector();
		baterias.indice = 0;
		baterias.indice2 = 0;
	}

	public short errorTarea() {
		return baterias.error_tarea;
	}

	public double tiempoRestante() {
		return baterias.tiempo_restante();
	}

	public double tiempoRestanteMision() {
		return baterias.tiempo_restante_tarea();
	}

	public double tiempoUltimo() {
		return baterias.t;
	}

	public double ultimaIntensidad() {
		return baterias.I_aux;
	}

	public void agregarElemento(double dato) {
		baterias.vector_consumo[baterias.indice] = dato;
		baterias.indice++;
		if (dato == -1)
			baterias.indice = baterias.indice - 1;
	}

	public void agregarTarea(double intensidad, double duracion) {
		baterias.vector_consumo[baterias.indice2] = intensidad;
		baterias.indice2++;
		baterias.vector_consumo[baterias.indice2] = duracion;
		baterias.indice2++;
		if (intensidad == -1)
			baterias.indice2 = baterias.indice2 - 2;
	}

	public void tensionIntensidad(double tension, double intensidad) {
		baterias.U = tension;
		baterias.I = intensidad;
	}
}

public class mainClass {
	static BatteryModel BatteryModelImpl;
	static Arduino ArduinoImpl;
	// public static int salida=0;

	public transient static org.omg.CORBA.Object obj;

	public static datos datos = new datos();

	public static void main(String args[]) {
		baterias baterias = new baterias();

		try {
			// create and initialize the ORB
			ORB orb = ORB.init(args, null);

			// get reference to rootpoa & activate the POAManager
			POA rootpoa = POAHelper.narrow(orb
					.resolve_initial_references("RootPOA"));
			rootpoa.the_POAManager().activate();

			// get the root naming context
			// NameService invokes the name service
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			// Use NamingContextExt which is part of the Interoperable
			// Naming Service (INS) specification.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

			// BATTERY_MODEL
			// create servant and register it with the ORB
			BatteryModelImpl BatteryModelImpl = new BatteryModelImpl();
			BatteryModelImpl.setORB(orb);

			// get object reference from the servant
			org.omg.CORBA.Object ref_bat = rootpoa
					.servant_to_reference(BatteryModelImpl);
			BatteryModel href_bat = BatteryModelHelper.narrow(ref_bat);

			// bind the Object Reference in Naming
			String name = "BatteryModel";
			NameComponent path[] = ncRef.to_name(name);
			ncRef.rebind(path, href_bat);

			System.out.println("BatteryModel Server ready and waiting ...");

			// Get ARDUINO
			// Resolve the object reference in naming
			name = "Arduino";
			path = ncRef.to_name(name);
			ArduinoImpl = ArduinoHelper.narrow(ncRef.resolve(path));

			// CURRENT_MONITOR
			CurrentMonitorImpl CurrentMonitorImpl = new CurrentMonitorImpl();
			
			// orb.connect(arduinoImpl);
			CurrentMonitorImpl.setORB(orb);

			// get object reference from the servant
			org.omg.CORBA.Object ref_cur = rootpoa.servant_to_reference(CurrentMonitorImpl);
			CurrentMonitor href_cur = CurrentMonitorHelper.narrow(ref_cur);

			// bind the Object Reference in Naming
			name = "CurrentAverage";
			path = ncRef.to_name(name);
			ncRef.rebind(path, href_cur);

			System.out.println("CurrentMonitor Server ready and waiting ...");


			Thread promedio = new promedio(ArduinoImpl, datos);
			promedio.start();

			// wait for invocations from clients
			orb.run();
		}

		catch (Exception e) {
			System.err.println("ERROR: " + e);
			e.printStackTrace(System.out);
		}
	}

}
