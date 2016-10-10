#include <UIPEthernet.h>

EthernetServer server = EthernetServer(1);//port
EthernetClient client;
bool alreadyConnected = false;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  IPAddress myIP(172,16,13,21);
  Ethernet.begin(mac,myIP);
  server.begin();
}

void loop()
{  
  client = server.available();
  if(client.connected()){
    if (client.available() > 0) {
      parse();
    }
  }
}

void parse(){
  String in;
  char tmp;
  while(client.available() > 0){
    tmp = client.read();
    in += tmp;
  }
  if(in.substring(0, in.length()-1).equals("request")){
    int input[4] = {analogRead(A0), analogRead(A1), 
    analogRead(A2), analogRead(A3)};
    client.println("analog data:");
    client.print("voltage = ");
    client.println(input[0]);
    client.print("current = ");
    client.println(input[1]);
    client.print("reference = ");
    client.println(input[2]);
    client.print("ground = ");
    client.println(input[3]); 
    client.print("milliseconds since powerup = ");
    client.println(millis());
    client.println("end");
  }
}

