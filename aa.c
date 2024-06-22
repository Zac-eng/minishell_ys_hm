#include <stdio.h>

// 関数の定義
void increment(int *ptr) {
    ptr++; // ポインタが指す値をインクリメントする
}

int main() {
    int num = 5;
    int *ptr = &num; // num のアドレスをポインタに格納する

    printf("Before increment: num = %p\n", ptr);

    // 関数を呼び出してポインタが指す値を変更する
    increment(ptr);

    printf("After increment: num = %p\n", ptr);

    return 0;
}