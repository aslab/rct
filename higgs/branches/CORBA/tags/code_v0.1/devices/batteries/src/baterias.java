/**
 * @author Marcos Salom
 * 
 */
public class baterias {

	// relaci�n tiempo - intensidad para U= 9.6 V
	//
	// log(t)=2.545154-1.213119*log(i)
	//
	// relaci�n tiempo - intensidad para U= 10.5 V
	//
	// log(t)=2,544446-1,1728384*log(i)
	//
	// relaci�n tensi�n - intensidad (entre 1.19 A y 0.63 A)
	//
	// 1.8666*U = 20.23 - I
	//
	// relaci�n tensi�n - tiempo (entre 1.19 A y 0.63 A, entre 5 y 10 horas)
	//
	// U - 10.2 = 0.991(log(t) - 2.4771)
	//
	// relaci�n tensi�n - intensidad (entre 1.75 A y 1.19 A)
	//
	// 0.93358*U = 10.710239 - I
	//
	// relaci�n tensi�n - tiempo (entre 1.75 A y 1.19 A, entre 3 y 5 horas)
	//
	// U - 9.6 = 2.7014*(log(t) - 2.255)
	//
	// curva frontera entre zonas...
	// 
	// U = 11.05499+0.82796*log(t)
	//
	// estimaci�n de pendiente en aproximaci�n zona lineal respecto al tiempo
	// 
	// pendiente = -0.007907*(I)^1.380974
	//
	// estimaci�n de pendiente en aproximaci�n zona lineal respecto al logaritmo
	// del tiempo
	//
	// pendiente = -0.21212285 - 0.159355*log(I)
	//
	// relaci�n tensi�n - intensidad para t=1 min
	//
	// V=12.74351-0.7531688*log(I)
	/**
	 * Calculates the time in the estimated current curve that corresponds to
	 * the fronteer line using Newton-Raphson.
	 * 
	 * @param m1
	 *            : slope of the decimal zone line, Uf: final discharge voltage,
	 *            tf: final discharge time
	 * @return Time of the estimated current curve corresponding to the fronteer
	 *         line
	 */
	public static double t_frontera(double m1, double Uf, double tf) {
		// esta devuelve el tiempo de la frontera
		double error = 1;
		double valor_mas_1 = 1;
		double valor = 1;
		double a = 11.05499;
		double b = 0.82796;
		int contador = 1000;

		while (error > 0.001) {
			valor_mas_1 = valor
					- (b * Math.log10(valor) - m1 * valor - (Uf - a - m1 * tf))
					/ (b / (Math.log(10) * valor) - m1);
			// System.out.println("v+1: "+ valor_mas_1);
			error = Math.abs((valor_mas_1 - valor) / valor_mas_1 * 100);
			valor = valor_mas_1;
			contador--;
			// System.out.println("entre, "+ contador);
			if (contador == 1) {
				System.out.println("Muchas iteraciones");
				return valor;
			}
		}

		return valor;
	}

	/**
	 * Calculates the voltage in the estimated current curve that corresponds to
	 * the fronteer line.
	 * 
	 * @param Fronteer
	 *            time
	 * @return Time of the estimated current curve corresponding to the fronteer
	 *         line
	 */
	public static double U_frontera(double tfront) {
		return 11.05499 + 0.82796 * Math.log10(tfront);
	}

	/**
	 * Calculates the discharge voltage
	 * 
	 * @param Current
	 *            measured
	 * @return discharge voltage
	 */
	public static double Uf(double I) {
		if (I >= 1.75) {
			return 9.6;
		} else if (I >= 1.19) {
			return (10.710239 - I) / 0.93358;
		} else if (I >= 0.63) {
			return (20.23 - I) / 1.8666;
		} else
			return 10.5;
	}

	/**
	 * Calculates the discharge time
	 * 
	 * @param Current
	 *            measured, discharge voltage
	 * @return discharge time
	 */
	public static double tf(double I, double Uf) {
		if (I >= 1.75) {
			// log(t)=2.545154-1.213119*log(i)
			return Math.pow(10, 2.545154 - 1.213119 * Math.log10(I));
		} else if (I >= 1.19) {
			// U - 9.6 = 2.7014*(log(t) - 2.255)
			// (Uf-9.6)/2.7014+2.255=log(t)
			return Math.pow(10, (Uf - 9.6) / 2.7014 + 2.255);
		} else if (I >= 0.63) {
			// U - 10.2 = 0.991(log(t) - 2.4771)
			// (Uf-10.2)/0.991+2.4771=log(t)
			return Math.pow(10, (Uf - 10.2) / 0.991 + 2.4771);
		} else {
			// log(I)=1.76262-0.7142128*log(t)
			// (1.76262-Math.log10(I))/0.7142128=Math.log(t)
			// log(I)=1,76262-0,7142128*log(t)
			// log(t)=2,544446-1,1728384*log(i)
			return Math.pow(10, (2.544446 - 1.1728384 * Math.log10(I)));
		}
	}

	/**
	 * Method that makes a linear interpolation/extrapolation between two
	 * points.
	 * 
	 * @param x1
	 *            ,x2,x,y1,y2
	 * @return t
	 */
	public static double ixpolar(double v1, double v2, double v, double t1,
			double t2) {
		// tengo los valores de v1, v2 y t1, t2. quiero el valor de t para un
		// determiado v.
		double t = ((t2 - t1) / (v2 - v1)) * (v - v1) + t1;
		return t;
	}

	/**
	 * Method that calculates the slope of the non logarithminc zone in the
	 * estimated discharge curve
	 * 
	 * @param Current
	 *            measured
	 * @return slope for non logarithmic zone
	 */
	public static double pendiente_no_log(double I) {
		// 0,35 A -0.002099738
		// 0,63 A -0.0038734
		// 1,19 A -0.0091669
		// 1,75 A -0.0162945
		// 4,2 A -0.062529
		// 7 A -0.1206
		// 14 A -0.30977

		// aumento un 5% (en valor absoluto) la pendiente para que el resultado
		// de un numero claramente
		// menor de tiempo al que realmente se tiene, para tener un peor caso

		if (I <= 0.63) {
			return 1.05 * ixpolar(0.35, 0.63, I, -0.002099738, -0.0038734);
		} else if (I <= 1.19) {
			return 1.05 * ixpolar(1.19, 0.63, I, -0.0091669, -0.0038734);
		} else if (I <= 1.75) {
			return 1.05 * ixpolar(1.19, 1.75, I, -0.0091669, -0.0162945);
		} else if (I <= 4.2) {
			return 1.05 * ixpolar(4.2, 1.75, I, -0.062529, -0.0162945);
		} else if (I <= 7) {
			return 1.05 * ixpolar(4.2, 7, I, -0.062529, -0.1206);
		} else
			return 1.05 * ixpolar(14, 7, I, -0.30977, -0.1206);
	}

	/**
	 * Method that calculates the slope of the logarithminc zone in the
	 * estimated discharge curve
	 * 
	 * @param Current
	 *            measured
	 * @return slope for logarithmic zone
	 */
	public static double pendiente_log(double I) {
		return -0.21212285 - 0.159355 * Math.log10(I);
	}

	/**
	 * Method that resets the tasks vector
	 */
	public static void reiniciar_vector() {
		vector_consumo[0] = -1;
		for (int i = 1; i < 99; i++) {
			vector_consumo[i] = -1;
		}
	}

	/**
	 * Calculates the time that the batteries have given current and the actual
	 * state.
	 * 
	 * @param U
	 *            : voltage measured; tfront Ufront: fronteer time and voltage;
	 *            Uf tf: discharte voltage and time; m1: logarithmic slope; I:
	 *            current measured.
	 * @return Actual time
	 */
	public static double tiempo_actual(double U, double tfront, double Ufront,
			double Uf, double tf, double m1, double I) {
		double log_tfront = 0;
		double log_t_actual = 0;
		double m2 = 0;
		if (U <= Ufront) {
			return (U - Uf) / m1 + tf;
		} else {
			log_tfront = Math.log10(tfront);
			m2 = pendiente_log(I);
			log_t_actual = (U - Ufront) / m2 + log_tfront;
			return Math.pow(10, log_t_actual);
		}
	}

	/**
	 * Calculates the remaining battery's life time at the current consumption
	 * state
	 * 
	 * @return Remaining battery's life time
	 */
	public static double tiempo_restante() {
		int i = 0;
		while (vector_consumo[i] != -1) {
			System.out.println("elemento " + i + ", valor: "
					+ vector_consumo[i]);
			i++;
		}

		contador = 0;
		m1 = pendiente_no_log(I);
		Uf = Uf(I);
		tf = tf(I, Uf);
		tfront = t_frontera(m1, Uf, tf);
		Ufront = U_frontera(tfront);
		tiempo_actual = tiempo_actual(U, tfront, Ufront, Uf, tf, m1, I);// esta

		// si el tiempo actual es menor que uno, entonces estaremos en la zona
		// no calculable

		if (tiempo_actual < 1)
			return -1;

		// ahora lo que toca es ver cuanto tiempo va a estarse bajo el presente
		// consumo
		// y determinar si habra carga para terminar la tarea

		// leer tiempo restante de tarea
		// comparar si puede terminarse y ver el tiempo final de la tarea (no de
		// duracion de la bateria a ese regimen de consumo...)
		// calcular la carga extraida de la bateria
		// ver el nuevo regimen de consumo, hallar el nuevo tiempo inicial
		// sumar la duracion y calcular carga final
		// volver... hasta q se terminen las tareas o hasta q se agote la
		// bateria
		t = tiempo_actual;

		return (tf - tiempo_actual);

	} // tiempo_restante

	/**
	 * Calculates the remaining battery's life time for a future task plannig
	 * 
	 * @return Remaining battery's life time for a future task plannig
	 */
	public static double tiempo_restante_tarea() {
		int i = 0;
		while (vector_consumo[i] != -1) {
			System.out.println("elemento " + i + ", valor: "
					+ vector_consumo[i]);
			i++;
		}

		double t_restante = 0;
		contador = 0;
		m1 = pendiente_no_log(I);
		Uf = Uf(I);
		tf = tf(I, Uf);
		tfront = t_frontera(m1, Uf, tf);
		Ufront = U_frontera(tfront);
		tiempo_actual = tiempo_actual(U, tfront, Ufront, Uf, tf, m1, I);// esta

		// si el tiempo actual es menor que uno, entonces estaremos en la zona
		// no calculable

		if (tiempo_actual < 1)
			return -1;

		// ahora lo que toca es ver cuanto tiempo va a estarse bajo el presente
		// consumo
		// y determinar si habra carga para terminar la tarea

		// leer tiempo restante de tarea
		// comparar si puede terminarse y ver el tiempo final de la tarea (no de
		// duracion de la bateria a ese regimen de consumo...)
		// calcular la carga extraida de la bateria
		// ver el nuevo regimen de consumo, hallar el nuevo tiempo inicial
		// sumar la duracion y calcular carga final
		// volver... hasta q se terminen las tareas o hasta q se agote la
		// bateria
		t = tiempo_actual;
		I_aux = I;
		if (vector_consumo[0] == -1) {
			return (tf - tiempo_actual);
		}
		Q = I_aux * t;

		while (vector_consumo[contador] != -1) {
			I_aux = vector_consumo[contador];
			t = Q / I_aux;
			contador++;

			t = t + vector_consumo[contador];
			System.out.println("Intensidad: " + I_aux + ",t inicial: " + t
					+ ", t final de actividad:" + t + ", t final:"
					+ tf(I_aux, Uf(I_aux)) + ", contador: " + contador);
			if ((t > tf(I_aux, Uf(I_aux)) || (U < Uf(I)))) {
				error_consumo = 1;

				break;
			}
			Q = t * I_aux;
			contador++;
		}
		if (error_consumo == 0) {
			System.out
					.println("El tiempo en el que estaremos al final del planning es: "
							+ t);
			System.out.println("El tiempo final para el ultimo contumo es: "
					+ tf(I_aux, Uf(I_aux)));
			t_restante = tf(I_aux, Uf(I_aux)) - t;
			return t_restante;
		} else {
			System.out.println("Se agotan las baterías durante la misión "
					+ (contador) / 2);
			error_tarea = (short) ((contador) / 2);
			return 0;
		}
	}// t_restante_tarea

	/**
	 * Contains the values of currents and durations for the future tasks'
	 * estimation
	 */
	public static double vector_consumo[] = new double[100];
	{
		vector_consumo[0] = -1;
	}
	/**
	 * index to move across the <i>vector_consumo</i> array to be filled by the
	 * <i>agregarElemento</i> method
	 */
	public static int indice = 0;
	/**
	 * index to move across the <i>vector_consumo</i> array to be filled by the
	 * <i>agregarTarea</i> method
	 */
	public static int indice2 = 0;
	/**
	 * Measured current
	 */
	public static double I = 0;
	/**
	 * Measured voltage
	 */
	public static double U = 0;
	/**
	 * Takes value=1 when the batteries are discharged
	 */
	public static short error_consumo;
	/**
	 * Takes the value of the task's ID when the batteries are discharged
	 */
	public static short error_tarea;
	/**
	 * Discharge voltage
	 */
	public static double Uf = 0; // necesito esta
	/**
	 * Discharge time
	 */
	public static double tf = 0; // necesito esta
	/**
	 * Fronteer time
	 */
	public static double tfront = 0;
	/**
	 * Counter to move across the <i>vector_consumo</i> array in the task
	 * estimation
	 */
	public static int contador = 0;
	/**
	 * Estimated charge
	 */
	public static double Q = 0;
	/**
	 * Time
	 */
	public static double t = 0;
	/**
	 * Auxiliar current
	 */
	public static double I_aux = 0;
	/**
	 * Fronteer voltage
	 */
	public static double Ufront = 0;
	/**
	 * Actual time
	 */
	public static double tiempo_actual = 0;
	/**
	 * Remaining battery life time
	 */
	public static double tiempo_restante = 0;
	/**
	 * Variable that stores the non-logarithmic zone slope the the estimated
	 * current curve
	 */
	public static double m1 = 0;

}
