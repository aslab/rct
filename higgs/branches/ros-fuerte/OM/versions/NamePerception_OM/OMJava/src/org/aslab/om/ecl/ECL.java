/**
 * the org.aslab.om.ecl package contains the Java implementation of the ECL Architectural Framework
 */
package org.aslab.om.ecl;

import org.aslab.om.ecl.Goal;
import org.aslab.om.ecl.action.Actuator;
import org.aslab.om.ecl.perception.Perceptor;
import org.aslab.om.ecl.perception.Sensor;

/** 
 * <!-- begin-UML-doc -->
 * <p>change name: ECL0<br></p><p><br></p><p>@author chcorbato</p>
 * this class defines the basics of an ECL unit
 * <p>The operation of the ECL follows the following activity diagram, which is basically a periodic loop which can be reset by an incoming goal</p>
 * <img src="doc-files/ECL-1.gif">
 * <p>The following sequence diagram shows the standard operation of the ECL as interactions between its conscituent objects</p>
 * <img src="doc-files/ECL-2.gif">
 * 
 * <!-- end-UML-doc -->
 * @author chcorbato
 * @!generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public abstract class ECL extends Thread {

	/** 
	 * <!-- begin-UML-doc -->
	 * loop&nbsp;period&nbsp;in&nbsp;millisecs,&nbsp;by&nbsp;default&nbsp;2&nbsp;secs
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected long tstep = new Integer(2000);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private boolean running = new Boolean(false);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private boolean alive = new Boolean(true);

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Goal goal = null;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Sensor sensor;

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Actuator actuator;
	
	protected Perceptor perceptor;


	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @param eclName the name for the org.aslab.om.ecl to identify it
	 * @param s the sensor for the org.aslab.om.ecl
	 * @param a the actuator for the org.aslab.om.ecl
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ECL(String eclName, Sensor s, Actuator a) {
		// begin-user-code
		super(eclName);
		sensor = s;
		actuator = a;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method for the <b>manager </b>of an ECL</p>
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void run() {
		// begin-user-code

		while (alive) {
			long startTime = System.currentTimeMillis();
			try {
				loop();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if ((tstep - (System.currentTimeMillis() - startTime)) < 0) {
				System.out.println("Loop took longer than period");
				continue;
			}
			try {
				sleep(tstep - (System.currentTimeMillis() - startTime));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		// end-user-code
	}

	// ECL loop becomes active
	/** 
	 * <!-- begin-UML-doc -->
	 * method for "controllable" components to start them
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void startECL() {
		// begin-user-code
		alive = true;
		running = true;
		start();
		// end-user-code
	}

	// ECL loop becomes inactive and internal memory is lost
	/** 
	 * <!-- begin-UML-doc -->
	 * method for "controllable" components to stop them
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void stopECL() {
		// begin-user-code
		alive = false;
		running = false;
		resetInternalState();
		// end-user-code
	}

	// ECL loop becomes inactive but internal information is preserved
	/** 
	 * <!-- begin-UML-doc -->
	 * method for "controllable" components to freeze their operation them
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void pauseECL() {
		// begin-user-code
		running = false;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * method for "controllable" components to resume their operation
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void resumeECL() {
		// begin-user-code
		running = true;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected abstract void resetInternalState();

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method&nbsp;for&nbsp;the&nbsp;<b>manager&nbsp;</b>of&nbsp;the&nbsp;org.aslab.om.ecl,&nbsp;so&nbsp;as&nbsp;to&nbsp;provide&nbsp;it&nbsp;with&nbsp;a&nbsp;reference&nbsp;to&nbsp;its&nbsp;actuators&nbsp;so&nbsp;as&nbsp;to&nbsp;be&nbsp;able&nbsp;to&nbsp;send&nbsp;action_list&nbsp;to&nbsp;them</p>
	 * <!-- end-UML-doc -->
	 * @param a
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setActuator(Actuator a) {
		// begin-user-code
		actuator = a;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method for an application <b>user </b>of the ECL</p>
	 * <!-- end-UML-doc -->
	 * @param g
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public abstract void setGoal(Goal g);

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>method for the <b>manager </b>of the org.aslab.om.ecl</p>
	 * <!-- end-UML-doc -->
	 * @param s
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setSensors(Sensor s) {
		// begin-user-code
		sensor = s;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <p>not to be called externally - just an specification</p><p>intended as an internal method - to be moved to an ECL general class from which an org.aslab.om.ecl inherits</p><p>method with the control cycle implemented by the org.aslab.om.ecl</p><p>it is called periodically at the rate specified for the org.aslab.om.ecl (from run method)</p>
	 * <!-- end-UML-doc -->
	 * @throws InterruptedException
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	private synchronized void loop() throws InterruptedException {
		// begin-user-code
		if (!running)
			return;
		perceive();
		// if there is no goal nor evaluation nor control can be performed
		if (goal == null)
			return;
		evaluate();
		control(); // compute and realise control action
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * the perception
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected abstract void perceive();

	/** 
	 * <!-- begin-UML-doc -->
	 * update any data structure containing an evaluation of the achievement of the goal
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected abstract void evaluate();

	/** 
	 * <!-- begin-UML-doc -->
	 * the control or action generation method
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected abstract void control();

	/** 
	 * <!-- begin-UML-doc -->
	 * sets&nbsp;the&nbsp;ECL&nbsp;loop&nbsp;period<br>@param&nbsp;tstep&nbsp;desired&nbsp;loop&nbsp;period&nbsp;in&nbsp;millisecs&nbsp;
	 * <!-- end-UML-doc -->
	 * @param tstep
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setTstep(long tstep) {
		// begin-user-code
		this.tstep = tstep;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <br>@return&nbsp;the&nbsp;loop&nbsp;period&nbsp;in&nbsp;millisecs
	 * <!-- end-UML-doc -->
	 * @return the period of this loop in millisecs
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double getTstep() {
		// begin-user-code
		return tstep;
		// end-user-code
	}

}