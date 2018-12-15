#include <ESP8266WiFi.h>

const char* ssid = "you AP name";
const char* password = "AP password";
const char* host = "server host";
String path = "/SpringMvcDemo/index.jsp";//file path
String postPath = "/SpringMvcDemo/login";// post adrress

void setup() {
 
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){// wait wifi model connecting
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP());

}

void loop() {

  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
     Serial.println("connection failed");
     return;
    }
    
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +                
  "Connection: keep-alive\r\n\r\n");//Http Get request 
  Serial.print(String("GET ") + path + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +                
  "Connection: keep-alive\r\n\r\n");//Http Get request 
  delay(500); // wait for server to respond

  String data = (String)"{\"heartbeat\":\"60\"}";//json data
  String postData = (String) "username=xuhe&password=123456";//body data
  int length = postData.length();
  String postRequest =(String)("POST ") + postPath + " HTTP/1.1\r\n" +
      "Content-Type: application/x-www-form-urlencoded;charset=utf-8\r\n" +
      "Host: " + host + ":" + httpPort + "\r\n" +          
      "Content-Length: " + length + "\r\n" +
      "Connection: Keep Alive\r\n\r\n" +
      postData+"\r\n";
  Serial.println(postRequest);
  client.print(postRequest); 
  delay(500);  
  // read response  
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);    // we'll parse the HTML body here
  }
    Serial.print("closing connection. ");
}
