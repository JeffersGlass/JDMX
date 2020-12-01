#include <JDMX.h>
#include <Rdm_Defines.h>
#include <Rdm_Uid.h>

#define dmxMaster_CHANNELS    512
#define RXEN_PIN                2

void setup() {
  // put your setup code here, to run once:
  RDM_Uid broadcast;
  broadcast.Initialize_BroadcastID();

  RDM_Uid source;
  source.Initialize(50,1,1,1,1);
  
  DMX_Master d ( dmxMaster_CHANNELS, RXEN_PIN);
  RDM_Controller r = RDM_Controller(source, d);

  delay(1000);

  r.setDMXAddress(100, broadcast);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
