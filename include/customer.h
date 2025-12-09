#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include <string>
#include <vector>

using namespace std;

// Customer class - inherits from User
class Customer : public User {
private:
  string address;
  string phone;
  vector<int> cartProductIds;
  vector<int> orderIds;

public:
  // Constructor
  Customer(int id, const string &name, const string &email,
           const string &password, const string &address = "",
           const string &phone = "");

  // Override parent functions
  void displayMenu() override;
  void displayInfo() const override;

  // Customer features
  void browseProducts();
  void addToCart(int productId);
  void removeFromCart(int productId);
  void viewCart() const;
  void clearCart();
  void placeOrder();
  void viewOrderHistory() const;

  // Getters
  string getAddress() const { return address; }
  string getPhone() const { return phone; }
  vector<int> getCart() const { return cartProductIds; }
  int getCartSize() const { return cartProductIds.size(); }

  // Setters
  void setAddress(const string &newAddress);
  void setPhone(const string &newPhone);
};

#endif
