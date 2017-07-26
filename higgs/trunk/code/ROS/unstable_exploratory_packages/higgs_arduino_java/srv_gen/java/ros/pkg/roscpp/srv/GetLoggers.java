/* Auto-generated by genmsg_cpp for file /opt/ros/diamondback/stacks/ros_comm/clients/cpp/roscpp/srv/GetLoggers.srv */

package ros.pkg.roscpp.srv;

import java.nio.ByteBuffer;


public class GetLoggers extends ros.communication.Service<GetLoggers.Request, GetLoggers.Response> {

  public static java.lang.String __s_getDataType() { return "roscpp/GetLoggers"; }
  public static java.lang.String __s_getMD5Sum() { return "32e97e85527d4678a8f9279894bb64b0"; }

  public java.lang.String getDataType() { return GetLoggers.__s_getDataType(); }
  public java.lang.String getMD5Sum() { return GetLoggers.__s_getMD5Sum(); }

  public GetLoggers.Request createRequest() {
    return new GetLoggers.Request();
  }

  public GetLoggers.Response createResponse() {
    return new GetLoggers.Response();
  }

static public class Request extends ros.communication.Message {


  public Request() {
  }

  public static java.lang.String __s_getDataType() { return "roscpp/GetLoggersRequest"; }
  public java.lang.String getDataType() { return __s_getDataType(); }
  public static java.lang.String __s_getMD5Sum() { return "d41d8cd98f00b204e9800998ecf8427e"; }
  public java.lang.String getMD5Sum() { return __s_getMD5Sum(); }
  public static java.lang.String __s_getServerMD5Sum() { return "32e97e85527d4678a8f9279894bb64b0"; }
  public java.lang.String getServerMD5Sum() { return __s_getServerMD5Sum(); }
  public static java.lang.String __s_getMessageDefinition() { return "\n" +
""; }
  public java.lang.String getMessageDefinition() { return __s_getMessageDefinition(); }

  public Request clone() {
    Request c = new Request();
    c.deserialize(serialize(0));
    return c;
  }

  public void setTo(ros.communication.Message m) {
    deserialize(m.serialize(0));
  }

  public int serializationLength() {
    int __l = 0;
    return __l;
  }

  public void serialize(ByteBuffer bb, int seq) {
  }

  public void deserialize(ByteBuffer bb) {
  }

  @SuppressWarnings("all")
  public boolean equals(Object o) {
    if(!(o instanceof Request))
      return false;
    Request other = (Request) o;
    return
      true;
  }

  @SuppressWarnings("all")
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    long tmp;
    return result;
  }
} // class Request

static public class Response extends ros.communication.Message {

  public java.util.ArrayList<ros.pkg.roscpp.msg.Logger> loggers = new java.util.ArrayList<ros.pkg.roscpp.msg.Logger>();

  public Response() {
  }

  public static java.lang.String __s_getDataType() { return "roscpp/GetLoggersResponse"; }
  public java.lang.String getDataType() { return __s_getDataType(); }
  public static java.lang.String __s_getMD5Sum() { return "32e97e85527d4678a8f9279894bb64b0"; }
  public java.lang.String getMD5Sum() { return __s_getMD5Sum(); }
  public static java.lang.String __s_getServerMD5Sum() { return "32e97e85527d4678a8f9279894bb64b0"; }
  public java.lang.String getServerMD5Sum() { return __s_getServerMD5Sum(); }
  public static java.lang.String __s_getMessageDefinition() { return "Logger[] loggers\n" +
"\n" +
"================================================================================\n" +
"MSG: roscpp/Logger\n" +
"string name\n" +
"string level\n" +
"\n" +
""; }
  public java.lang.String getMessageDefinition() { return __s_getMessageDefinition(); }

  public Response clone() {
    Response c = new Response();
    c.deserialize(serialize(0));
    return c;
  }

  public void setTo(ros.communication.Message m) {
    deserialize(m.serialize(0));
  }

  public int serializationLength() {
    int __l = 0;
    __l += 4;
    for(ros.pkg.roscpp.msg.Logger val : loggers) {
      __l += val.serializationLength();
    }
    return __l;
  }

  public void serialize(ByteBuffer bb, int seq) {
    bb.putInt(loggers.size());
    for(ros.pkg.roscpp.msg.Logger val : loggers) {
      val.serialize(bb, seq);
    }
  }

  public void deserialize(ByteBuffer bb) {

    int __loggers_len = bb.getInt();
    loggers = new java.util.ArrayList<ros.pkg.roscpp.msg.Logger>(__loggers_len);
    for(int __i=0; __i<__loggers_len; __i++) {
      ros.pkg.roscpp.msg.Logger __tmp = new ros.pkg.roscpp.msg.Logger();
      __tmp.deserialize(bb);
      loggers.add(__tmp);;
    }
  }

  @SuppressWarnings("all")
  public boolean equals(Object o) {
    if(!(o instanceof Response))
      return false;
    Response other = (Response) o;
    return
      loggers.equals(other.loggers) &&
      true;
  }

  @SuppressWarnings("all")
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    long tmp;
    result = prime * result + (this.loggers == null ? 0 : this.loggers.hashCode());
    return result;
  }
} // class Response

} //class

