#pragma once

#include "cstdio"
#include "string"

#include "cpr/cpr.h"

#include "json.hpp"

using nlohmann::json;

class OctoPrintClient {

public:


private:
    std::string APIKey;
    std::string serverURL;

    void GetVersion();

    void GetStatus();

    void ControlPrinthead();

    void ControlTool();

    void ControlBed();

    void GetRequest(const char* route);

    void PostRequest(const char *route);
};