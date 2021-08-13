union test {
  char *y;
};
union test *t;
char a;
int main() {
  //(t->y)=&a;
  a = *(t->y);
  return 0;
}
