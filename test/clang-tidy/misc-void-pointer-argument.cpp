// RUN: %check_clang_tidy %s misc-void-pointer-argument %t

void f(void *something);
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' has a void* argument [misc-void-pointer-argument]


void f2(int i);
void f3(int *i);

void f4(int n, void *something);
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f4' has a void* argument [misc-void-pointer-argument]
