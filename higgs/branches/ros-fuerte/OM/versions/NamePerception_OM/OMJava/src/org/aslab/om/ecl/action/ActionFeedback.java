package org.aslab.om.ecl.action;

/**
 * Class to convey all the information about the result of an action as provided by its executor
 * 
 * @author chcorbato
 */
public class ActionFeedback {
	
	/**
	 * the ID of the actions the feedback corresponds to
	 */
	public short actionID;
	
	
	/**
	 * the result of the action (success or failure)
	 */
	public ActionResult result;
	
	/**
	 * any log information about the execution of the action
	 */
	public String log;
	
	public ActionFeedback(){
	}
	
	/**
	 * a constructor that initializes all the attributes
	 * @param id
	 * @param r
	 * @param s
	 */
	public ActionFeedback(short id, ActionResult r, String s){
		actionID = id;
		result = r;
		log = s;
	}


}
