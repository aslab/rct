//import processing.core.PApplet;
//import processing.core.PFont;
import processing.serial.*;
import gnu.io.*;

import java.lang.reflect.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * 
 * @author Marcos Salom
 *         <p>
 *         This class communicates with the Arduino board
 *         </p>
 * @author Francisco Jesús Arjonilla
 *         <p>
 *	   Various modifications and enhancements.
 *         </p>
 */
public class arduinoProcessing implements SerialPortEventListener {
// NOGUI public class arduinoProcessing extends PApplet {

	// NOGUI PFont myFont;
	// Variables para las lecturas de los sensores anal�gicos

	/**
	 * Stores whether the servo is enabled or not
	 */
	static float servo; // dice si el servo esta activado o no

	// ********************************* ANALOG PINS
	/**
	 * Stores value of the analog pins 0 to 11
	 */
	static float[] an_pin = new float[12];

	// ********************************* DIGITAL PINS
	/**
	 * Stores value of the digital pin 22
	 */
	static int dig_pin22;

	/**
	 * Stores value of the digital pin 23
	 */
	static int dig_pin23;

	/**
	 * Stores value of the digital pin 24
	 */
	static int dig_pin24;

	/**
	 * Stores value of the digital pin 25
	 */
	static int dig_pin25;

	/**
	 * Stores value of the digital pin 26
	 */
	static int dig_pin26;

	/**
	 * Stores value of the digital pin 27
	 */
	static int dig_pin27;

	// ********************************* MISC VARIABLES
	/**
	 * Stores the value of the lowest potentiometer position at the startup
	 * method
	 */
	static int tope_inf;

	/**
	 * Tells whether the startup method was successfully completed or not
	 */
	static int tope_sup;

	/**
	 * Stores the PID setpoint returned by the Arduino board
	 */
	static float referencia; // valor que nos devuelve arduino

	// ********************************* PID PARAMETERS

	/**
	 * Stores the value of the K parameter of the PID
	 */
	static int PID_K;

	/**
	 * Stores the value of the Ti parameter of the PID
	 */
	static int PID_Ti;

	/**
	 * Stores the value of the Td parameter of the PID
	 */
	static int PID_Td;

	/**
	 * Stores the value of the Beta parameter of the PID
	 */
	static int PID_Beta;

	/**
	 * Stores the value of the Tr parameter of the PID
	 */
	static int PID_Tr;

	/**
	 * Stores the value of the N parameter of the PID
	 */
	static int PID_N;

	/**
	 * Stores the value of the h parameter of the PID
	 */
	static int PID_h;

	/**
	 * Set the numbre of batteires used
	 */
	static int n_bat;

	int lf = 10; // ASCII linefeed

	boolean received;
	Command orden = mainClass.orden;

	OutputStream serialOut;
	InputStream serialIn;
	// ---------------------------------------------------------

	/**
	 * Sets up the Processing applet and initializes the serial communication
	 */
	public arduinoProcessing() {
	// NOGUI public void setup() {

		// NOGUI size(200, 200);
		// NOGUI myFont = createFont("Arial", 18);
		// NOGUI textFont(myFont, 10);
		// NOGUI println(Serial.list());

		try{
			System.setProperty("gnu.io.rxtx.SerialPorts", "/etc/higgs/devices/arduino_dev");
			CommPortIdentifier portIdentifier =
				CommPortIdentifier.getPortIdentifier("/etc/higgs/devices/arduino_dev");
			if ( portIdentifier.isCurrentlyOwned() )
			{
				System.out.println("Error: Port is currently in use");
			}
			else
			{
				CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);

				if ( commPort instanceof SerialPort )
				{
					SerialPort serialPort = (SerialPort) commPort;
					serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,
							SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
					serialIn = serialPort.getInputStream();
					serialOut = serialPort.getOutputStream();

					serialPort.addEventListener(this);
					serialPort.notifyOnDataAvailable(true);

				}
				else
				{
					System.out.println("Error: Only serial ports are handled by this example.");
				}
			}     

			received = false;
		}
		catch( Exception e )
		{
			System.err.println("ERROR: " + e);
			e.printStackTrace(System.out);
		}
	}

	/**
	 * <p>
	 * Executes when the buffer contains a certain ASCII character. Handles the
	 * communication with the Arduino board. Stores the information in command's
	 * class array vector_corba.
	 * </p>
	 */
	static int counter = 0;
	public void serialEvent(SerialPortEvent arg0) {
		try
		{
			//System.out.println("Serial event #" + counter++ );
			String myString = null;
			if (orden.tipo_orden() == 0) {
				serialOut.write(0);
				myString = "";
				byte b = 0;
				while ( b != 124) // the ascii value of the "|" character
				{
					myString += ( char ) b; ;
					b = (byte)serialIn.read();
				} if (myString != null) {
					myString = myString.trim(); // remove whitespace around our
					// values
					String myStrings[] = myString.split(",");
					int inputs[] = new int[myStrings.length];
					if (myStrings.length == 0)
						return;
					for (int i = 0; i < myStrings.length; i++)
					{
						try{
						inputs[i] = Integer.parseInt(myStrings[i]);
						}catch(Exception e)
						{inputs[i] = 0;}
					}
					// now assign your values in processing

					if ((inputs[0] != 2) && (Array.getLength(inputs) > 28)) {

						servo = inputs[0];

						for (int i = 0; i < 12; i++)
							an_pin[i] = inputs[i + 1];

						dig_pin22 = inputs[13];
						dig_pin23 = inputs[14];
						dig_pin24 = inputs[15];
						dig_pin25 = inputs[16];
						dig_pin26 = inputs[17];
						dig_pin27 = inputs[18];

						referencia = inputs[19];

						tope_inf = inputs[20];
						orden.escribir_tope_inferior(tope_inf);
						tope_sup = inputs[21];

						PID_K = inputs[22];
						PID_Ti = inputs[23];
						PID_Td = inputs[24];
						PID_Beta = inputs[25];
						PID_Tr = inputs[26];
						PID_N = inputs[27];
						PID_h = inputs[28];

						for (int j = 0; j < 29; j++) {
							orden.escribir_vector_corba(j, (float) (inputs[j]));
						}

					}
					if (mainClass.lista_de_ordenes.size() != 0)
					{
						orden o = (orden)mainClass.lista_de_ordenes.removeFirst();
						orden.cambiar_orden(o.orden, o.pin);
					}


				}
			} else {
				if (orden.orden_enviada() == false) {
					serialOut.write(orden.tipo_orden());
					//System.out.println("envio orden" + orden.tipo_orden());
					myString = "";
					byte b = 0;
					while ( b != 124) // the ascii value of the "|" character
					{
						myString += (char)b;
						b = (byte)serialIn.read();
					} if (myString != null) {
						myString = myString.trim(); // remove whitespace around our
						// values
						// int inputs[] = Integer.parseInt(myString.split(","));
						// now assign your values in processing
						// val = inputs[0];
						// retorno = inputs[1];
						// servo = inputs[2];

						switch (orden.tipo_orden()) {

							case 1:
							case 2:
							case 3:
								orden.orden_enviada = true;
								break;
							case 4:
								orden.orden_cero();
								break; // activa o desactiva el servo
							case 5:
								orden.orden_cero();
								break; // puesta a cero del laser y el pid
							case 6:
							case 7:
								orden.orden_enviada = true;
								break;
								// case 1:orden.c_orden_enviada(true);break;
								// case 2:orden.orden_cero();break;
							default:
								;
						}
					}
				} else {
					serialOut.write(orden.parametro());
					//System.out.println("envio parametro " + orden.parametro());
					myString = "";
					byte b = 0;
					while ( b != 124) // the ascii value of the "|" character
					{
						myString += (char)b;
						b = (byte)serialIn.read();
					} if (myString != null) {
						myString = myString.trim(); // remove whitespace around our
						// values
						// int inputs[] = Integer.parseInt(myString.split(","));
						// now assign your values in processing
						// val = inputs[0];
						// retorno = inputs[1];
						// servo = inputs[2];

					}
					orden.orden = 0;
					orden.orden_enviada = false;
				}

			}
		}
		catch( Exception e )
		{
			System.err.println("ERROR: " + e);
			e.printStackTrace(System.out);
		}

	}

	/**
	 * Refreshes the applet and tells what is displayed on the screen.
	 */
	/* // NOGUI
	   public void draw() {
	   background(0);
	   fill(255);
	   textFont(myFont, 10);

	   text("Ref. usuario:" + orden.referencia, 5, 12);
	   text("Ref. (retorno): " + referencia, 100, 12);
	// text("Ref. (retorno, en grados): " + redondear(grados(referencia)),
	// 5,36);
	// if((redondear(grados(an_pin[0]))>140))
	// text("Grados: Fuera del rango lineal", 5,72);
	// else {
	// if((redondear(grados(an_pin[0]))<40))
	// text("Grados: Fuera del rango lineal", 5,72);
	// else text("Grados: " + redondear(90-grados(an_pin[0])), 5,72);}

	text("Pines analogiocos: " + (servo == 1), 5, 24);
	text("U Instrum: " + redondear(an_pin[0] * 11.38 / 531), 5, 36);
	text("I Instrum: " + redondear(an_pin[1] / 100), 100, 36);

	text("Valor Pin2: " + an_pin[2], 5, 48);
	text("Valor pin3: " + an_pin[3], 100, 48);
	text("Valor pin4: " + an_pin[4], 5, 60);
	text("Valor Pin5: " + an_pin[5], 100, 60);// 5
	text("Valor Pin6: " + an_pin[6], 5, 72);// 6
	text("Valor Pin7: " + an_pin[7], 100, 72);
	text("Valor Pin8: " + an_pin[8], 5, 84);
	text("Valor Pin9: " + an_pin[9], 100, 84);
	text("Valor Pin10: " + an_pin[10], 5, 96);
	text("Valor Pin11: " + an_pin[11], 100, 96);
	// text("Angulo del potenciometro: " +
	// angulo_potenciometro(an_pin[5],tope_inf), 5,120);

	text("Pines digitales", 5, 108);

	text("Pin dig 22: " + dig_pin22, 5, 120);
	text("Pin dig 23: " + dig_pin23, 100, 120);
	text("Pin dig 24: " + dig_pin24, 5, 132);
	text("Pin dig 25: " + dig_pin25, 100, 132);
	text("Pin dig 26: " + dig_pin26, 5, 144);
	text("Pin dig 27: " + dig_pin27, 100, 144);

	text("Valor Inferior: " + tope_inf, 5, 156);
	text("Valor Superior: " + tope_sup, 100, 156);

	text("K: " + PID_K, 5, 168);
	text("Ti: " + PID_Ti, 65, 168);
	text("Td: " + PID_Td, 130, 168);
	text("Beta: " + PID_Beta, 5, 180);
	text("Tr: " + PID_Tr, 65, 180);
	text("N: " + PID_N, 130, 180);
	text("h: " + PID_h, 5, 192);
	text("Servo Activado: " + (servo == 1), 80, 192);

	// text("Angulo en torno a 1: " + redondear(alpha2(acel21)), 10,160);
	// text("Angulo en torno a 2: " + redondear(alpha1(acel11)), 10,180);
	if (received)
	rect(10, 10, 16, 16);
	received = false;
	// show_boxes();
	   }
	   */

	public double redondear(double numero/* , int decimales */) {
		int decimales = 2;
		double numero1 = numero;
		return Math.round(numero1 * Math.pow(10, decimales))
			/ Math.pow(10, decimales);
	}

	/**
	 * Transforms a certain number into degrees. To be used with the tiltmeter
	 * 
	 * @param Number
	 *            to be turned into degrees
	 * @return Number transformed into degrees
	 */
	public float grados(float numero) {
		return (float) (0.1840333 * numero + 14.905094);
	}

	/*
	 * these were the initial accelerometer models for determining the angles of
	 * higgs refered to the earth's surface. public float alpha1(float numero){
	 * return (float)(181.6446-0.32835*numero); }
	 * 
	 * public float alpha2(float numero){ return (float)(168.76-0.3117*numero);
	 * }
	 */

	/**
	 * Returns the value of the degree turned by the laser
	 * 
	 * @param Potentiometer
	 *            reading
	 * @param lowest
	 *            potentiometer value at the start up method
	 * @return Degree turned by the laser
	 */
	public double angulo_potenciometro(float lectura, int tope_inferior) {
		return redondear((float) (0.9346 * lectura - 0.9346 * tope_inferior - 13.6));
	}

}
