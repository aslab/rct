package org.aslab.om.ecl.perception;

public interface Referent {
	/**
	 * recognizes an instance (singularity) as being of a type (referent)
	 * perception method to recognize or identify a referent type in a singularity
	 * encodes the perceptual model of the referent type
	 * @param s the singularity to be recognized of corresponding to a certain referent
	 * @return level of matching in the identification, from 0= none to 1=perfect match
	 */
	public double recognize(Singularity s); // for referents which are instances this is the identify method
	
	
	public String getName();
}
