#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ヒアドキュメントを処理し、一時ファイルに保存する関数
void handle_heredoc(char *delimiter, char *filename)
{
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read_len;
    int     fd;

    // ヒアドキュメントの入力を保存する一時ファイルを作成
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    printf("heredoc> ");
    while ((read_len = getline(&line, &len, stdin)) != -1)
    {
        // 終端文字列（delimiter）に到達したら終了
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n')
            break;

        // 入力を一時ファイルに書き込む
        write(fd, line, read_len);
        printf("heredoc> ");
    }

    free(line);
    close(fd);  // 一時ファイルを閉じる
}

// 一時ファイルを標準入力にリダイレクトする関数
void redirect_heredoc_to_stdin(char *filename)
{
    int fd;

    // 一時ファイルを読み込み専用で開く
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    // 標準入力をヒアドキュメントの内容にリダイレクト
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(fd);  // ファイルディスクリプタを閉じる
}

int main()
{
    // 一時ファイル名の指定
    char *heredoc_filename = "/tmp/heredoc_temp.txt";

    // ヒアドキュメントを処理
    handle_heredoc("EOF", heredoc_filename);

    // ヒアドキュメントを標準入力としてリダイレクト
    redirect_heredoc_to_stdin(heredoc_filename);

    // ヒアドキュメントを標準入力に渡して cat コマンドを実行
    execlp("cat", "cat", NULL);

    // エラーが発生した場合の処理
    perror("execlp");
    return 1;
}
