#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>


//親プロセスがforkすることで子プロセスのpidが戻り値として得られる
//作成した子プロセスがもう一度forkを実行すると、戻り値が0になり孫プロセスは作成されない
//forkを実行しpid = 0の場合そのプロセスは子プロセスとなる。
//pid == 0で条件分岐させ、処理を書くことで親子で別の処理を実行することが可能
//親子のプロセスで同名の変数を定義した場合別々の領域に作成されるため共有は別の方法で行う必要がある
//forkを実行するした直後の位置から実行を継続する->fork以前の変数の値は共有される

//https://man7.org/linux/man-pages/man2/fork.2.html

int main(void)
{
	pid_t pid;
	int n = 1;
	int fp = open("sample.txt", O_WRONLY);

	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
		perror("signal");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	n++;
	if (pid == 0)
	{
		for (int i = 0; i < 10000; i++)
			n++;
		printf("child printing pid = %d, gid = %d\n", pid, getgid());
		printf("child n = %d\n", n);
		write(fp, "This is child\n", 14);
		exit(EXIT_SUCCESS);
	}
	n++;
	if (pid > 0)
	{
		for (int i = 0; i < 10000; i++)
			n++;
		printf("parent printing pid = %d, gid = %d\n", pid, getgid());
		printf("parent n = %d\n", n);
		write(fp, "This is parent\n", 15);
		exit(EXIT_SUCCESS);
	}
}
