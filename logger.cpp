#include "logger.h"

void OrderBook::addOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (order.type == BUY) {
        buyOrders.push(order);
    } else {
        sellOrders.push(order);
    }
    Logger::log("Added Order: " + std::to_string(order.id));
}

void OrderBook::matchOrders() {
    std::lock_guard<std::mutex> lock(bookMutex);
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order buyOrder = buyOrders.top();
        Order sellOrder = sellOrders.top();

        if (buyOrder.price >= sellOrder.price) {
            int matchedQuantity = std::min(buyOrder.quantity, sellOrder.quantity);
            Logger::log("Matched: Buy Order " + std::to_string(buyOrder.id) + " and Sell Order " + std::to_string(sellOrder.id));
            
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
