#include "multi_stock_order_book.h"
#include <iostream>

int main() {
    MultiStockOrderBook orderBooks;

    //apple
    Order buyOrder1 = {1, BUY, 150.0, 10, 1623786000};
    Order sellOrder1 = {2, SELL, 149.5, 10, 1623786001};
    orderBooks.addOrder("AAPL", buyOrder1);
    orderBooks.addOrder("AAPL", sellOrder1);
    orderBooks.matchOrders("AAPL");


    //google
    Order buyOrder2 = {3, BUY, 2500.0, 5, 1623786100};
    Order sellOrder2 = {4, SELL, 2495.0, 5, 1623786101};
    orderBooks.addOrder("GOOG", buyOrder2);
    orderBooks.addOrder("GOOG", sellOrder2);
    orderBooks.matchOrders("GOOG");

    return 0;
}
