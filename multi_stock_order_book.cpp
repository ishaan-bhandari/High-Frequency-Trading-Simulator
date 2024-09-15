#include "multi_stock_order_book.h"

void MultiStockOrderBook::addOrder(const std::string& symbol, const Order& order) {
    if (stockOrderBooks.find(symbol) == stockOrderBooks.end()) {
        stockOrderBooks.emplace(symbol, OrderBook());
    }
    stockOrderBooks[symbol].addOrder(order);
    Logger::log("Added order " + std::to_string(order.id) + " for stock " + symbol);
}

void MultiStockOrderBook::matchOrders(const std::string& symbol) {
    stockOrderBooks[symbol].matchOrders();
    Logger::log("Matched orders for stock " + symbol);
}

bool MultiStockOrderBook::empty(const std::string& symbol) const {
    auto it = stockOrderBooks.find(symbol);
    if (it != stockOrderBooks.end()) {
        return it->second.empty();
    }
    return true;
}

void MultiStockOrderBook::cancelOrder(const std::string& symbol, int orderId) {
    if (stockOrderBooks.find(symbol) != stockOrderBooks.end()) {
        stockOrderBooks[symbol].cancelOrder(orderId);
        Logger::log("Cancelled order " + std::to_string(orderId) + " for stock " + symbol);
    }
}

void MultiStockOrderBook::modifyOrder(const std::string& symbol, int orderId, double newPrice, int newQuantity) {
    if (stockOrderBooks.find(symbol) != stockOrderBooks.end()) {
        stockOrderBooks[symbol].modifyOrder(orderId, newPrice, newQuantity);
        Logger::log("Modified order " + std::to_string(orderId) + " for stock " + symbol);
    }
}
