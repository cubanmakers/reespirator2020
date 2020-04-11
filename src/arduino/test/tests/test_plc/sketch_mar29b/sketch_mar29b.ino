void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(57200);
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long time = millis();
  if (millis() > time + 50) {
    time = millis();
    static int pres1 = 940;
    static int pres2 = 1012;
    static int vol = 5;
    static int flujo = 10;
    char* str = malloc(100);
      sprintf(str, "DT %05d %05d %05d %06d", (pres1), (pres2), vol, flujo);
        Serial2.println(str);
        Serial.println(str);
        free(str);
    pres1 += ((random() % 80)-40);
    pres2 += (random() % 80) -40;
    vol += (random() % 5);
    //flujo =+ (random() % 100) - 50;
    flujo++;
  }

}
