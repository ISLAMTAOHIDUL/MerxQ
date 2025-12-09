#include "../include/application.h"
#include "../include/exceptions.h"


















// ============================================
// CUSTOMER FEATURES
// ============================================

void Application::displayProductList() const {
  if (products.empty()) {
    cout << Utils::colorText("No products available.", "yellow") << endl;
    return;
  }

  cout << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;
  cout << Utils::colorText(
              " ID     │ Name                      │ Price      │ Stock",
              "white", "", "bold")
       << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;

  for (const Product &p : products) {
    p.displayShort();
  }
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;
}

void Application::browseProducts() {
  Utils::clearScreen();
  Utils::showSubHeader("📦 Product Catalog");

  products = FileManager::loadProducts(); // Refresh
  displayProductList();

  Utils::pauseScreen();
}

void Application::searchProducts() {
  Utils::clearScreen();
  Utils::showSubHeader("🔍 Search Products");

  string query = Utils::getStringInput("Search term: ");

  // Convert query to lowercase for case-insensitive search
  string queryLower = query;
  for (char &c : queryLower)
    c = tolower(c);

  cout << endl;
  cout << Utils::colorText("Search results for: ", "white")
       << Utils::colorText(query, "yellow", "", "bold") << endl;

  bool found = false;
  for (const Product &p : products) {
    // Convert product fields to lowercase for comparison
    string nameLower = p.getName();
    string catLower = p.getCategory();
    string descLower = p.getDescription();
    for (char &c : nameLower)
      c = tolower(c);
    for (char &c : catLower)
      c = tolower(c);
    for (char &c : descLower)
      c = tolower(c);

    if (nameLower.find(queryLower) != string::npos ||
        catLower.find(queryLower) != string::npos ||
        descLower.find(queryLower) != string::npos) {
      p.displayShort();
      found = true;
    }
  }

  if (!found) {
    cout << Utils::colorText("No products found matching your search.",
                             "yellow")
         << endl;
  }

  Utils::pauseScreen();
}

void Application::addToCart() {
  Utils::clearScreen();
  Utils::showSubHeader("🛒 Add to Cart");

  products = FileManager::loadProducts();
  displayProductList();

  string productId = Utils::getStringInput("Enter Product ID (or 'back'): ");
  if (productId == "back")
    return;

  try {
    Product product = FileManager::findProduct(productId);

    if (!product.isInStock()) {
      cout << Utils::colorText("✗ Product is out of stock!", "red") << endl;
      Utils::pauseScreen();
      return;
    }

    int quantity = Utils::getIntInput("Quantity: ", 1, product.getQuantity());

    currentCart.addItem(product, quantity);
    cout << Utils::colorText("✓ Added to cart!", "green", "", "bold") << endl;
    Utils::pauseScreen();
  } catch (const ProductNotFoundException &e) {
    cout << Utils::colorText("✗ " + string(e.what()), "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::viewCart() {
  Utils::clearScreen();
  Utils::showSubHeader("🛒 Your Cart");

  currentCart.displayCart();
  Utils::pauseScreen();
}

void Application::checkout() {
  Utils::clearScreen();
  Utils::showSubHeader("💳 Checkout");

  if (currentCart.isEmpty()) {
    cout << Utils::colorText("Your cart is empty!", "yellow") << endl;
    Utils::pauseScreen();
    return;
  }

  currentCart.displayCart();

  cout << endl;
  string confirm = Utils::getStringInput("Confirm order? (yes/no): ");

  if (confirm != "yes" && confirm != "y") {
    cout << Utils::colorText("Order cancelled.", "yellow") << endl;
    Utils::pauseScreen();
    return;
  }

  try {
    // Create order
    string orderId = FileManager::generateOrderId();
    Order order =
        Order::createFromCart(orderId, currentUser->getId(), currentCart);

    // Save order
    FileManager::addOrder(order);

    // Update product stock
    for (const CartItem &item : currentCart.getItems()) {
      Product p = FileManager::findProduct(item.product.getId());
      p.reduceStock(item.quantity);
      FileManager::updateProduct(p);
    }

    // Clear cart
    currentCart.clear();
    products = FileManager::loadProducts();
    orders = FileManager::loadOrders();

    cout << endl;
    cout << Utils::colorText("╔═══════════════════════════════════════════╗",
                             "green")
         << endl;
    cout << Utils::colorText("║", "green") << "     "
         << Utils::colorText("ORDER PLACED SUCCESSFULLY!", "white", "", "bold")
         << "         " << Utils::colorText("║", "green") << endl;
    cout << Utils::colorText("╠═══════════════════════════════════════════╣",
                             "green")
         << endl;
    cout << Utils::colorText("║", "green")
         << " Order ID: " << Utils::colorText(orderId, "yellow", "", "bold")
         << "                       " << Utils::colorText("║", "green") << endl;
    cout << Utils::colorText("╚═══════════════════════════════════════════╝",
                             "green")
         << endl;

    Utils::pauseScreen();
  } catch (const exception &e) {
    cout << Utils::colorText("✗ Error: " + string(e.what()), "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::viewOrderHistory() {
  Utils::clearScreen();
  Utils::showSubHeader("📋 Order History");

  vector<Order> customerOrders =
      FileManager::getCustomerOrders(currentUser->getId());

  if (customerOrders.empty()) {
    cout << Utils::colorText("You haven't placed any orders yet.", "yellow")
         << endl;
    Utils::pauseScreen();
    return;
  }

  cout << endl;
  for (const Order &order : customerOrders) {
    order.displayShort();
  }

  string viewDetails = Utils::getStringInput(
      "\nView order details? Enter Order ID (or 'back'): ");
  if (viewDetails != "back") {
    for (const Order &order : customerOrders) {
      if (order.getId() == viewDetails) {
        order.displayOrder();
        break;
      }
    }
  }

  Utils::pauseScreen();
}

void Application::viewProfile() {
  Utils::clearScreen();
  Utils::showSubHeader("👤 My Profile");

  currentUser->displayInfo();
  Utils::pauseScreen();
}
