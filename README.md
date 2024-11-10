# minishell_yooshi_ryomori

## 開発順序参考
- usatieさん(メイン参考)
	- [minishell usatie](https://usatie.notion.site/minishell-29921d3ea13447ad897349acd5733d5e)
- nfukadaさん
	- [minishell nfukada](https://nafuka.hatenablog.com/entry/2021/03/29/194200)
## Gitの使い方
- issueを活用しよう
	- [issue使い方](https://qiita.com/tkmd35/items/9612c03dc60b1c516969)
- branchを使おう
	- [branchについて](https://qiita.com/risagon/items/0cd3592b08ee058ffb80)
- コミットメッセージ'a'禁止令
	- [commit messageテンプレート](https://qiita.com/shun198/items/72511bd95e13cf0be88c)
- command
	- [git commandまとめ git概要](https://www.atlassian.com/ja/git/glossary#commands)
## pipeについて
- [pipe](https://www.coins.tsukuba.ac.jp/~syspro/2023/2023-06-14/index.html)


bashの実行部分をC言語で実装します。



```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>

#define MAX_PATH_LENGTH PATH_MAX
#define MAX_ARGS 256

// コマンド実行の結果を表す構造体
typedef struct {
    int status;     // 0: 成功, -1: エラー
    char* error;    // エラーメッセージ
} ExecuteResult;

// ファイルが実行可能かチェックする
static int is_executable(const char* path) {
    struct stat st;
    
    // ファイルの情報を取得
    if (stat(path, &st) != 0) {
        return 0;
    }
    
    // ディレクトリでないことを確認
    if (S_ISDIR(st.st_mode)) {
        return 0;
    }
    
    // 実行権限のチェック
    uid_t uid = geteuid();
    gid_t gid = getegid();
    
    // 所有者として実行可能
    if (st.st_uid == uid) {
        return (st.st_mode & S_IXUSR) != 0;
    }
    
    // グループとして実行可能
    if (st.st_gid == gid) {
        return (st.st_mode & S_IXGRP) != 0;
    }
    
    // その他として実行可能
    return (st.st_mode & S_IXOTH) != 0;
}

// PATHからコマンドを探す
static char* find_command_in_path(const char* command) {
    char* path_env = getenv("PATH");
    if (!path_env) {
        return NULL;
    }
    
    // PATH文字列をコピー（strtokは文字列を変更するため）
    char* path_copy = strdup(path_env);
    if (!path_copy) {
        return NULL;
    }
    
    char* result = NULL;
    char* dir = strtok(path_copy, ":");
    
    while (dir != NULL) {
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        
        // ファイルが存在し実行可能な場合
        if (access(full_path, F_OK) == 0 && is_executable(full_path)) {
            result = strdup(full_path);
            break;
        }
        
        dir = strtok(NULL, ":");
    }
    
    free(path_copy);
    return result;
}

// コマンドを実行する
ExecuteResult execute_command(const char* command, char* const args[]) {
    ExecuteResult result = {-1, NULL};
    
    // 空のコマンドをチェック
    if (!command || strlen(command) == 0) {
        result.error = strdup("empty command");
        return result;
    }
    
    char* cmd_path = NULL;
    
    // コマンドの種類を判定
    if (command[0] == '/' || strncmp(command, "./", 2) == 0) {
        // 絶対パスまたは相対パス
        cmd_path = strdup(command);
    } else {
        // PATHから検索
        cmd_path = find_command_in_path(command);
    }
    
    if (!cmd_path) {
        result.error = strdup("command not found");
        return result;
    }
    
    // ファイルの存在チェック
    if (access(cmd_path, F_OK) != 0) {
        result.error = strdup("no such file or directory");
        free(cmd_path);
        return result;
    }
    
    // 実行権限のチェック
    if (!is_executable(cmd_path)) {
        result.error = strdup("permission denied");
        free(cmd_path);
        return result;
    }
    
    // 子プロセスを作成して実行
    pid_t pid = fork();
    
    if (pid == -1) {
        // fork失敗
        result.error = strdup("fork failed");
        free(cmd_path);
        return result;
    }
    
    if (pid == 0) {
        // 子プロセス
        execv(cmd_path, args);
        // execvが返ったらエラー
        fprintf(stderr, "execv failed: %s\n", strerror(errno));
        exit(1);
    }
    
    // 親プロセス
    int status;
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status)) {
        result.status = WEXITSTATUS(status);
    } else {
        result.status = -1;
        result.error = strdup("abnormal termination");
    }
    
    free(cmd_path);
    return result;
}

// 使用例
int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return 1;
    }
    
    // コマンドライン引数を準備
    char* args[MAX_ARGS];
    int i;
    
    for (i = 0; i < argc - 1 && i < MAX_ARGS - 1; i++) {
        args[i] = argv[i + 1];
    }
    args[i] = NULL;
    
    // コマンドを実行
    ExecuteResult result = execute_command(argv[1], args);
    
    if (result.error) {
        fprintf(stderr, "Error: %s\n", result.error);
        free(result.error);
        return 1;
    }
    
    return result.status;
}

```

この実装では、以下の主要な点に注意して実装しています：

1. コマンドの検索と実行
- コマンドが絶対パス(/から始まる)か相対パス(./から始まる)の場合は直接そのパスを使用
- それ以外の場合はPATH環境変数から検索
- `execv()`を使用して実際のコマンド実行

2. ファイルチェック
- `access()` 関数でファイルの存在を確認
- `stat()` 構造体を使用してファイルの詳細情報を取得
- ディレクトリかどうかのチェック
- 実行権限の確認（所有者、グループ、その他）

3. プロセス管理
- `fork()` で子プロセスを作成
- `execv()` で実際のコマンド実行
- `waitpid()` で子プロセスの終了を待機
- 終了ステータスの取得と確認

4. エラーハンドリング
- メモリ割り当てのエラーチェック
- システムコールのエラーチェック
- 適切なエラーメッセージの生成
- メモリリークの防止

5. セキュリティ考慮事項
- パスの最大長のチェック
- 引数の数の制限
- 権限のチェック

この実装を使用するには、以下のように構築してください：

```bash
gcc -Wall -o myshell shell.c
./myshell ls -l
```

実装の拡張として、以下のような機能を追加することができます：

1. シグナルハンドリング
2. パイプやリダイレクトの実装
3. 環境変数の管理
4. ビルトインコマンドのサポート
5. ジョブ制御

これらの機能の実装が必要な場合は、お知らせください。