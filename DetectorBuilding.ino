/*
  Nathan Elias
  LASA Science Olympiad
  Detector Building
*/

//Assigning LEDs
int red = 13;
int green = 12;
int blue = 11;

int thermistor = A0; //Declares thermistor pin
float voltage = 0; //Declares voltage

#define SAMPLES 20 //Number of loops
int samples[SAMPLES]; //Declares array of size numSamples

//Defining values for temperature calculation
float resistor = 10000;

//Set up function, starts things up
void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  analogReference(EXTERNAL); //Declares reference voltage
  Serial.begin(9600); //Begins serial monitor
}

//Loop function, "main" function
void loop() {

  //For temperature
  int i;
  float resistance = 0;
  
  for (i = 0; i< SAMPLES; i++) { //Reads thermistor value numSamples times
    samples[i] = analogRead(thermistor);
    resistance += samples[i];
  }

  resistance /= SAMPLES; //Calculates average

  //Formula to calculate resistance
  resistance = 1023 / resistance - 1;
  resistance = resistor / resistance;

  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.print("\t");

  //For voltage
  voltage = 3.3 * (resistance / (10000 + resistance));//Voltage divider equation
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("\t");

  //Formula to create temperature
  float temperature;
  temperature = 75.913*(pow (M_E, -1*(pow(10, -4))*resistance )); //Conversion formula to calculate temperature(degrees celsius) from resistance, which is calculated from voltage 
  
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print(" *C\n");

  if(temperature > 0 && temperature < 25){
    digitalWrite(red, HIGH); 
    digitalWrite(blue, LOW); 
    digitalWrite(green, LOW);  
  }
  else if(temperature > 25 && temperature < 30){
    digitalWrite(green, HIGH); 
    digitalWrite(blue, LOW); 
    digitalWrite(red, LOW);  
  }
  else if(temperature > 30){
    digitalWrite(blue, HIGH); 
    digitalWrite(green, LOW); 
    digitalWrite(red, LOW);  
  }
  else{
    digitalWrite(green, LOW); 
    digitalWrite(blue, LOW); 
    digitalWrite(red, LOW);  
  }
  
  delay(800);
}
