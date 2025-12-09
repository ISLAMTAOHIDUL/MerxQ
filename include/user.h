#ifndef USER_H
#define USER_H

#include "utils.h"
#include <iostream>
#include <string>

using namespace std;

// Base class for all users (Customer and Admin inherit from this)
class User {
protected:
  int id;
  string name;
  string email;
  string password;
  string role; // "customer" or "admin"

public:
  // Constructor
  User(int id, const string &name, const string &email, const string &password,
       const string &role);

  // Virtual destructor for proper cleanup
  virtual ~User() = default;

  // Pure virtual - makes this class abstract
  virtual void displayMenu() = 0;

  // Virtual functions - can be overridden by child classes
  virtual void displayInfo() const;
  virtual bool authenticate(const string &inputPassword) const;

  // Getters
  int getId() const { return id; }
  string getName() const { return name; }
  string getEmail() const { return email; }
  string getPassword() const { return password; }
  string getRole() const { return role; }

  // Setters
  void setName(const string &newName);
  void setEmail(const string &newEmail);
  void setPassword(const string &newPassword);
};

#endif
