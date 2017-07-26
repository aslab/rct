/**
 * 
 * @author Marcos Salom
 * @author Francisco Jesús Arjonilla
 *         <p>
 *         This class contains the data that will be exchanged between the class
 *         that communicates with the Arduino board and the CORBA server
 *         </p>
 */

public class Command {

	/**
	 * Stores the value of the command to be sent to the Arduino board
	 */
	public int orden = 0;

	/**
	 * Flag that indicates if the command was sent to the board so the parameter
	 * can be sent
	 */
	public boolean orden_enviada = false;

	/**
	 * Stores the setpoint for the PID
	 */
	public int referencia = 200;

	/**
	 * Stores the value of the pin to me switch ON/OFF
	 */
	public int pin;

	/**
	 * Stores the new value of the setpoint transformed by the A-D
	 */
	public float valor_inclin;

	/**
	 * Stores the lowest value of the potentiometer in the startup method
	 */
	public int tope_inferior;

	/**
	 * Stores the Arduino's information received
	 */
	public float vector_corba[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	/**
	 * Stores the process ID
	 */
	public double processID=0;

	/**
	 * Writes the value given by valor in the array vector_corba ant the indice
	 * position
	 * 
	 * @param writes
	 *            a value determined by "valor" at the "indice" position of the
	 *            vector_corba
	 */
	public synchronized void escribir_vector_corba(int indice, float valor) {

		this.vector_corba[indice] = valor;
	}

	/**
	 * Reads and returns the value at the indice position in the array
	 * vector_corba
	 * 
	 * @param Index
	 *            of the vector corba to be read
	 * @return Value stored at the "indice" position
	 */
	public synchronized double leer_vector_corba(int indice) {
		return this.vector_corba[indice];
	}

	/**
	 * Returns value of variable tipo_orden
	 * 
	 * @return Type of command to be sent to the Arduino board
	 */
	public synchronized int tipo_orden() {
		return orden;

	}

	/**
	 * Returns value of variable orden_enviada
	 * 
	 * @return If the order was sent so that the parameter can be sent
	 */
	public synchronized boolean orden_enviada() {
		return orden_enviada;
	}

	/**
	 * Returns the parameter to be sent
	 * 
	 * @return Parameter of the command
	 */
	public synchronized int parametro() { // esta devuelve el valor de la nueva
											// referencia para el PID - el
											// parametro de la nueva orden.
		switch (orden) {
		case 1:
		case 2:
		case 3:
			return referencia;
		case 6:
		case 7:
			return pin;
		default:
			return 0;
		}// switch
	}

	/**
	 * Sets the value of orden to zero
	 */
	public synchronized void orden_cero() {

		orden = 0;
		//System.out.println("orden cero!!!");
	}


	/**
	 * Changes the value of the variable orden
	 * 
	 * @param Sets
	 *            the value of the command and parameter to be sent to the
	 *            Arduino board
	 */
	public synchronized void cambiar_orden(int orden_nueva, int parametro) {

		orden = orden_nueva;

		switch (orden_nueva) {

		case 1:
		case 2:
		case 3:
			referencia = parametro;
			break;
		case 6:
			pin = parametro;
			break; // esta orden es para poner a '1' un pin digital
		case 7:
			pin = parametro;
			break; // esta orden es para poner a '0' un pin digital
		default:
			;
		}
	}

	public synchronized void escribir_val_inc(float valor) {

		valor_inclin = valor;
	}

	public synchronized float leer_val_incl() {
		return valor_inclin;
	}

	/**
	 * reads the value of lowest potentiometer reading at the pontentiometer's
	 * start up
	 * 
	 * @return Value of lowest potentiometer reading at the pontentiometer's
	 *         start up
	 */
	public synchronized int leer_tope_inferior() {

		return tope_inferior;
	}

	public synchronized void writeProcessID(String pid){
		this.processID=Double.parseDouble(pid);
	}
	
	public synchronized double getProcessID(){
		return this.processID;
	}
	
	
	/**
	 * Sets the value of lowest potentiometer reading at the pontentiometer's
	 * start up
	 * 
	 * @param New
	 *            value for tope_inferior
	 */
	public synchronized void escribir_tope_inferior(int tope_inferior) {

		this.tope_inferior = tope_inferior;
	}

	/**
	 * Changes the value of the PID's setpoint using a A-D converter
	 * 
	 * @param New
	 *            angle of the PID setpoint
	 */
	public synchronized void cambiar_inclinacion(float angulo) {

		// inicializa
		int angulo_trans = 0;// este es el algulo transformado al valor del
								// inclinometro

		// angulo_trans=(int)(5.4338*(angulo+90)-80.9913);
		angulo_trans = (int) ((angulo + 13.6) / 0.9346 + leer_tope_inferior());

		//System.out.println("Grados: " + angulo + ", transformado: "
				//+ angulo_trans);
		if (angulo_trans > 510) {
			cambiar_orden(3, angulo_trans - 510);
		} else {
			if (angulo_trans > 255) {
				cambiar_orden(2, angulo_trans - 255);
			} else {
				cambiar_orden(1, angulo_trans);
			}
		}
	}
}
