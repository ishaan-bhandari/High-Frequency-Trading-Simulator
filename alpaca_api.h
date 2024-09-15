#ifndef ALPACA_API_H
#define ALPACA_API_H

#include <string>
#include <curl/curl.h>

class AlpacaAPI {
public:
    AlpacaAPI(const std::string& apiKey, const std::string& secretKey);
    std::string getRealTimePrice(const std::string& symbol);
    void placeOrder(const std::string& symbol, int qty, const std::string& side, double price);

private:
    std::string apiKey;
    std::string secretKey;
    std::string baseURL;

    std::string makeRequest(const std::string& url, const std::string& method, const std::string& payload = "");
};

#endif
