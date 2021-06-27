//#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
//#include <DHT.h>

//Conexion del sensor HC-SR04
const int EchoPin = 12;// D6 pin de disparo
const int TriggerPin =13; //D7 Pin de entrada 

int pir_pin = 14; //d5
int led_pin = 15;//d8
int valed = 1;//valor de led encendido en widget 
int valed2 = 0;//valor de led apagado en widget

//Conexion a sensor DHT
#include "DHT.h"
#define DHTPIN 2     // Pin D4 en Wemos equivale al 2 en Arduino
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

//variables
int contconexion = 0;
int duracion;
int distancia;

const char *ssid = "INFINITUMkw7y";
const char *password = "ce184574b0";

unsigned long previousMillis = 0;

char host[48];
String strhost = "192.168.1.65";
//String strhost = "localhost:3000"; //IP del Server
String strurl = "/add"; //URL
String chipid = "";

//funcion para insertar datos

String enviardatos(String datos) {
  Serial.print(datos);
  String linea = "error";
  WiFiClient client;
  strhost.toCharArray(host, 49);
  if (!client.connect(host, 3000)) {
    Serial.println("Fallo de conexion al servidor");
    return linea;
  }

  client.print(String("POST ") + strurl + " HTTP/1.1" + "\r\n" + 
               "Host: " + strhost + "\r\n" +
               "Accept: */*" + "*\r\n" +
               "Content-Length: " + datos.length() + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
               "\r\n" + datos);           
  delay(10);             
  
  Serial.print(" Enviando datos al APIRest...");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("No conectado con el cliente");
      client.stop();
      return linea;
    }
  }
  // imprime las lineas que recibe del servidor
  while(client.available()){
    linea = client.readStringUntil('\r');
  }  
  Serial.println(linea);
  return linea;
}

//-------------------------------------------------------------------------

void setup() {
 // Inicia Serial
  Serial.begin(115200);
  Serial.println("");
  // Iniciamos DHT
  dht.begin();
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
   delay(1000);

  Serial.print("chipId: "); 
  chipid = String(ESP.getChipId());
  Serial.println(chipid); 

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //50 intentos para conectar  si no lo cancela
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
     // IPAddress ip(192, 168, 43, 5); 
     // IPAddress gateway(192, 168, 43, 1); 
     // IPAddress subnet(255, 255, 255, 0); 
     // WiFi.config(ip, gateway, subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado con la IP ");
      Serial.println(WiFi.localIP());
      
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion al wifi");  
  } 
}

//--------------------------LOOP--------------------------------
void loop() {

   /////PIR
  if(digitalRead(pir_pin) == HIGH)
  {
    digitalWrite(led_pin, HIGH);
    //Serial.print("Led", valed);
    Serial.println("Se ha detectado Movimiento");
    //delay(10000);
    //digitalWrite(led_pin, LOW);
  }
  /*else
  {
    digitalWrite(led_pin, LOW);
    //Serial.print("Led", valed2);
    Serial.println("No se ha detectado Movimiento");
  }*/
  
  //Iniciamos el envio de valores del ultrasonico
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duracion = pulseIn(TriggerPin, HIGH);
  distancia = duracion / 58;
  
 // Leemos datos del DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  delay(1000);
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 10000) { //envia la temperatura cada 10 segundos
    previousMillis = currentMillis;

   /* Serial.println("Distancia: ");
    Serial.println(distancia);*/
    //Serial.println(t);
    //enviardatos("Temperatura=" + String(t) + "ºC " + "&Humedad=" + String(h)+ "% " + "&Distancia=" + String(15)+ "Cm " + "&Crecimiento=" + String(valed++)+ "Dc ");
    enviardatos("Temperatura=" + String(t) + "&Humedad=" + String(h) + "&Distancia=" + String(distancia) + "&Crecimiento=" + String(valed++));
  }
}
