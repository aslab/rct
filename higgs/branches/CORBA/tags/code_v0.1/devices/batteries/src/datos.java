import java.util.Date;

public class datos {

	/**
	 * Flag to begin counting time and calculating the current's average
	 */
	short flag = 0;
	/**
	 * Stores the value of the current's average
	 */
	double I_promedio = 0;
	/**
	 * Stores the value of the total measurement duration
	 */
	double t_total = 0;
	/**
	 * Flag to exit the program
	 */
	int salida = 0;
	/**
	 * Stores the initial time
	 */
	double t_init = 0;
	/**
	 * Stores the final time
	 */
	double t_end = 0;
	Date currentDate = new Date();
	double contador = 1;

	/**
	 * Reads the current's average value
	 * @return
	 */
	public synchronized double leer_I_promedio() {
		return this.I_promedio;
	}

	/**
	 * Reads the total measurement's duration
	 * @return Total measurement's duration
	 */
	public synchronized double leer_t_total() {
		return this.t_total;
	}

	/**
	 * Sets the value of the current's average
	 * @param I: Measured Current
	 */
	public synchronized void escribir_I_promedio(double I) {
		this.I_promedio = I;
	}

	/**
	 * Sets the value of the total measurement's duration 
	 * @param t: Measurement duration
	 */
	public synchronized void escribir_t_total(double t) {
		this.t_total = t;
	}

	/**
	 * Reads the flag's value
	 * @return Flag value
	 */
	public synchronized short leer_flag() {
		return this.flag;
	}

	/**
	 * Sets the flag's value
	 * @param flag: new flag value
	 */
	public synchronized void escribir_flag(short flag) {
		this.flag = flag;
	}

	public synchronized void salida() {
		this.salida = 1;
	}

	public synchronized int valor_salida() {
		return this.salida;
	}

	public synchronized void timeStart() {
		this.t_init = currentDate.getTime();
		this.flag = 1;
	}

	public synchronized void timeStop() {
		this.t_end = currentDate.getTime();
		this.t_total = (this.t_end - this.t_init);
		this.flag = 0;
		this.contador = 1;
	}

	/**
	 * Returns the counter's value
	 * @return Counter's value
	 */
	public synchronized double getContador() {
		return this.contador;
	}
	
	/**
	 * Resets the counter
	 */
	public synchronized void resetContador() {
		this.contador = 1;
	}
	/**
	 * Increases the counter
	 */
	public synchronized void incrementarContador() {
		this.contador++;
	}

}
