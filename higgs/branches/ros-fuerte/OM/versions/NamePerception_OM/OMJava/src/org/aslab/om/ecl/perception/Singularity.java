package org.aslab.om.ecl.perception;

import java.sql.Time;

public abstract class Singularity {
	/**
	 * a singularity is an informational signal obtained at a certain time
	 */
	Time timestamp = new Time(System.currentTimeMillis());
}
