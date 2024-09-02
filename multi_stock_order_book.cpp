#include "multi_stock_order_book.h"

void MultiStockOrderBook::addOrder(const std::string& symbol, const Order& order) {
    stockOrderBooks[symbol].addOrder(order);
}

void MultiStockOrderBook::matchOrders(const std::string& symbol) {
    stockOrderBooks[symbol].matchOrders();
}

bool MultiStockOrderBook::empty(const std::string& symbol) const {
    auto it = stockOrderBooks.find(symbol);
    if (it != stockOrderBooks.end()) {
        return it->second.empty();
    }
    return true;
}
