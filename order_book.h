#include <unordered_map>
#include "order.h"
#include "logger.h"

class OrderBook {
private:
    std::priority_queue<Order> buyOrders;
    std::priority_queue<Order> sellOrders;
    std::unordered_map<int, Order> orderMap;
    mutable std::mutex bookMutex;

public:
    void addOrder(const Order& order);
    void matchOrders();
    void cancelOrder(int orderId);
    void modifyOrder(int orderId, double newPrice, int newQuantity);
    bool empty() const;
};

void OrderBook::cancelOrder(int orderId) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (orderMap.find(orderId) != orderMap.end()) {
        orderMap.erase(orderId);
        Logger::log("Cancelled Order: " + std::to_string(orderId));
    }
}

void OrderBook::modifyOrder(int orderId, double newPrice, int newQuantity) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (orderMap.find(orderId) != orderMap.end()) {
        orderMap[orderId].price = newPrice;
        orderMap[orderId].quantity = newQuantity;
        Logger::log("Modified Order: " + std::to_string(orderId));
    }
}
