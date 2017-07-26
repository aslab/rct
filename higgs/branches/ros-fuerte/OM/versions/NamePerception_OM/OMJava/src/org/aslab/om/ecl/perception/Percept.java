package org.aslab.om.ecl.perception;

import java.sql.Time;

/**
 * @author chcorbato
 * 
 * object that corresponds to an instance referent, rather than an Ig's proper percept
 * the idea is that a previous percept is also a referent in the next preception
 */
public interface Percept extends Referent {
	/**
	 * Updates the info in this percept from a corresponding singularity
	 * @param sing the ingularity from which to take info about this referent and include in this object
	 * as percept
	 */
	public void update(Singularity sing);	// TODO somewhere better
	public boolean internalModel(); // TODO move somewhere better
	public void setTime(Time t);
}
