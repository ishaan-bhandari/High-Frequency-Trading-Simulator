#ifndef MULTI_STOCK_ORDER_BOOK_H
#define MULTI_STOCK_ORDER_BOOK_H

#include "order_book.h"
#include "thread_pool.h"
#include <unordered_map>
#include <string>
#include "alpaca_api.h"

class MultiStockOrderBook {
private:
    std::unordered_map<std::string, OrderBook> stockOrderBooks;

public:
    MultiStockOrderBook() = default;
    void addOrder(const std::string& symbol, const Order& order);
    void matchOrders(const std::string& symbol);
    bool empty(const std::string& symbol) const;
    void cancelOrder(const std::string& symbol, int orderId);
    void modifyOrder(const std::string& symbol, int orderId, double newPrice, int newQuantity);
    bool empty() const;
};

#endif