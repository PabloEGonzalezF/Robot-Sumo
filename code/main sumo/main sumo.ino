#define TRIG  17
#define ECHO  16
#define TRIG2 4
#define ECHO2 2
#define MD1 5
#define MD2 18
#define MI2 19
#define MI1 21
#define BUTTON_PIN 23

bool codeExecuted = false;  //estas variables se utilizan para poder hacer que es sumo empiece a sentir despues de que el pulsador es presionado//
unsigned long buttonPressTime = 0;

void setup() { //aquí en el void setup se inicializan los pines  anteriormente definidos//                                                                                                                                                         //como entradas o salidas//                                         
   Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);  //low significa apagado así como high encendido, asi como 1 y 0//
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  digitalWrite(TRIG2, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP); //define la resistencia interna del pulsador como pull up//
}

void loop() {  //el void loop es la parte del código que se ejecuta permanentemente//
  if (!codeExecuted) {  //esta parte lo que hace es poner al pin en 0 es decir no a sí presionado para luego con la variable millis ir contando el tiempo //
    if (digitalRead(BUTTON_PIN) == LOW) {
      buttonPressTime = millis();
      codeExecuted = true;
    }
  }

  if (codeExecuted && (millis() - buttonPressTime >= 5000)) { //aqui lo que hacemos es que si el botón ha sido presionado y pasaron los cinco segundo que se ejecute el código "executecode"//
    executeCode();
  }

void executeCode() {
//definimos y calculamos la distancia y la pasamos a cm para el sensor de ultrasonido en base a una cuenta matemática//
  long t;
  long d;
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  t = pulseIn(ECHO, HIGH);
  d = t / 59;

  Serial.print("distancia: ");
  Serial.print(d);
  Serial.println();
  delay(1000);

  long t2;
  long d2;
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);

  t2 = pulseIn(ECHO2, HIGH);
  d2 = t2 / 59;

  Serial.print("distancia2: ");
  Serial.print(d2);
  Serial.println();
  delay(1000);

  if (d >= 10 && d <= 200 && d2 >= 30 && d2 <= 150) {
//si las distancias respetan la siguiente condición se ejecutará el siguiente bloque//
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(MI1, HIGH);
    digitalWrite(MI2, LOW);
    Serial.println(" ataque ");
  } else if (d > 200 && d < 300 && d2 >= 250 && d2 <= 350) {
//si esa condición no se cumple pero si se cumple la siguiente entonces ocurrirá esto//
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
    digitalWrite(MI1, HIGH);
    digitalWrite(MI2, LOW);
    Serial.println(" busqueda ");
  } else {
//y finalmente si nada de eso se cumple ocurrirá lo siguiente//
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(MI1, LOW);
    digitalWrite(MI2, HIGH);
    Serial.println(" busqueda ");
    delay(3000);
  }
}
