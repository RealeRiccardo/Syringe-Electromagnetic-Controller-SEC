//CODE TO OPERATE THE SYRINGE ELECTROMAGNETIC CONTROLLER (SEC)

// Define thermistor parameters
#define RT0 5000   // Ω
#define B 3950     // K

// Define input & output pins
int Relay_pin = 3; 
int Thermistor_Pin = A3;

int WAIT_LONG = 1000;
int WAIT_SHORT = 50;

float T_SET = 36.5;
int WAIT_BAT;
float Vrt, Vr, Vcc;
float R = 4700;
float logRT, RT, T, Tc, T0;

int ThermistorPin2 = A5;
float Vrt2, Vr2;
float logRT2, RT2, T2, Tc2, T02;

void setup() {
  Serial.begin(9600);
  pinMode(Relay_pin, OUTPUT);
  Vcc = 3.3;
  T0 = 25 + 273.15; 
}

void loop() {
 
  Vrt = analogRead(Thermistor_Pin);
  Vrt = Vrt * 5 / 1023;
  Vr = Vcc - Vrt;
  RT = Vrt / (Vr / R);
   
  logRT = log(RT/RT0);
  Tc = 1/( (1/T0) + (logRT/B) ); //Temperature from thermistor
  Tc =  Tc - 273.15;                 //Conversion to Celsius


  Vrt2 = analogRead(ThermistorPin2);
  Vrt2 = Vrt2 * 5 / 1023;
  Vr2 = 3.3 - Vrt2;
  RT2 = Vrt2 / (Vr2 / R);
   
  logRT2 = log(RT2/RT0);
  Tc2 = 1/( (1/T0) + (logRT2/B) ); //Temperature from thermistor
  Tc2 =  Tc2 - 273.15+3;                 //Conversion to Celsius
 
  Serial.println("Temperature: ");
  Serial.print(Tc);
  Serial.print("        ");
  Serial.println(Tc2);

  digitalWrite(Relay_pin, HIGH); // Currently no stepper motor movement
  if (Tc<T_SET) {
   delay(WAIT_LONG);          //Wait 1000 milliseconds (1 second) before moving again
  }
  else {
   delay(WAIT_SHORT);         //Wait 1000 milliseconds (1 second) before moving again
  }
  digitalWrite(Relay_pin, LOW);  // Currently no stepper motor movement
  delay(WAIT_LONG);          //Wait 1000 milliseconds (1 second) before moving again
 
 
}