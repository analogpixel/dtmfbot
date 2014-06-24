// The library toggles digital pin 4 in the sampling loop which allows
// measurement of the actual sampling frequency.
// If you call .sample() continuously like this:
// while(1)dtmf.sample(sensorPin);
// you can put a frequency counter on pin 4 to determine what the
// sampling frequency is on your Arduino. Note that the frequency
// counter will show half the actual rate. My meter showed 4.463kHz
// so the sampling rate is 8926Hz
#include <DTMF.h>

class DTMF
{
  // user-accessible "public" interface
  public:
    DTMF(float,float);
    DTMF(float);
void sample(int);
void detect(float dtmf_mag[],int adc_centre);
char button(float mags[],float magnitude);
  // library-accessible "private" interface
  private:

//El_Supremo change to int
void ProcessSample(int,int);
void ResetDTMF(void);

};

int sensorPin = A0;

// NOTE that N MUST NOT exceed 160
// This is the number of samples which are taken in a call to
// .sample. The smaller the value of N the wider the bandwidth.
// For example, with N=128 at a sample rate of 8926Hz the tone
// detection bandwidth will be 8926/128 = 70Hz. If you make N
// smaller, the bandwidth increases which makes it harder to detect
// the tones because some of the energy of one tone can cross into
// an adjacent (in frequency) tone. But a larger value of N also means
// that it takes longer to collect the samples.
// A value of 64 works just fine, as does 128.
// NOTE that the value of N does NOT have to be a power of 2.
float n=128.0;
// sampling rate in Hz
float sampling_rate=8926.0;

// Instantiate the dtmf library with the number of samples to be taken
// and the sampling rate.
DTMF dtmf = DTMF(n,sampling_rate);

void setup(){
 

 pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  
Serial.begin(115200);
}

int nochar_count = 0;
float d_mags[8];

void loop()
{
  clearPins();
  char thischar;
  
  // This reads N samples from sensorpin (must be an analog input)
  // and stores them in an array within the library. Use while(1)
  // to determine the actual sampling frequency as described in the
  // comment at the top of this file
  /* while(1) */
  
  dtmf.sample(sensorPin);
  
  // The first argument is the address of a user-supplied array
  // of 8 floats in which the function will return the magnitudes
  // of the eight tones.
  // The second argument is the value read by the ADC when there
  // is no signal present. A voltage divider with precisely equal
  // resistors will presumably give a value of 511 or 512.
  // My divider gives a value of 506.
  // If you aren't sure what to use, set this to 512

  //dtmf.detect(d_mags,506);
  dtmf.detect(d_mags,0);
  
  // detect the button
  // If it is recognized, returns one of 0123456789ABCD*#
  // If unrecognized, returns binary zero

  // Pass it the magnitude array used when calling .sample
  // and specify a magnitude which is used as the threshold
  // for determining whether a tone is present or not
  //
  // If N=64 magnitude needs to be around 1200
  // If N=128 the magnitude can be set to 1800
  // but you will need to play with it to get the right value
  thischar = dtmf.button(d_mags,1800);
  
  if (thischar) {
    if (thischar == '3') {
      forewards(1000);
      Serial.print("Foreward\n");
    }
    if (thischar == '4') {
      backwards(1000);
      Serial.print("Backward\n");
    }
    if (thischar == '5') {
      turnRight(250);
      Serial.print("Right\n");
    }
    
    if(thischar=='6') {
      turnLeft(250);
      Serial.print("Left\n");
    }
    
  }
  
}

void clearPins() {
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);  
}

void turnRight(int ms) {
  clearPins();
  digitalWrite(7, HIGH);
  digitalWrite(3, HIGH);
  delay(ms);
  clearPins();
}

void turnLeft(int ms) {
  clearPins();
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  delay(ms);
  clearPins();
}


void backwards(int ms) {
  clearPins();
  digitalWrite(6, HIGH); // left wheel back
  digitalWrite(3, HIGH); // right wheel back
  delay(ms);
  clearPins();
}

void forewards(int ms) {
  clearPins();
  
  digitalWrite(7, HIGH); // left wheel forward
  digitalWrite(5, HIGH); // right wheel forward
  delay(ms);
  
  clearPins();
}

