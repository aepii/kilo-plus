#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Hold the original terminal settings to restore them after disabling raw mode
struct termios original_termios; 

// Disable raw mode
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) // Set the original terminal settings
}

// Enable raw mode
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &original_termios); // Save the original terminal settings
  atexit(disableRawMode); // Disable raw mode on termination

  struct termios raw = original_termios; // Create a copy of original terminal settings to raw
  raw.c_lflag &= ~(ECHO); // Disable echo

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply the modified settings to the terminal
}

// Main entry
int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');

  return 0;
}