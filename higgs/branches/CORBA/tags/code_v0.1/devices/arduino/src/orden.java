/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
public class orden
{
	/**
	 * Stores the value of the command to be sent to the Arduino board
	 */
	public int orden;

	/**
	 * Stores the number of the pin to me switched ON/OFF
	 */
	public int pin;

	public orden (int o, int p)
	{
		orden = o;
		pin = p;
	}
}

