#include "alpaca_api.h"
#include <iostream>

AlpacaAPI::AlpacaAPI(const std::string& apiKey, const std::string& secretKey)
    : apiKey(apiKey), secretKey(secretKey), baseURL("https://paper-api.alpaca.markets/v2") {}

std::string AlpacaAPI::makeRequest(const std::string& url, const std::string& method, const std::string& payload) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (apiKey + ":" + secretKey).c_str());

        if (!payload.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, std::string* userp) {
            userp->append((char*)contents, size * nmemb);
            return size * nmemb;
        });

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}
std::string AlpacaAPI::getRealTimePrice(const std::string& symbol) {
    std::string url = baseURL + "/assets/" + symbol;
    return makeRequest(url, "GET");
}

void AlpacaAPI::placeOrder(const std::string& symbol, int qty, const std::string& side, double price) {
    std::string url = baseURL + "/orders";
    std::string payload = "{\"symbol\":\"" + symbol + "\", \"qty\":" + std::to_string(qty) +
                          ", \"side\":\"" + side + "\", \"type\":\"limit\", \"limit_price\":" + std::to_string(price) +
                          ", \"time_in_force\":\"gtc\"}";

    makeRequest(url, "POST", payload);
}
