/*
 * Copyright (C) 2011 Google Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package org.aslab.tests.nodeslistener;

import org.apache.commons.logging.Log;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.NodeMain;
import org.ros.node.topic.Subscriber;

import org.ros.message.*;



/**
 * A simple {@link Subscriber} {@link NodeMain}.
 * 
 * @author damonkohler@google.com (Damon Kohler)
 */
public class NodeListener extends AbstractNodeMain {

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("node_listener");
  }

  @Override
  public void onStart(ConnectedNode connectedNode) {
    final Log log = connectedNode.getLog();
    Subscriber<std_msgs.String> subscriber = connectedNode.newSubscriber("chatter", std_msgs.String._TYPE);
    subscriber.addMessageListener(new MessageListener<std_msgs.String>() {
      @Override
      public void onNewMessage(std_msgs.String message) {
        log.info("I heard: \"" + message.getData() + "\"");
      }
    });
    
    Subscriber<meta_msgs.NodesInfoList> subscriber2 = connectedNode.newSubscriber("node_list", meta_msgs.NodesInfoList._TYPE);
    subscriber2.addMessageListener(new MessageListener<meta_msgs.NodesInfoList>() {
        @Override
        public void onNewMessage(meta_msgs.NodesInfoList message) {
          log.info("I heard: \"" + "algo" + "\"");
        }
      });
  }
}
