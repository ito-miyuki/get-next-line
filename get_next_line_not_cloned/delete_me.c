#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5


// get_next_line 関数は指定されたファイルディスクリプタ (fd) から改行文字までのデータを読み取る関数です
char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1];  // データを一時的に保存するためのバッファ
    int chars_read;  // read 関数から読み取った文字数
    char *str = buffer;  // バッファ内を移動するためのポインタ
    int counter = 0;  // バッファから読み取った文字数のカウンター
    char *result = malloc(sizeof(char) * (BUFFER_SIZE + 1));  // 読み取ったデータを保存するためのメモリ領域

    // バッファから改行文字が見つかるまでループ
    while (*str != '\n') {
        counter = 0;  // カウンターの初期化
        // バッファから BUFFER_SIZE 分だけ読み取るループ
        while (counter < BUFFER_SIZE && *str != '\n') {
            chars_read = read(fd, str, 1);  // 1 バイトずつ読み取り
            counter++;
            if (chars_read <= 0) {  // read 関数から読み取れなかった場合
                if (str == buffer) {
                    free(result);  // 最初から何も読み取られなかった場合、メモリを解放
                    return NULL;
                } else {
                    *str = '\0';  // バッファを終端
                    return buffer;
                }
            }
            str++;
        }
        *str = '\0';  // バッファを終端
        result = ft_strjoin(result, buffer);  // データを result に連結
    }

    free(result);  // ループを抜けた後、メモリを解放
    return buffer;  // 改行文字までのデータを返す
}
