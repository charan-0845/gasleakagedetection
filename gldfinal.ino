#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h> // ✅ ESP32-compatible Servo library

// **WiFi and Firebase Credentials**
const char* ssid = "KSR";     
const char* password = "12345678";
#define FIREBASE_HOST "https://#######.firebaseio.com"
#define FIREBASE_PATH "/alerts.json"
#define FIREBASE_AUTH "######"

// **Telegram Bot Credentials**
const char* botToken = "7#####";
const char* chatID = "#####";

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);
LiquidCrystal_PCF8574 lcd(0x27);

// **Predefined Location Link**
const char* locationLink = "https://maps.google.com/?q=17.395498775982773,78.62198948297176";

// **Pin Assignments**
#define MQ5_SENSOR 34
#define GREEN_LED  26
#define RED_LED    25
#define BUZZER     27
#define SERVO_PIN  14  // ✅ PWM-capable pin on ESP32 for servo

// **Gas Thresholds**
#define WARNING_THRESHOLD 350  
#define ALERT_THRESHOLD   800  

// **Flags and Timers**
bool alertSent = false;
bool servoActivated = false;  // ✅ Prevent repeated servo trigger
unsigned long lastTelegramCheck = 0;
const long telegramCheckInterval = 2000;

// ✅ Servo setup
Servo tripServo;

void setup() {
    Serial.begin(115200);
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.setCursor(0, 0);
    lcd.print("Gas Guard");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi...");

    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    delay(2000);
    
    client.setInsecure();

    pinMode(MQ5_SENSOR, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Safe:No Gas Leak");

    // ✅ Initialize Servo
    tripServo.setPeriodHertz(50);                // Standard 50Hz for servo
    tripServo.attach(SERVO_PIN, 500, 2400);      // Min/max pulse width in µs
    tripServo.write(0);                          // Initial position
}

void loop() {
    int gasValue = analogRead(MQ5_SENSOR);
    Serial.print("Gas Level: ");
    Serial.println(gasValue);
    
    lcd.setCursor(0, 1);
    lcd.print("Gas Level: ");
    lcd.print(gasValue);
    lcd.print("    ");
    
    if (gasValue > ALERT_THRESHOLD && !alertSent) {
        sendFirebaseAlert();
        alertSent = true;

        

        // **Critical Gas Leak Detected**
        lcd.setCursor(0, 0);
        lcd.print("ALERT:HIGH LEAK!");
        
        digitalWrite(GREEN_LED, LOW);
        for (int i = 0; i < 5; i++) {
            digitalWrite(RED_LED, HIGH);
            digitalWrite(BUZZER, HIGH);
            delay(500);
            digitalWrite(RED_LED, LOW);
            delay(500);
        }
        digitalWrite(BUZZER, HIGH);
        bot.sendMessage(chatID, "🚨 ALERT: HIGH Gas Leak Detected! Take Immediate Action!", "");
        // ✅ Trigger Servo (if not already triggered)
        if (!servoActivated) {
            tripServo.write(30); // Rotate to 90°
            delay(1000);         // Wait for servo to move
            tripServo.write(0);  // Optional: return to initial
            servoActivated = true;
        }
    } 
    else if (gasValue > WARNING_THRESHOLD) {
        // **Moderate Gas Leak Detected**
        lcd.setCursor(0, 0);
        lcd.print("WARNING:GAS LEAK!");
        
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        for (int i = 0; i < 3; i++) {
            digitalWrite(BUZZER, HIGH);
            delay(300);
            digitalWrite(BUZZER, LOW);
            delay(300);
        }
        bot.sendMessage(chatID, "⚠️ WARNING: Moderate Gas Leak Detected!", "");
    } 
    else {
        // **Safe Condition**
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Safe:No Gas Leak ");
        
        alertSent = false;       // Reset alert flag
        servoActivated = false;  // ✅ Allow servo to retrigger next time
    }
    
    // **Check for Telegram Messages Every 2 Sec**
    if (millis() - lastTelegramCheck > telegramCheckInterval) {
        checkTelegramMessages();
        lastTelegramCheck = millis();
    }

    delay(1000);
}

// **Function to Send Alert to Firebase**
void sendFirebaseAlert() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String firebaseURL = String(FIREBASE_HOST) + FIREBASE_PATH + "?auth=" + FIREBASE_AUTH;
        
        http.begin(firebaseURL);
        http.addHeader("Content-Type", "application/json"); 

        StaticJsonDocument<200> doc;
        doc["alert"] = "🚨 Gas Leak Detected!";
        doc["location"] = locationLink;

        String requestBody;
        serializeJson(doc, requestBody);

        int httpResponseCode = http.POST(requestBody);

        if (httpResponseCode > 0) {
            Serial.println("✅ Alert sent to Firebase!");
        } else {
            Serial.print("❌ Firebase error: ");
            Serial.println(http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("⚠️ Wi-Fi Disconnected!");
    }
}

// **Function to Handle Telegram Requests**
void checkTelegramMessages() {
    int messageCount = bot.getUpdates(bot.last_message_received + 1);

    while (messageCount) {
        for (int i = 0; i < messageCount; i++) {
            String userChatID = bot.messages[i].chat_id;
            String text = bot.messages[i].text;

            if (text == "/gaslevel") {
                int gasLevel = analogRead(MQ5_SENSOR);
                bot.sendMessage(userChatID, "📡 Gas Level: " + String(gasLevel), "");
            }
        }
        messageCount = bot.getUpdates(bot.last_message_received + 1);
    }
}
