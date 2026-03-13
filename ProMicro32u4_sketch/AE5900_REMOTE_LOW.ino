/* 
 * AE 5900 REMOTE INTERFACE - FINAL STABLE VERSION
 * Konfiguration: 40 Kanäle Standard, 300s PTT Timeout
 */

const int PIN_DOWN    = 2;
const int PIN_UP  = 3;
const int PIN_MODE  = 4;
const int PIN_PTT   = 5; 
const int PIN_LED   = 13; 

// Status-Variablen
int currentMode = 0; // 0=PA, 1=CW, 2=FM, 3=AM, 4=USB, 5=LSB
int currentCH   = 1;
int maxChannels = 40; // Standard auf 40 Kanäle (Schweiz/EU) gesetzt

unsigned long pttStartTime = 0;
unsigned long pttTimeoutMs = 300000; // Standard 300 Sek (5 Min)
unsigned long lastHeartbeat = 0;

bool pttActive = false;

void setup() {
  pinMode(PIN_UP, OUTPUT);
  pinMode(PIN_DOWN, OUTPUT);
  pinMode(PIN_MODE, OUTPUT);
  pinMode(PIN_PTT, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  
 
  digitalWrite(PIN_PTT, LOW);
  
  Serial.begin(9600);
}


void pulsePin(int pin, int ms) {
  digitalWrite(pin, HIGH);
  digitalWrite(PIN_LED, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
  digitalWrite(PIN_LED, LOW);
  delay(ms); 
}


void sendFullStatus() {
  Serial.print("STATUS|CH:"); Serial.print(currentCH);
  Serial.print("|MODE:"); Serial.print(currentMode);
  Serial.print("|MAX:"); Serial.print(maxChannels);
  Serial.print("|PTT:"); Serial.println(pttActive ? "ON" : "OFF");
}

void loop() {
  
  if (pttActive && pttStartTime > 0 && (millis() - pttStartTime > pttTimeoutMs)) {
    pttActive = false;
    digitalWrite(PIN_PTT, LOW);
    sendFullStatus(); 
    pttStartTime = 0; 
  }

  if (Serial.available() > 0) {
    char cmd = Serial.read();

    switch (cmd) {
      lastHeartbeat = millis(); 
      case 'U': // Up
        pulsePin(PIN_UP, 100);
        currentCH++;
        if (currentCH > maxChannels) currentCH = 1;
        break;

      case 'D': // Down
        pulsePin(PIN_DOWN, 100);
        currentCH--;
        if (currentCH < 1) currentCH = maxChannels;
        break;

      case 'M': // Mode
        pulsePin(PIN_MODE, 150); 
        currentMode = (currentMode + 1) % 6;
        break;

      case 'P': 
        pttActive = !pttActive;
        if (pttActive) {
          digitalWrite(PIN_PTT, HIGH); 
          pttStartTime = millis();     
        } else {
          digitalWrite(PIN_PTT, LOW);  
          pttStartTime = 0;            
        }
        break;

      case 'S': // Sync
        currentCH = 1;
        currentMode = 0;
        break;

      case 'C': // Region Toggle 40/80
        maxChannels = (maxChannels == 40) ? 80 : 40;
        if (currentCH > maxChannels) currentCH = 1;
        break;
        
      case 'T': // Timeout setzen (Bsp: T60)
        long seconds = Serial.parseInt(); 
        if (seconds > 0 && seconds <= 600) { 
          pttTimeoutMs = seconds * 1000;
        }
        break;

      case 'G': // Get Status (für Web-Reload)
        
        break;
    }
    
    
    sendFullStatus();
  }
}
