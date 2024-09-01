#include "order_book.h"
#include <iostream>

void OrderBook::addOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (order.type == BUY) {
        buyOrders.push(order);
    } else {
        sellOrders.push(order);
    }
}

void OrderBook::matchOrders() {
    std::lock_guard<std::mutex> lock(bookMutex);
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order buyOrder = buyOrders.top();
        Order sellOrder = sellOrders.top();

        if (buyOrder.price >= sellOrder.price) {
            int matchedQuantity = std::min(buyOrder.quantity, sellOrder.quantity);
            std::cout << "Matched: Buy Order " << buyOrder.id << " and Sell Order " << sellOrder.id 
                      << " for " << matchedQuantity << " units at price " << sellOrder.price << std::endl;

            if (buyOrder.quantity > matchedQuantity) {
                buyOrders.pop();
                buyOrder.quantity -= matchedQuantity;
                buyOrders.push(buyOrder);
            } else {
                buyOrders.pop();
            }

            if (sellOrder.quantity > matchedQuantity) {
                sellOrders.pop();
                sellOrder.quantity -= matchedQuantity;
                sellOrders.push(sellOrder);
            } else {
                sellOrders.pop();
            }
        } else {
            break;
        }
    }
}

bool OrderBook::empty() const {
    std::lock_guard<std::mutex> lock(bookMutex);
    return buyOrders.empty() && sellOrders.empty();
}
