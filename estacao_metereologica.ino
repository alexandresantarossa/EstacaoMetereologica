#include <DHT.h> //UMIDADE
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(2,DHT22); // Declara objeto do tipo DHT //UMIDADE
Adafruit_BMP280 bmp; // Declara objeto do tipo BMP //PRESSÃO

int bin, bin_lum; float tensao_lm35, temp_lm35, umid, temp_dht, press, temp_bmp280, alt, tensao_lum, res_lum, lum; // Declara variáveis 

void setup()
{
Serial.begin(9600); // Inicializa serial
analogReference(INTERNAL); // Fundo escala 1,1 V
dht.begin(); // Inicializa objeto dht
bmp.begin(0x76); // Inicializa objeto BMP
lcd.init(); // Inicializa LCD
lcd.backlight(); // Liga luz do LCD

lcd.setCursor(0,0);
lcd.print("ESTACAO");
lcd.setCursor(0,1);
lcd.print("METEREOLOGICA");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("GRUPO: ISABELLA,");
lcd.setCursor(0,1);
lcd.print("GUSTAVO E");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ALEXANDRE");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("INSTRUMENTACAO");
lcd.setCursor(0,1);
lcd.print("E MEDICAO");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("TURMA A2");
delay(2000);
lcd.clear();
}

void loop() {
  
//LM35  
bin = analogRead(A0); // Lê valor binário
tensao_lm35 = (bin/1023.0)*1.1; // Converte em tensão
temp_lm35 = (tensao_lm35*100.0730893) +0.133495463; // Converte em temp.
Serial.print("\n\nTensão LM35 [V]: ");
Serial.print(tensao_lm35);
Serial.print("\nTemperatura [C]: ");
Serial.print(temp_lm35); // Exibe temperatura

lcd.setCursor(0,0);
lcd.print("TEMPERATURA [C]:");
lcd.setCursor(0,1);
lcd.print(temp_lm35);
delay(5000);
lcd.clear();

delay(2000);

umid = dht.readHumidity(); // Lê umidade
temp_dht = dht.readTemperature(); // Lê temperatura
umid = umid * 1.205039024 - 10.97803763; // Calibração
Serial.print("\nUmidade [%]: ");
Serial.print(umid); // Exibe umidade

lcd.setCursor(0,0);
lcd.print("UMIDADE [%]");
lcd.setCursor(0,1);
lcd.print(umid);
delay(5000);
lcd.clear();

delay(2000);


press = bmp.readPressure(); // Lê pressão
temp_bmp280 = bmp.readTemperature();// Lê temperatura
alt= bmp.readAltitude(1013.25); // Altitude em metros
Serial.print("\nPressão [hPa]: ");
Serial.print(press/100); // Exibe pressão
Serial.print("\nAltitude [m]: ");
Serial.print(alt); // Exibe pressão

lcd.setCursor(0,0);
lcd.print("PRESSAO[hPa]:");
lcd.setCursor(0,1);
lcd.print(press/100);
delay(5000);
lcd.clear();

delay(2000);

lcd.setCursor(0,0);
lcd.print("ALTITUDE [m]:");
lcd.setCursor(0,1);
lcd.print(alt);
delay(5000);


delay(2000);


bin_lum = analogRead(A1); // Lê binário
tensao_lum = (bin_lum/1023.0)*1.1; // Calc. tensão
res_lum = tensao_lum*100000.0/(5.0-tensao_lum); // Calc. resist.
lum = pow(10,6.5-1.25*log10(res_lum)); // Calc. lumnos.
Serial.print("\nResitência LDR: ");
Serial.print(res_lum); // Exibe luminosidade
Serial.print("\nLuminosidade [Lux]: ");
Serial.print(lum); // Exibe luminosidade

lcd.setCursor(0,0);
lcd.print("LUMINOSIDADE:");
lcd.setCursor(0,1);
lcd.print(lum);
delay(5000);

lcd.clear();
delay(2000);

}
