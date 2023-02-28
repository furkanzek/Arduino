#define RCPin 2
int RCValue, RCV;

void setup() {
  Serial.begin(9600);
  pinMode(RCPin, INPUT);
}

void loop() {
  RCValue = pulseIn(RCPin, HIGH);
  RCV = map(RCValue, 1000, 2000, -90, 90);
  Serial.println(RCV);
}
