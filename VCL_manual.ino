#include <P1AM.h>

//int inputCounts; //raw ADC count
const int numPaths = 2; //number of independent VCL paths, corresponding to one switch, LED, and relay output to solid-state relay

//switch inputs
int switchPins[numPaths] = {13,14};
int switchStates[numPaths];//used to compare previous reading with current
//relay module channels
int ledChans[numPaths] = {7,8};
int vclChans[numPaths] = {1,5};
int state;

void setup() {
	Serial.begin(19200);
	while (!P1.init()){ 
		; //Wait for Modules to Sign on   
  	}
	for (int i = 0; i <= numPaths - 1; i++) {//zero-indexed arrays
		pinMode(switchPins[i],INPUT);
		setVCL(i,0);//init to off
		switchStates[i] = 0;
	}
}

void loop() {
	//inputCounts = P1.readAnalog(1, 2); //slot 1, chan 2
	for (int i = 0; i <= numPaths - 1; i++){
		state = ~digitalRead(switchPins[i]); //be sure to use pin with internal pullup - switch grounds input
		if (state != switchPins[i]) {
			setVCL(i,state);
			switchStates[i] = state;
		}
	}
delay(50);//crude debounce
}

void setVCL(int path, int state){
	P1.writeDiscrete(state,2,ledChans[path]);
	P1.writeDiscrete(state,2,vclChans[path]);
}
