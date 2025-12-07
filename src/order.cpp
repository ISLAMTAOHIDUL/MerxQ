#include "../include/order.h"
#include "../include/exceptions.h"
#include <iomanip>
#include <sstream>

// ============================================
// CONSTRUCTORS
// ============================================

Order::Order()
    : id(""), customerId(0), totalAmount(0.0), status(OrderStatus::PENDING),
      createdAt(getCurrentTimestamp()), updatedAt(createdAt) {}

Order::Order(const string &id, int customerId, const vector<OrderItem> &items,
             double total)
    : id(id), customerId(customerId), items(items), totalAmount(total),
      status(OrderStatus::PENDING), createdAt(getCurrentTimestamp()),
      updatedAt(createdAt) {}

// ============================================
// FACTORY METHOD
// ============================================

Order Order::createFromCart(const string &orderId, int customerId,
                            const Cart &cart) {
  if (cart.isEmpty()) {
    throw InvalidInputException("Cannot create order from empty cart");
  }

  vector<OrderItem> orderItems;
  for (const CartItem &cartItem : cart.getItems()) {
    OrderItem item;
    item.productId = cartItem.product.getId();
    item.productName = cartItem.product.getName();
    item.price = cartItem.product.getPrice();
    item.quantity = cartItem.quantity;
    orderItems.push_back(item);
  }

  return Order(orderId, customerId, orderItems, cart.getTotal());
}

