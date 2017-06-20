import ros.*;
import ros.communication.*;

public class Talker {
	public static void main(String args[]) 
	                       throws InterruptedException, RosException {
		Ros ros = Ros.getInstance();
		ros.init("Talker");
				
		ros.pkg.std_msgs.msg.String msg = new ros.pkg.std_msgs.msg.String();
		ros.pkg.sensor_msgs.Imu msg_c = new ros.pkg.sensor_msgs.Imu();
		
		NodeHandle n = ros.createNodeHandle();	
		
		Publisher<ros.pkg.std_msgs.msg.String> pub = 
							    n.advertise("chatter", msg, 100);
		Publisher<ros.pkg.sensor_msgs.Imu> pub_c = 
            					n.advertise("compass", msg_c, 100);
		
		int count = 0; 
		while(pub.isValid()) {
			msg.data = "Hello there! This is message [" + count + "]"; 
			pub.publish(msg);
			
			msg_c.orientation.x = 0;
			msg_c.orientation.y = 0;
			msg_c.orientation.z = 0;
			msg_c.orientation.w = 0;
			
			pub.publish(msg_c);
			
			ros.logInfo("I published [" + msg.data + "]"); 
			ros.logInfo("and also [" + msg_c.orientation.x + "]");
			n.spinOnce();
			Thread.sleep(200);
			count++; 
		}
	}
}