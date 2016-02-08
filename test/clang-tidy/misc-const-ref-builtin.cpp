// RUN: %check_clang_tidy %s misc-const-ref-builtin %t

void f(const int& i);
// CHECK-MESSAGES: :[[@LINE-1]]:19: warning: const reference to 'int' at parameter 'i' in function 'f' [misc-const-ref-builtin]

void f2(const int&);
// CHECK-MESSAGES: :[[@LINE-1]]:19: warning: const reference to 'int' type at index '0' in function 'f2' [misc-const-ref-builtin]

typedef int Int;
void t(const Int& i);


template<typename T>
void g(const T&);

void X() {
  g(5);
}

void f3();

void h(int& i);

class Bar {};
void f4(const Bar& bar);

class Baz {
  int i;
};
void f5(const Baz& baz);

void f(const int& i, const int& j);
// CHECK-MESSAGES: :[[@LINE-1]]:19: warning: const reference to 'int' at parameter 'i' in function 'f' [misc-const-ref-builtin]
// CHECK-MESSAGES: :[[@LINE-2]]:33: warning: const reference to 'int' at parameter 'j' in function 'f' [misc-const-ref-builtin]
