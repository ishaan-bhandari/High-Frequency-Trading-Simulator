#include "order_book.h"

void OrderBook::addOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (order.type == BUY) {
        buyOrders.push(order);
    } else {
        sellOrders.push(order);
    }
}
