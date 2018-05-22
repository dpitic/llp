/*
 * This program deonstrates inclusion polymorphism in C.
 */
#include <stdio.h>

struct parent
{
  const char *field_parent;
};

struct child
{
  struct parent base;
  const char *field_child;
};

void print_parent(struct parent *this) {
  printf("%s\n", this->field_parent);
}

int main(int argc, char const *argv[])
{
  struct child c;
  c.base.field_parent = "parent";
  c.field_child = "child";
  print_parent((struct parent*)&c);
  return 0;
}