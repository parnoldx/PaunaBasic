#pragma once

#include <WebServer.h>
#include <DNSServer.h>
#include "Config.h"
#include "HTMLContent.h"

class WebConfig {
public:
    WebConfig();
    void init();
    void handleClient();
    void stop();
    
private:
    WebServer server;
    DNSServer dnsServer;
    
    void setupRoutes();
    void handleRoot();
    void handleGetValues();
    void handleGetReading();
    void handleSetCalibration();
    void handleSetStandby();
    void handleFinish();
    
    const char* getHtmlContent();
};