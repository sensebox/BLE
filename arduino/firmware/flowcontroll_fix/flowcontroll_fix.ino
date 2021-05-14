#include <senseBoxIO.h>
#include <phyphoxBle.h>

void send_cmd(char *cmd)
{
  Serial.println(cmd);
  Serial.print(": ");

  Serial3.print(cmd);
  Serial3.write('\r');
  Serial3.flush();

  delay(1000);
  while(Serial3.available()){ Serial.write(Serial3.read()); }
  Serial.println("");
}

void setup()
{
  senseBoxIO.powerXB1(false); // power off

  Serial.begin(115200);
  while(!Serial); // wait for serial monitor
  Serial.println("--- START ---");

  senseBoxIO.powerXB1(true);  // power on

  //----------------------------------------------
  //einmalig ausführen
  delay(2000);
  Serial3.begin(115200);
  send_cmd("AT+GMR"); //version
  send_cmd("AT+CGMR"); //version
  send_cmd("AT+UMRS=115200,2,8,1,1"); //flow_control aus
  //send_cmd("AT+UMRS?");
  send_cmd("AT&W0"); //speichern
  send_cmd("AT+CPWROFF"); //neustarten
  delay(2000);
  //----------------------------------------------

  PhyphoxBLE::start("senseBox MCU"); //Start the BLE server
}

void loop()
{
	float randomNumber = random(0,100); //Generate random number in the range 0 to 100
	PhyphoxBLE::write(randomNumber);     //Send value to phyphox

  PhyphoxBLE::poll();
}
