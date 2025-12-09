#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include <string>

using namespace std;

// Admin class - inherits from User
class Admin : public User {
private:
  string department;
  bool superAdmin;

public:
  // Constructor
  Admin(int id, const string &name, const string &email, const string &password,
        const string &department = "General", bool superAdmin = false);

  // Override parent functions
  void displayMenu() override;
  void displayInfo() const override;

  // Inventory management
  void viewInventory();
  void addProduct();
  void updateProduct(int productId);
  void deleteProduct(int productId);

  // Order management
  void viewAllOrders();
  void updateOrderStatus(int orderId);

  // User management
  void viewAllUsers();

  // Getters
  string getDepartment() const { return department; }
  bool isSuperAdmin() const { return superAdmin; }

  // Setters
  void setDepartment(const string &newDepartment);
  void setSuperAdmin(bool status);
};

#endif
