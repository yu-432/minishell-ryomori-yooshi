#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/environ.h"
#include <sys/stat.h>//add(ryomori):builtin_pwd



bool	path_cwdcheck(char *pwd_path, char *path)
{
	struct stat buf;
	struct stat buf2;

	memset(&buf, 0, sizeof(pwd_path));
	memset(&buf2, 0, sizeof(path));
	if (stat(pwd_path, &buf) < 0)
	{
		perror("Error: stat");
		return (1);
	}
	if (stat(path, &buf2) < 0)
	{
		perror("Error: stat");
		return (1);
	}
	return (buf.st_ino == buf2.st_ino);
}

//正確にパス求めるgetenv-->getcwd(確実)二重チェック
int builtin_pwd(char *line)
{
	char *pwd_path;

	(void)line;
	pwd_path = getenv ("PWD");
	fprintf(stderr, "current_path: %s\n", pwd_path);
	if (pwd_path != NULL || !path_cwdcheck(pwd_path, "."))
	{
		fprintf(stderr, "path_cwdcheck: %s\n . :%s\n", pwd_path, ".");//pathの中身確認
		if (getcwd(pwd_path, PATH_MAX) == NULL)
		{
			perror("Error: getcwd");
			return(1);
		}
		write(STDOUT_FILENO, pwd_path, strlen(pwd_path));
		write(STDOUT_FILENO, "\n", 1);
		return(0);
	}
	else
	{
		fprintf(stderr, "------------------ans\n");
		write(STDOUT_FILENO, pwd_path, strlen(pwd_path));
		write(STDOUT_FILENO, "\n", 1);
	}
	return(0);
}



// int builtin_pwd(char *line)
// {
// 	char pwd_path[PATH_MAX];

// 	(void)line;
// 	if(getcwd(pwd_path, PATH_MAX) == NULL)
// 	{
// 		perror("Error: getcwd");
// 		return(1);
// 	}
// 	else
// 	{
// 		fprintf(stderr, "------------------ans\n");
// 		write(STDOUT_FILENO, pwd_path, strlen(pwd_path));
// 		write(STDOUT_FILENO, "\n", 1);
// 		return(0);
// 	}
// }


int main()
{
	builtin_pwd("pwd");
	return(0);
}