/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include "buttons.h"

uint32_t num_codes[] = {
  BUT_0, BUT_1, BUT_2, BUT_3, BUT_4,
  BUT_5, BUT_6, BUT_7, BUT_8, BUT_9
};

IRsend irsend;

void send_code(uint32_t code) {
  irsend.sendNEC(code, 32);
  delay(100);
}

void send_num(int num) {
  send_code(num_codes[num]);
}

void send_channel(int chan) {
  if(chan > 100) {
    send_num((chan/100)%10);
    chan = chan % 100;
  }
  if(chan > 10) {
    send_num((chan/10)%10);
    chan = chan % 10;
  }
  send_num(chan);
}

boolean isnum(char chr) {
  if(chr >= '0' && chr <= '9') {
    return true;
  } else {
    return false;
  }
}

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  delay(1000);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("Done with setup");
}

void loop() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    if(inputString.startsWith(":") && inputString.length() == 5) {
      if(isnum(inputString[1]) && isnum(inputString[2]) && isnum(inputString[3])) {
        Serial.println("MATCH");
        Serial.println(inputString.length());
        Serial.println(inputString.substring(1,4));
        send_channel(inputString.substring(1,4).toInt());
      } else if(inputString.startsWith(":INF")) {
        send_code(BUT_INFO);
      } else if(inputString.startsWith(":BCK")) {
        send_code(BUT_BACK);
      } else if(inputString.startsWith(":MNU")) {
        send_code(BUT_MENU);
      } else if(inputString.startsWith(":EXT")) {
        send_code(BUT_EXIT);
      } else if(inputString.startsWith(":TXT")) {
        send_code(BUT_TEXT);
      } else if(inputString.startsWith(":REC")) {
        send_code(BUT_REC);
      } else if(inputString.startsWith(":AUP")) {
        send_code(BUT_UP);
      } else if(inputString.startsWith(":ADN")) {
        send_code(BUT_DOWN);
      } else if(inputString.startsWith(":ALT")) {
        send_code(BUT_LEFT);
      } else if(inputString.startsWith(":ART")) {
        send_code(BUT_RIGHT);
      } else if(inputString.startsWith(":OKY")) {
        send_code(BUT_OK);
      } else if(inputString.startsWith(":PLY")) {
        send_code(BUT_PLAYPAUSE);
      } else if(inputString.startsWith(":PAU")) {
        send_code(BUT_PLAYPAUSE);
      } else if(inputString.startsWith(":REW")) {
        send_code(BUT_REW);
      } else if(inputString.startsWith(":FWD")) {
        send_code(BUT_FWD);
      } else if(inputString.startsWith(":STP")) {
        send_code(BUT_STOP);
      } else if(inputString.startsWith(":VUP")) {
        send_code(BUT_VOLPLUS);
      } else if(inputString.startsWith(":VDN")) {
        send_code(BUT_VOLMIN);
      } else if(inputString.startsWith(":MUT")) {
        send_code(BUT_MUTE);
      } else if(inputString.startsWith(":CUP")) {
        send_code(BUT_CHPLUS);
      } else if(inputString.startsWith(":CDN")) {
        send_code(BUT_CHMIN);
      } else if(inputString.startsWith(":RED")) {
        send_code(BUT_RED);
      } else if(inputString.startsWith(":GRN")) {
        send_code(BUT_GREEN);
      } else if(inputString.startsWith(":YEL")) {
        send_code(BUT_YELLOW);
      } else if(inputString.startsWith(":BLU")) {
        send_code(BUT_BLUE);
      }
    } else {
      Serial.println("FAIL");
      Serial.println(inputString.length());
      Serial.println(inputString);
    }
    inputString = "";
    stringComplete = false;
  }
}

