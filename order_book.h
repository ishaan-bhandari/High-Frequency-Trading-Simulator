#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "order.h"
#include <queue>
#include <mutex>

class OrderBook {
private:
    std::priority_queue<Order> buyOrders;
    std::priority_queue<Order> sellOrders;
    std::mutex bookMutex;

public:
    void addOrder(const Order& order);
    void matchOrders();
    bool empty() const;
};

#endif
