package org.aslab.om.ecl.knowledge;

import java.io.Serializable;

import org.aslab.om.ecl.perception.Percept;


/**
 * @author chcorbato
 * TODO refactor : i.e. convert into interface
 * state atoms capture knowledge of the instantaneous state of the plant
 */
public abstract class StateAtom extends KnowledgeAtom implements Percept, Serializable {


}
