package org.aslab.om.ecl.perception;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.aslab.om.ecl.knowledge.KnowledgeBase;


/** 
 * <!-- begin-UML-doc -->
 * Currently not in use, this shall be an abstract class defining the generalities of ComponentsPerceptor
 * <p>Implementation of the Explicit Perceptor pattern</p>
 * <p>Activity diagram for the Explicit Perceptor pattern (realizes Ignacio's theory of perception)</p>
 * <img src="doc-files/ExplicitPerceptor-1.gif">
 * 
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class ExplicitPerceptor extends Perceptor {
	
	protected Set<Percept> percepts = new HashSet<Percept>();	// TODO find a better name
	
	protected Set<Referent> referents =  new HashSet<Referent>();
	
	protected KnowledgeBase kbase;
	
	public ExplicitPerceptor(Sensor s, KnowledgeBase k) {
		sensor = s;
		kbase = k;
	}

	/** Defines the basic steps of Ig's perception
	 * @see org.aslab.om.ecl.perception.Perceptor#perceive()
	 */
	@Override
	public void perceive(){
		updateReferents();		
		Set<Singularity> singularities = null;
		try {
			singularities = sensoryPerception();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		cognitivePerception(singularities);	
	}
	
	protected abstract void updateReferents();

	protected abstract void configSensors();

	protected abstract Set<Singularity> sensoryPerception() throws IllegalAccessException;
	
	protected abstract void cognitivePerception(Set<Singularity> sensoryInput);	
	

	/** 
	 * <!-- begin-UML-doc -->
	 * returns the referent instance (percept) that correspond to the singularity
	 * <!-- end-UML-doc -->
	 * @param sing the singularity that is to be matched to the known referent instances
	 * @return the percept with the highest recognizing score
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Percept identifyPercept(Singularity sing) {
		double score = 0;
		Percept best_match = null;
		
		for (Iterator<Percept> j = percepts.iterator(); j.hasNext();) {
			Percept base = j.next();
			if ( base.recognize(sing) > score){
				best_match = base;
				score = base.recognize(sing);
			}
		}
		
		if( score > 0.1 ){
			return best_match;
		}
		else
			return null;
	}

}
