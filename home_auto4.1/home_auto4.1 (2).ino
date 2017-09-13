#include <ESP8266WiFi.h>

WiFiServer server(80); //Initialize the server on Port 80

const int DEV1_PIN = 16;
const int DEV2_PIN = 12;
const int DEV3_PIN = 13;
const int DEV4_PIN = 14;
const int SENS1_PIN = 4;
const int SENS2_PIN = 5;
double timer_on = 0; 
int timer_count = 0;
int timer_flag = 0;
int timer_check_flag = 0;
double counter = 0;

void setup() {
pinMode(DEV1_PIN, OUTPUT);
digitalWrite(DEV1_PIN, LOW); //Initial state is ON
pinMode(DEV2_PIN, OUTPUT);
digitalWrite(DEV2_PIN, LOW); //Initial state is ON
pinMode(SENS1_PIN, INPUT_PULLUP);
pinMode(SENS2_PIN, INPUT_PULLUP);
WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
WiFi.softAP("SAM-ESP12F", "123456789x"); // Provide the (SSID, password); . 
server.begin(); // Start the HTTP Server
Serial.begin(9600); //Start communication between the ESP8266-12E and the monitor window

}
void loop() { 
WiFiClient client = server.available();
if (!client) { 
  check_timer();
return; 
} 

//Looking under the hood

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
digitalWrite(DEV2_PIN, HIGH);}
else if (request.indexOf("/rst") != -1){ 
timer_on = 0;
timer_count = 0;
timer_check_flag = 0;  
timer_flag = 0;
digitalWrite(DEV1_PIN, LOW);
}
else if (request.indexOf("/10tmr") != -1){ 
timer_flag = timer_flag+1;
Serial.println("timer_flag = ");
Serial.println(timer_flag);
if (timer_flag == 1) {
Serial.println("Setting timer ....");  
timer_check_flag = 1;
timer_count = 10;
timer_on = millis();
digitalWrite(DEV1_PIN, HIGH);
Serial.print("Set timer count = ");
Serial.print(timer_count);
}
}

else if (request.indexOf("/20tmr") != -1) { 
timer_flag = timer_flag+1;
Serial.println("timer_flag = ");
Serial.println(timer_flag);
if (timer_flag == 1) {
Serial.println("Setting timer ....");  
timer_check_flag = 1;
timer_count = 20;
timer_on = millis();
digitalWrite(DEV1_PIN, HIGH);
Serial.print("Set timer count = ");
Serial.print(timer_count);
}
}
else if (request.indexOf("/30tmr") != -1) { 
timer_flag = timer_flag+1;
Serial.println("timer_flag = ");
Serial.println(timer_flag);
if (timer_flag == 1) {
Serial.println("Setting timer ...."); 
timer_check_flag = 1;
timer_count = 30;
timer_on = millis();
digitalWrite(DEV1_PIN, HIGH);
Serial.print("Set timer count = ");
Serial.print(timer_count);
}
}

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
if (timer_check_flag == 1) {
client.println("<meta http-equiv=\"refresh\" content=\"2\" />");
}
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
client.println("</head>");
client.println("<body bgcolor = \"#69afff\">");
client.println("<center>");
client.println("<h2 style= \"background-color:LightSeaGreen\"><center><font face=\"Verdana\" size=\"16\" color=\"LightSeaGreen\"> - </font></center></h1>");
client.println("</center>");
client.println("<center>");
client.println("<h1 style= \"background-color:LightSteelBlue\"><center><font face=\"Verdana\" size=\"20\" color=\"#E11711\"> Home Automation v4.1 </font></center></h2>");
client.println("</center>");
client.println("<center>");
client.println("<h3 style= \"background-color:Silver\"><center><font face=\"Verdana\" size=\"16\" color=\"Silver\"> - </font></center></h3>");
client.println("</center>");
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
client.println("<center>");
client.println("<font face=\"Verdana\" size=\"12\" color=\"#000000\">TIMER</font>");
client.println(counter);
if ((timer_count == 10) && (timer_check_flag == 1))  {
  client.println("<a href=\"/10tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#00FF00\">10MINS</button></a>");
}
else  
{
  client.println("<a href=\"/10tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#A1C0A1\">10MINS</button></a>");
}
if ((timer_count == 20) && (timer_check_flag == 1))  {
  client.println("<a href=\"/20tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#00FF00\">20MINS</button></a>");
}
else
{
  client.println("<a href=\"/20tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#A1C0A1\">20MINS</button></a>");  
}
if ((timer_count == 30) && (timer_check_flag == 1))  {
  client.println("<a href=\"/30tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#00FF00\">30MINS</button></a>");
}
else
{
  client.println("<a href=\"/30tmr\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#A1C0A1\">30MINS</button></a>"); 
}
if (timer_flag != 0) {
  client.println("<a href=\"/rst\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#FF0000\">RESET</button></a>"); 
}
else
{
      client.println("<a href=\"/rst\"\"><button type=\"submit\" value=\"Submit\" style= \"width:200px;height:75px;font-size:30px;background-color:#E89779\">RESET</button></a>"); 
   
}
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
//client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Arial Italic\" size=\"10\" color=\"#000000\">OUTPUT STATUS</font>");
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
client.println("</center>");
client.println("<hr/><hr>");
//client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Arial Italic\" size=\"10\" color=\"#000000\">SENSOR STATUS</font>");
client.println("</center>");
client.println("<center>");
client.println("<table border=\"5\">");
client.println("<tr>");
if (digitalRead(SENS1_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Sensor 1 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Sensor 1 is OFF</td>");
}
client.println("<br />");
if (digitalRead(SENS2_PIN))
{ 
client.print("<td style= \"background-color:lime;color:red\">Sensor 2 is ON</td>");
}
else
{
client.print("<td style= \"background-color:red;color:black\">Sensor 2 is OFF</td>");
}
client.println("</tr>");
client.println("</table>");
client.println("<br><br>");
client.println("<hr/><hr>");
//client.println("<br><br>");
client.println("<center>");
client.println("<font face=\"Arial Italic\" size=\"5\" color=\"#000000\">https://github.com/srebosura/ESP8266</font>");
client.println("</center>");
client.println("</html>"); 

check_timer();
client.flush();
//delay(1); 
Serial.println("Client disonnected");
}

void check_timer() {
if (timer_check_flag == 1)  {
  //Serial.println("Checking timer ....");
  counter = (millis() - timer_on)/1000; 
  Serial.println(counter);
  //Serial.println(timer_flag);
  if ((millis() - timer_on) >= (timer_count*1000*60))  {
  digitalWrite(DEV1_PIN, LOW);
  timer_on = 0;
  timer_count = 0;
  //timer_flag = 0;
  timer_check_flag = 0;
  Serial.println("Set timer off!");
  }
}
}


