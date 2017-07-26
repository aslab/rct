package org.aslab.om.metacontrol.action;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.aslab.om.ecl.action.ActionStatus;


public class Reconfiguration {
	
	/**
	 * a map of ComponentActions indexed by their action ID
	 */
	public Map<Short,ComponentAction> action_list = new HashMap<Short,ComponentAction>();
	
	public void addAction(ComponentAction action) {
		action_list.put(action.getId(), action);
	}

	/**
	 * processes the actions in the list that had not been processed but now can be
	 * @return the commands of the action_list that had not been processed, null if none
	 */
	public Set<ReconfigurationCommand> process(){
		Set<ReconfigurationCommand> aux = new HashSet<ReconfigurationCommand>();
		for(Iterator<ComponentAction> iter = action_list.values().iterator(); iter.hasNext();){
			ReconfigurationCommand command = (ReconfigurationCommand) iter.next().execute();
			if (command != null)
				aux.add(command);
		}
		if (aux.isEmpty())
			return null;
		else
			return aux;
	}
	
	/**
	 * for debugging purposes, only actions that are not successfully done are printed
	 */
	public void print(){
		System.out.println("   --> Reconfiguration:");
		for (Iterator<ComponentAction> iter = action_list.values().iterator(); iter.hasNext();){
			ComponentAction action = iter.next();
			
			if( action.getStatus() != ActionStatus.SUCCESS )
				action.print();
		}
	}

	/**
	 * clean up the action plan according the status of actions
	 * for the moment there is no re-planning, but if it were, it should go here
	 * for the moment we only remove actions that are completed (either FAILURE or SUCCESS)
	 */
	public void updatePlan() {
		
		for( Iterator<ComponentAction> iter = action_list.values().iterator(); iter.hasNext();){
			ComponentAction action = iter.next();
			if ( action.getStatus() == ActionStatus.FAILURE ||
					action.getStatus() == ActionStatus.SUCCESS
				){
				action_list.remove(action.getId());
			}	
			
		}
	}
		

	
}
