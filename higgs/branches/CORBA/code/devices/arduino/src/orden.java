/*
 * @author Francisco J. Arjonilla
 * Last Change: mié jul 27 01:00  2011 C
 *
 * Stores the data structure to send for queueing the orders.
 */
public class orden
{
	/**
	 * Stores the value of the command to be sent to the Arduino board
	 */
	public int orden;

	/**
	 * Stores the number of the pin to be switched ON/OFF
	 */
	public int pin;

	public orden (int o, int p)
	{
		orden = o;
		pin = p;
	}
}

