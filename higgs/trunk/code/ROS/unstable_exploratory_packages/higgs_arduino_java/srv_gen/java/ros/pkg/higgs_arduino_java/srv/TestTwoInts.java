/* Auto-generated by genmsg_cpp for file /usr/local/ros_aslab/higgs_arduino_java/srv/TestTwoInts.srv */

package ros.pkg.higgs_arduino_java.srv;

import java.nio.ByteBuffer;


public class TestTwoInts extends ros.communication.Service<TestTwoInts.Request, TestTwoInts.Response> {

  public static java.lang.String __s_getDataType() { return "higgs_arduino_java/TestTwoInts"; }
  public static java.lang.String __s_getMD5Sum() { return "f0b6d69ea10b0cf210cb349d58d59e8f"; }

  public java.lang.String getDataType() { return TestTwoInts.__s_getDataType(); }
  public java.lang.String getMD5Sum() { return TestTwoInts.__s_getMD5Sum(); }

  public TestTwoInts.Request createRequest() {
    return new TestTwoInts.Request();
  }

  public TestTwoInts.Response createResponse() {
    return new TestTwoInts.Response();
  }

static public class Request extends ros.communication.Message {

  public int a;
  public int b;

  public Request() {
  }

  public static java.lang.String __s_getDataType() { return "higgs_arduino_java/TestTwoIntsRequest"; }
  public java.lang.String getDataType() { return __s_getDataType(); }
  public static java.lang.String __s_getMD5Sum() { return "ef8322123148e475e3e93a1f609b2f70"; }
  public java.lang.String getMD5Sum() { return __s_getMD5Sum(); }
  public static java.lang.String __s_getServerMD5Sum() { return "f0b6d69ea10b0cf210cb349d58d59e8f"; }
  public java.lang.String getServerMD5Sum() { return __s_getServerMD5Sum(); }
  public static java.lang.String __s_getMessageDefinition() { return "int32 a\n" +
"int32 b\n" +
"\n" +
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
    __l += 4; // a
    __l += 4; // b
    return __l;
  }

  public void serialize(ByteBuffer bb, int seq) {
    bb.putInt(a);
    bb.putInt(b);
  }

  public void deserialize(ByteBuffer bb) {
    a = bb.getInt();
    b = bb.getInt();
  }

  @SuppressWarnings("all")
  public boolean equals(Object o) {
    if(!(o instanceof Request))
      return false;
    Request other = (Request) o;
    return
      a == other.a &&
      b == other.b &&
      true;
  }

  @SuppressWarnings("all")
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    long tmp;
    result = prime * result + this.a;
    result = prime * result + this.b;
    return result;
  }
} // class Request

static public class Response extends ros.communication.Message {

  public int sum;

  public Response() {
  }

  public static java.lang.String __s_getDataType() { return "higgs_arduino_java/TestTwoIntsResponse"; }
  public java.lang.String getDataType() { return __s_getDataType(); }
  public static java.lang.String __s_getMD5Sum() { return "0ba699c25c9418c0366f3595c0c8e8ec"; }
  public java.lang.String getMD5Sum() { return __s_getMD5Sum(); }
  public static java.lang.String __s_getServerMD5Sum() { return "f0b6d69ea10b0cf210cb349d58d59e8f"; }
  public java.lang.String getServerMD5Sum() { return __s_getServerMD5Sum(); }
  public static java.lang.String __s_getMessageDefinition() { return "int32 sum\n" +
"\n" +
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
    __l += 4; // sum
    return __l;
  }

  public void serialize(ByteBuffer bb, int seq) {
    bb.putInt(sum);
  }

  public void deserialize(ByteBuffer bb) {
    sum = bb.getInt();
  }

  @SuppressWarnings("all")
  public boolean equals(Object o) {
    if(!(o instanceof Response))
      return false;
    Response other = (Response) o;
    return
      sum == other.sum &&
      true;
  }

  @SuppressWarnings("all")
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    long tmp;
    result = prime * result + this.sum;
    return result;
  }
} // class Response

} //class

