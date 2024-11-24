#include "WebConfig.h"
#include "Storage.h"
#include "Scale.h"

extern Scale scale;

WebConfig::WebConfig() : server(80) {}

void WebConfig::init() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPdisconnect(false);
    IPAddress apIP(192, 168, 4, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("Pauna Scale Setting");
    
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    setupRoutes();
    server.begin();
}

void WebConfig::setupRoutes() {
    server.on("/", HTTP_GET, std::bind(&WebConfig::handleRoot, this));
    server.on("/getValues", HTTP_GET, std::bind(&WebConfig::handleGetValues, this));
    server.on("/get-reading", std::bind(&WebConfig::handleGetReading, this));
    server.on("/setCalibration", HTTP_GET, std::bind(&WebConfig::handleSetCalibration, this));
    server.on("/setStandby", HTTP_GET, std::bind(&WebConfig::handleSetStandby, this));
    server.on("/finish", HTTP_GET, std::bind(&WebConfig::handleFinish, this));
    server.onNotFound(std::bind(&WebConfig::handleRoot, this));
}

void WebConfig::handleClient() {
    dnsServer.processNextRequest();
    server.handleClient();
}

void WebConfig::handleRoot() {
    server.send(200, "text/html", index_html);
}

void WebConfig::handleGetValues() {
    int standby = Storage::loadStandby();
    String json = "{\"standby\":" + String(standby) + "}";
    server.send(200, "application/json", json);
}

void WebConfig::handleGetReading() {
    while (!scale.update());
    float weight = scale.getData();
    int weightAsInt = int(weight + 0.5);
    char weightAsString[6] = {0};
    dtostrf(weightAsInt, 5, 0, weightAsString);
    server.send(200, "application/json", "{\"reading\":" + String(weightAsString) + "}");
}

void WebConfig::handleSetCalibration() {
    if (server.hasArg("weight")) {
        float weight = server.arg("weight").toFloat();
        scale.refreshDataSet();
        float calibrationValue = scale.getNewCalibration(weight);
        
        Storage::saveCalibration(calibrationValue);
        
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Missing weight parameter");
    }
}

void WebConfig::handleSetStandby() {
    if (server.hasArg("minutes")) {
        int minutes = server.arg("minutes").toInt();
        Storage::saveStandby(minutes);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Missing minutes parameter");
    }
}

void WebConfig::handleFinish() {
    server.send(200, "text/plain", "OK");
    stop();
    ESP.restart();
}

void WebConfig::stop() {
    dnsServer.stop();
    server.stop();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
}