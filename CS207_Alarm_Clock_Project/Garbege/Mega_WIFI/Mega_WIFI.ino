#include<Stream.h>
#include<String.h>
#include<SoftwareSerial.h>

int wifi_Act_Pin = 2;
String s = "";
String r = "";

void print_WIFI_C()
{
  Serial.println("List of Basic commands: ");
  Serial.println("");
  Serial.println(" 1) AT - Status check");
  Serial.println(" 2) AT+RST - Reset WI-FI");
  Serial.println(" 3) AT+GMR - Print firmware version");
  Serial.println(" 4) AT+GSLP= Millisecond - Enter deep sleep mode for set time(Reseet Pin High)");
  Serial.println(" 5) ATE0 - Disable echo (Does not send back received command)");
  Serial.println(" 6) ATE1 - Enable echo (Does send back received command)");
  Serial.println("");
  Serial.println("List of WI-FI layer commands: ");
  Serial.println("");
  Serial.println(" 1) AT+CWMODE=? - List valid modes");
  Serial.println(" 2) AT+CWMODE? - QueryAT+CWLAP AP’s info which is connect by ESP8266.");
  Serial.println(" 3) AT+CWMODE=mode - 1 = Station mode (client); 2 = AP mode (host); 3 = AP + Station mode;");
  Serial.println(" 4) AT+CWJAP? - Prints the SSID of Access Point ");
  Serial.println(" 5) AT+CWJAP=ssid,pwd - Use String Symbvol to connect a SSID with supplied password.");
  Serial.println(" 6) AT+CWLAP - Lists available Access Points.");
  Serial.println(" 7) AT+CWLAP=ssid,mac,ch - Search available APs with specific conditions. ecn: 0 = OPEN 1 = WEP 2 = WPA_PSK 3 = WPA2_PSK 4 = WPA_WPA2_PSK. ssid: String, SSID of AP. rssi: signal strength. mac: String, MAC address");
  Serial.println(" 8) AT+CWQAP - Disconnect ESP8266 from the AP is currently connected to.");
  Serial.println(" 9) AT+CWSAP? - Query configuration of ESP8266 softAP mode.");
  Serial.println("10) AT+CWSAP=ssid,pwd,ch,ecn - Use quatation to set configuration of softAP mode.(ssid: String, ESP8266’s softAP SSID pwd: String, Password, no longer than 64 characters ch: channel id  ecn: 0 = OPEN 2 = WPA_PS 3 = WPA2_PSK 4 = WPA_WPA2_PSK)");
  Serial.println("11) AT+CWLIF - List information on of connected clients.");
  Serial.println("12) AT+CWDHCP=mode,en - (NOT FUNCTIONAL) Enable or disable DHCP for selected mode");
  Serial.println("13) AT+CIPSTAMAC? - Print current MAC ESP8266’s address.");
  Serial.println("14) AT+CIPSTAMAC=mac - Use quatation to set ESP8266’s MAC address");
  Serial.println("15) AT+CIPAPMAC? - Get MAC address of ESP8266 softAP.");
  Serial.println("16) AAT+CIPAPMAC=mac - Use quatation to set mac of ESP8266 softAP.");
  Serial.println("17) AT+CIPSTA? - Get IP address of ESP8266 station.");
  Serial.println("18) AT+CIPSTA=ip - Use quatation to set ip addr of ESP8266 station.");
  Serial.println("19) AT+CIPAP? - Get ip address of ESP8266 softAP.");
  Serial.println("20) AT+CIPAP=ip - Use quatation to set ip addr of ESP8266 softAP.");
  Serial.println("");
  Serial.println("TCPIP Layer");
  Serial.println("");
  Serial.println(" 1) AT+CIPSTATUS=? - Connection is Ok");
  Serial.println(" 2) AT+CIPSTATUS - Get information about connection. status： 2: Got IP 3: Connected 4: Disconnected id： id of the connection (0~4), for multi-connect type： String, “TCP” or “UDP” addr： String, IP address. port： port number tetype： 0 = ESP8266 runs as a client 1 = ESP8266 runs as a server");
  Serial.println(" 3) AT+CIPSTART=? - List possible commands variations");
  Serial.println(" 4) AT+CIPSTART=type,addr,port - Start a connection as client. (Single connection mode)");
  Serial.println(" 5) AT+CIPSTART=id,type,addr,port - Start a connection as client. (Multiple connection mode. Parameters: id: 0-4, id of connection. Type: String, “TCP” or “UDP”. Addr: String. Port: String, remote port)");
  Serial.println(" 6) AT+CIPSEND=? - Send test");
  Serial.println(" 7) AT+CIPSEND=length - Set length of the data that will be sent. For normal send (single connection).");
  Serial.println(" 8) AT+CIPSEND=id,length - Set length of the data that will be sent. For normal send (multiple connection). Parameters: id: ID no. of transmit connection. Length: data length, MAX 2048 bytes");
  Serial.println(" 9) AT+CIPSEND - Send data. For unvarnished transmission mode. Unvarnished Transmission Mode Wrap return “>” after execute command. Enters unvarnished transmission, 20ms interval between each packet, maximum 2048 bytes per packet. When single packet containing “+++” is received, it returns to command mode.");
  Serial.println("10) AT+CIPCLOSE=? - Connection close status check");
  Serial.println("11) AT+CIPCLOSE=id - Close TCP or UDP connection.For multiply connection mode");
  Serial.println("12) AT+CIPCLOSE - Close TCP or UDP connection.For single connection mode");
  Serial.println("13) AT+CIFSR=? Status check");
  Serial.println("14) AT+CIFSR - Get local IP address.");
  Serial.println("15) AT+CIPMUX=mode - (1 or 0) Enable / disable multiplex mode (up to 4 conenctions)");
  Serial.println("16) AT+CIPMUX? - Print current multiplex mode.");
  Serial.println("17) AT+CIPSERVER=mode[,port] - Configure ESP8266 as server. Parameters: mode: 0: Delete server (need to follow by restart). 1: Create server. port: port number, default is 333. NOTE: Server can only be created when AT+CIPMUX=1. Server monitor will automatically be created when Server is created. When a client is connected to the server, it will take up one connection，be gave an id.");
  Serial.println("18) AT+CIPMODE? -  Set transfer mode, normal or transparent transmission.");
  Serial.println("19) AT+CIPMODE=mode - Set transfer mode,normal or transparent transmission. Parameters: Mode: 0: Normal mode. 1: Unvarnished transmission mode");
  Serial.println("20) AT+CIPSTO? - Query server timeout. Parameters: Time: server timeout, range 0~7200 seconds");
  Serial.println("21) AT+CIUPDATE - Start update through network. Parameters: -n: 1: found server 2: connect server 3: got edition 4: start update");
  Serial.println("22) +IPD,len:data - Receive network data from single connection.");
  Serial.println("23) +IPD,id,len:data - Receive network data from multiple connection.");
  Serial.println("");
  Serial.println("Enter your command here: ");
  Serial.println("");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(wifi_Act_Pin, OUTPUT);
  digitalWrite(wifi_Act_Pin, HIGH);
  Serial.println("Enter your command here: ");
  Serial.println("");
  Serial.println("To show list of available commands type Help or F1");
  Serial.println("");

}

void loop() {
  while (!Serial.available()) {}
  while (Serial.available()) {
    s = Serial.readString();
  }
  if ((s == "Help\r\n") || (s == "help\r\n") || (s == "HELP\r\n") || (s == "F1\r\n")) {
    Serial.println("List of available command: ");
    Serial.println("");
    print_WIFI_C();
    s = "";
  }
  else if((s.indexOf('A') == 0) && (s.indexOf('T') == 1) || (s.indexOf('+') == 0)){
    Serial1.print(s);
       while (!Serial1.available()){}
         while (Serial1.available()) {
            r += Serial1.readString();
            delay(1000);
    }
    Serial.println("WI-FI command recived: " + s);
    Serial.println("Return from the WI-FI module is: ");
    Serial.println("");
    Serial.println(r);
    while(Serial.available()){}

  }
    s = "";
    r = "";
}
