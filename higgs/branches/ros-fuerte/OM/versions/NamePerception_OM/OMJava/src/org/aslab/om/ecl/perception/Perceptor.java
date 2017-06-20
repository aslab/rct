package org.aslab.om.ecl.perception;


/**
 * @author chcorbato
 *
 * parent class for perception modules or subsystems, TODO improve
 */
public abstract class Perceptor {
	protected Sensor sensor;

	public abstract void perceive();

}
