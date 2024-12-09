#include <WiFi.h>
#include <WebServer.h>

//#include "esp_wpa2.h"
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_eap_client.h>

IPAddress local_IP(192, 168, 0, 175); // Nurodykite norimą IP adresą
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "DIR-825-C953";
const char* password = "65000010";

const char* ssid_2 = "Redmi";
const char* password_2 = "65000010";

const char* ssid_3 = "VGTU";
const char* username_3 = "20233064";
const char* password_3 = "Vilniustech@eu.1";

WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(5000);
        Serial.print(".");
        if (WiFi.status() != WL_CONNECTED){
          WiFi.begin(ssid_2, password_2);
          delay(5000);
        }
        if (WiFi.status() != WL_CONNECTED){
          //WiFi.disconnect(true);
          WiFi.mode(WIFI_STA);
          esp_eap_client_set_identity((uint8_t*)username_3, strlen(username_3));
          esp_eap_client_set_username((uint8_t*)username_3, strlen(username_3));
          esp_eap_client_set_password((uint8_t*)password_3, strlen(password_3));
          esp_wifi_sta_enterprise_enable();
          WiFi.begin(ssid_3);
          delay(5000);
        }
    }
    Serial.println("\nWiFi prisijungta!");
    Serial.println(WiFi.localIP());

    // Priskirk POST ir OPTIONS
    server.on("/data", HTTP_POST, handlePostData);
    server.on("/data", HTTP_OPTIONS, handleOptions);

    server.begin();
    Serial.println("Serveris paleistas!");
}

void loop() {
    server.handleClient();
}


void handlePostData() {
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        Serial.println("Gauti POST duomenys: " + body);
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "text/plain", "POST užklausa gauta!");
    } else {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(400, "text/plain", "Klaida: nėra POST duomenų.");
    }
}

// Deklaracija
void handleOptions() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.send(204); // 204 No Content
}