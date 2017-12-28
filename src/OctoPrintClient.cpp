#include "OctoPrintClient.h"

void OctoPrintClient::GetVersion() {
    GetRequest("/api/version");
}

void OctoPrintClient::GetStatus() {
    GetRequest("/api/printer");
}

void OctoPrintClient::ControlPrinthead() {
    PostRequest("/api/printer/printhead");
}

void OctoPrintClient::ControlTool() {
    PostRequest("/api/printer/tool");
}

void OctoPrintClient::ControlBed() {
    PostRequest("/api/printer/bed");
}

void OctoPrintClient::GetRequest(const char *route) {
    cpr::GetAsync(cpr::Url{serverURL + route},
                  cpr::Header{{"X-Api-Key", APIKey}});
}

void OctoPrintClient::PostRequest(const char *route) {
    cpr::PostAsync(cpr::Url{serverURL + route},
                   cpr::Header{{"X-Api-Key", APIKey}});
}