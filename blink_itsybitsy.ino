#include <Adafruit_DotStar.h>
Adafruit_DotStar m4dot(1, 8, 6, DOTSTAR_BRG);

#define HBLEDPIN 13
#define HBPERIOD 4000000u
#define HBDUTY   (HBPERIOD / 10u)

// Simulated ISR for LED heartbeat
void heartbeat()
{
	static unsigned int t = HBPERIOD;  // start high

	if (t == HBPERIOD) {
		// Rising edge at start/end of period
		digitalWrite(HBLEDPIN, HIGH);
		t = 0;
	} else if (t == HBDUTY) {
		// Falling edge at end of duty cycle
		digitalWrite(HBLEDPIN, LOW);
	}
	++t;
}

void setup()
{
	m4dot.begin();
	m4dot.show();  // ItsyBitsy M4 DotStar LED = off
	pinMode(HBLEDPIN, OUTPUT);
}

void loop()
{
	heartbeat();
	// Do other work here (which will slow down the heartbeat)
}
