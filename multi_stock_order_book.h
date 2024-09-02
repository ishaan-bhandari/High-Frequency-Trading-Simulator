#ifndef MULTI_STOCK_ORDER_BOOK_H
#define MULTI_STOCK_ORDER_BOOK_H

#include "order_book.h"
#include <unordered_map>
#include <string>

class MultiStockOrderBook {
private:
    std::unordered_map<std::string, OrderBook> stockOrderBooks;

public:
    void addOrder(const std::string& symbol, const Order& order);
    void matchOrders(const std::string& symbol);
    bool empty(const std::string& symbol) const;
};

#endif
