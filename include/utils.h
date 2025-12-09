#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

// Utility class for common functions
class Utils {
public:
  // ANSI COLOR & FORMATTING
  // Apply color to text (red, green, yellow, blue, white)
  static string colorText(const string &text, const string &color = "",
                          const string &bgColor = "", const string &style = "");

  // DISPLAY FUNCTIONS
  // Show main header with blue background
  static void showMainHeader(const string &title);

  // Show sub-header for sections
  static void showSubHeader(const string &subtitle);

  // Clear the console screen
  static void clearScreen();

  // Wait for user to press Enter
  static void pauseScreen();

  // Show loading animation
  static void showLoading(const string &message, int seconds = 2);

  // INPUT VALIDATION
  // Get valid integer between min and max
  static int getIntInput(const string &prompt, int min, int max);

  // Get valid decimal number
  static double getDoubleInput(const string &prompt, double min, double max);

  // Get string input from user
  static string getStringInput(const string &prompt);

  // Get menu choice
  static int getMenuChoice(const string &prompt, int minOption, int maxOption);
};

#endif
