import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;

import higgs.*;

/**
 * 
 * @author Marcos Salom
 * <p>This class calculates the current's average and the total calculation time
 *
 */
public class promedio extends Thread {
	Arduino ArduinoImpl;
	datos datos;

	double contador = 1;

	promedio(Arduino ArduinoImpl, datos datos) {
		this.ArduinoImpl = ArduinoImpl;
		this.datos = datos;
	}

	public void run() {
		while (datos.valor_salida() == 0) {
			if (datos.leer_flag() == 1) {
				System.out.println("flag a 1!!!!!");
				datos.escribir_I_promedio((datos.leer_I_promedio()
						* (datos.getContador() - 1) + ArduinoImpl.iv_instrumentation().current)
						/ datos.getContador());
				System.out.println("Valor pin 2 "
						+ ArduinoImpl.iv_instrumentation().current
						+ ", valor de i_prom: " + datos.leer_I_promedio()
						+ ", contador:" + datos.getContador());

				try {
					Thread.sleep(1); // 1000 millisecs
				}
				catch (InterruptedException ex) {
				}
				datos.incrementarContador();
			}

		}
	}

}
