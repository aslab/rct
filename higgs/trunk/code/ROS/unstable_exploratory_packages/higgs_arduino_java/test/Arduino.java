import processing.serial.*;
import gnu.io.*;

import java.lang.reflect.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * 
 * @author Carlos Hernandez
 *
 *         <p>
 *         Direct communication with the Arduino board. base on arduinoProcessing
 *         </p>
 */

public class Arduino implements SerialPortEventListener {
	
	/**
	 * Stores value of the digital pin 25 (compass)
	 */
	static int compass_dig_pin25;
	
	int lf = 10; // ASCII linefeed

	boolean received;
	Command orden = mainClass.orden;

	OutputStream serialOut;
	InputStream serialIn;
	
	
}