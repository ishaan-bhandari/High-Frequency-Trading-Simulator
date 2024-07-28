#ifndef ORDER_H
#define ORDER_H

enum OrderType {
    BUY,
    SELL
};

struct Order {
    int id;
    OrderType type;
    double price;
    int quantity;
    long timestamp;

    bool operator<(const Order& other) const {
        if (price == other.price) {
            return timestamp > other.timestamp;
        }
        return type == BUY ? price < other.price : price > other.price;
    }
};

#endif
