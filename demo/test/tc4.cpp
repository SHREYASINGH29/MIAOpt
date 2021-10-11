struct s{
    int a, b;
    int*d;
}*c;
int r;
int* s;
int main(){
     c->a = r;
     s = c->d;
     c->d = &r;
}
