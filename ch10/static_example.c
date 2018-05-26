/*
 * This program is used to demonstrate the effect of the static keyword on
 * global variables and functions. In this context, it makes the symbol
 * availalbe only in the current module (.c file). The nm command can be used
 * to examine the symbol table of the compiled object.
 *   $ nm static_example.o
 */
int global_int;        /* external linkage */
static int module_int; /* module scope global variable with internal linkage */

/* Module scope (global) function with internal linkage. */
static int module_function() {
  /*
   * Static local variables are placed in the BSS section which makes them
   * global variables (they persist between function calls), but they have local
   * function scope, so they are not accessible by other functions. The next
   * time this function executes, the value of a local static variable will be
   * the same as when the function terminated last time.
   */
  static int static_local_var;

  /*
   * Local variables are allocated on the stack frame for the function and
   * their scope is local to that function. They disappear when the function
   * returns.
   */
  int local_var; /* internal linkage */
  return 0;
}

int main(void) { return 0; }