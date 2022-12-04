import processing.serial.*;
import processing.net.*;
Serial p;
Server s;
Client c;
void setup() {
  p = new Serial(this, "COM6", 9600); // 주의1: 포트번호
  s = new Server(this, 12345);
}
String m="0";
void draw() {
  c = s.available();
  if (c!=null) {
    String req = c.readString();
    if(req.indexOf("GET")==0)
    {
      if (c!=null) {
        String a = c.readString();
        c.write("HTTP/1.1 200 OK\r\n\r\n");
        c.write(m);
        c.stop();
      }
    }
    else if(req.indexOf("PUT")==0)
    {
      int n = req.indexOf("\r\n\r\n")+4;
        req = req.substring(n);
        req += '\n';
        p.write(req);
    }
  }
  
  
  if (p.available()>0) {
    String a = p.readString();
    if (a!=null) m = a;
    background(0,0,0);
    text(a, 30, 30);
  }
}
