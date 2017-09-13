#include <ESP8266WiFi.h>

WiFiServer server(80); //Initialize the server on Port 80

const int DEV1_PIN = 16;
const int DEV2_PIN = 12;
const int DEV3_PIN = 13;
const int DEV4_PIN = 14;

void setup() {
pinMode(16, OUTPUT);
digitalWrite(DEV1_PIN, LOW); //Initial state is ON
pinMode(12, OUTPUT);
digitalWrite(DEV2_PIN, LOW); //Initial state is ON

WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
WiFi.softAP("SAM-ESP12F", "123456789x"); // Provide the (SSID, password); . 
server.begin(); // Start the HTTP Server

}
void loop() { 

WiFiClient client = server.available();
if (!client) { 
return; 
} 

//Looking under the hood
Serial.begin(9600); //Start communication between the ESP8266-12E and the monitor window
IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
Serial.print("Server IP is: "); // Print the IP to the monitor window 
Serial.println(HTTPS_ServerIP);
//Read what the browser has sent into a String class and print the request to the monitor
String request =  client.readStringUntil('\r'); 
//Looking under the hood 
Serial.println(request);

if (request.indexOf("/1OFF") != -1){ 
digitalWrite(DEV1_PIN, LOW); }
else if (request.indexOf("/1ON") != -1){ 
digitalWrite(DEV1_PIN, HIGH); } 
if (request.indexOf("/2OFF") != -1){ 
digitalWrite(DEV2_PIN, LOW); }
else if (request.indexOf("/2ON") != -1){ 
digitalWrite(DEV2_PIN, HIGH); 
}

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("<meta http-equiv=\"refresh\" content=\"15\" />");
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
client.println("</head>");
client.println("<body bgcolor = \"#69afff\">");
client.println("<center>");
client.println("<h2 style= \"background-color:LightSeaGreen\"><center><font face=\"Verdana\" size=\"16\" color=\"LightSeaGreen\"> - </font></center></h1>");
client.println("</center>");
client.println("<center>");
client.println("<h1 style= \"background-color:LightSteelBlue\"><center><font face=\"Verdana\" size=\"20\" color=\"#E11711\"> Home Automation v1.02 </font></center></h2>");
client.println("</center>");
client.println("<center>");
client.println("<h3 style= \"background-color:Silver\"><center><font face=\"Verdana\" size=\"16\" color=\"Silver\"> - </font></center></h3>");
client.println("</center>");
client.println("<br><br>");
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Verdana\" size=\"12\" color=\"#000000\">DEV 1</font>");
if (digitalRead(DEV1_PIN))
{ 
client.println("<a href=\"/1ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
}
else
{
client.println("<a href=\"/1ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#A1C0A1\">ON </button></a>");
}
client.println("<a href=\"/1OFF\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#E89779\">OFF </button></a><br />"); 
client.println("</center>"); 
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Verdana\" size=\"12\" color=\"#000000\">DEV 2</font>");
if (digitalRead(DEV2_PIN))
{ 
client.println("<a href=\"/2ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
}
else
{
client.println("<a href=\"/2ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#A1C0A1\">ON </button></a>");
}
//client.println("<a href=\"/2ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
client.println("<a href=\"/2OFF\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#E89779\">OFF </button></a><br />"); 
client.println("</center>"); 
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Verdana\" size=\"12\" color=\"#000000\">DEV 3</font>");
if (digitalRead(DEV3_PIN))
{ 
client.println("<a href=\"/3ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
}
else
{
client.println("<a href=\"/3ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#A1C0A1\">ON </button></a>");
}
//client.println("<a href=\"/Device3on\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
client.println("<a href=\"/3OFF\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#E89779\">OFF </button></a><br />"); 
client.println("</center>"); 
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Verdana\" size=\"12\" color=\"#000000\">DEV 4</font>");
if (digitalRead(DEV4_PIN))
{ 
client.println("<a href=\"/4ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
}
else
{
client.println("<a href=\"/4ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#A1C0A1\">ON </button></a>");
}
//client.println("<a href=\"/4ON\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#00FF00\">ON </button></a>");
client.println("<a href=\"/4OFF\"\"><button style= \"width:200px;height:100px;font-size:100px;background-color:#E89779\">OFF </button></a><br />"); 
client.println("</center>");
client.println("<hr/><hr>");
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Arial Italic\" size=\"10\" color=\"#000000\">I/O STATUS</font>");
client.println("</center>");
client.println("<center>");
client.println("<table border=\"5\">");
client.println("<tr>");
if (digitalRead(DEV1_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Dev 1 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Dev 1 is OFF</td>");
}
client.println("<br />");
if (digitalRead(DEV2_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Dev 2 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Dev 2 is OFF</td>");
}
client.println("</tr>");
client.println("<tr>");
if (digitalRead(DEV3_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Dev 3 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Dev 3 is OFF</td>");
}
if (digitalRead(DEV4_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Dev 4 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Dev 4 is OFF</td>");
}
client.println("</tr>");
client.println("</table>");
client.println("<br><br>");
client.println("<br><br>");
client.println("</center>");
client.println("<hr/><hr>");
client.println("<br><br>");
client.println("<br><br>");
client.println("<br><br>");
client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Arial Italic\" size=\"6\" color=\"#000000\">https://github.com/srebosura/ESP8266</font>");
client.println("</center>");
client.println("</html>"); 

//delay(1); 
Serial.println("Client disonnected");
}


