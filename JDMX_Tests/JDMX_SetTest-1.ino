#include <JDMX.h>
#include <Rdm_Defines.h>
#include <Rdm_Uid.h>
#include <Arduino.h>

#define dmxMaster_CHANNELS    512
#define RXEN_PIN                4
#define TXEN_PIN                10
#define LED                     11
#define TRIGGER                 6

RDM_Uid source {0x20, 0xC2, 4, 3, 2, 1};
RDM_Uid dest {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
RDM_Uid bcast {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

DMX_Master d ( dmxMaster_CHANNELS, RXEN_PIN, TXEN_PIN, true);
RDM_Controller r (source, d);

void setup() {
  // put your setup code here, to run once:

  pinMode(LED, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  d.setChannelRange(1, 512, 0);
  d.enable();
  for (int i = 1; i <= 512; i++) {
    d.setChannelValue(i, int(i / 2));
  }
  delay(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  //d.enable();
  delay(1);
  digitalWrite(TRIGGER, HIGH);
  //r.setDMXAddress(400, bcast);
  uint8_t addressData[] = {0, 400};
  r.sendRawCommand(bcast, 0x30, rdm::DmxStartAddress, 0x02, addressData);
  digitalWrite(TRIGGER, LOW);
  delay(50);
  //d.disable();
  delay(50);
  digitalWrite(LED, LOW);
  delay(1000);
}

/*
   Bits/bytes for setDmxAddress:
     START CODE               SC_RDM              0
     xCC
   SUB START CODE             SC_SUB_MESSAGE      0x01
   Message Length                                 0x1A (26)
   Destination UID            Broadcast           0xFFFFFFFFFFFF
   Source UID                 My UID              0x20C2
   Transaction Number                             0x00
   Port ID/Resp Type                              0x00
   Message Count                                  0x00
   Sub Device                                     0x00
   Command Class              Set Command         0x30
   Parameter ID                                   ??
   Parameter Data Length (PDL)                    0x02
   Parameter Data                                 Matches address set
   Checksum High                                  Checksum
   Checksum Low                                   Checksum
*/
