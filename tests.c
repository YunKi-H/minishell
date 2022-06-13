#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	t_sh	*msh;
	msh = init_sh(envp);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	while (1)
	{
		if (parsing(ft_readline("\rmsh % "), msh))
			continue ; // new prompt
		// todo : check_syn_err(msh);
		run_cmd(msh);
	}

	// get_path test
	// while (1)
	// {
	// 	parsing(readline("msh % "), msh);
	// 	char *path = get_path(msh->cmdt->head, msh);
	// 	printf("%s\n", path);
	// 	free(path);
	// 	system("leaks minishell");
	// }

	// _getenv test
	// printf("%s : %s\n", "USER", _getenv("USER", msh->envt)->value);
	// printf("%s : %s\n", "LANG", _getenv("LANG", msh->envt)->value);
	// printf("%s : %s\n", "_", _getenv("_", msh->envt)->value);
	// printf("%s : %s\n", "AAAA", (char *)_getenv("AAAA", msh->envt));

	// exit test
	// t_env *env = msh->envt->head;
	// env->next->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_exit(msh, cmdl);
	// 	printf("%d\n", msh->sh_error);
	// 	break;
	// }

	// unset test
	// t_env *env = msh->envt->head;
	// env->next->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	ft_env(msh->envt);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_unset(msh, cmdl);
	// 	ft_env(msh->envt);
	// }

	// export test
	// t_env *env = msh->envt->head;
	// env->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_export(msh, cmdl);
	// 	ft_env(msh->envt);
	// }

	// cd test
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_cd(msh, cmdl);
	// 	ft_pwd();
	// }

	// tokenize test
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	// parsing(ft_strdup("echo            \"he\"l'l'\"o\" '|' \"cat\" -e"), msh);
	// 	print_cmdt(msh);
	// 	break ;
	// }

	// env,pwd test
	// ft_env(msh->envt);
	// printf("-----------\n");
	// ft_pwd();

	// replace_env test
	// char *test1 = replace_env("abcdefg hijklmn opqrstu ", msh);
	// printf("test1 = %s\n", test1);
	// char *test2 = replace_env("$USER", msh);
	// printf("test2 = %s\n", test2);
	// char *test3 = replace_env("\"$USER\" '$USER' \"$USER\"", msh);
	// printf("test3 = %s\n", test3);
	// char *test4 = replace_env("$USER$AAA$USER$USER$AAA", msh);
	// printf("test4 = %s\n", test4);
	// char *test5 = replace_env("$ \"$\" $ ", msh);
	// printf("test5 = %s\n", test5);
	// msh->sh_error = 127;
	// char *test6 = replace_env("$???", msh);
	// printf("test6 = %s\n", test6);

	// buffer test
	// t_buf	*test;
	// test = new_buf();
	// char *tmp = "abcdefghikljsdfhbnojnfbop oijfapobknadsdfbfdobnjokjop oaksdjfoasfhbniosejbno woakdgjnaaaaaaaaaaa";
	// int i = 0;
	// while (tmp[i])
	// {
	// 	printf("%d\n", i);
	// 	buf_append(test, tmp[i]);
	// 	i += 1;
	// }
	// system("leaks minishell");
	// printf("%d %s\n", test->size, test->buffer);

	// getenv 동적할당여부 (false)
	// char *test = getenv("PWD");
	// printf("PWD : %s\n", test);
	// free(test);

	// 환경변수 제대로 init 된거 test
	// t_env	*tmp = msh->envt->head;
	// int i = 0;
	// while (tmp)
	// {
	// 	printf("[%d] key : [%s] value : [%s]\n", i, tmp->key, tmp->value);
	// 	i += 1;
	// 	tmp = tmp->next;
	// }

	// readline 동적할당여부 (true)
	// char *line = readline("shell % ");
	// printf("line : %s\n",line);
	// free(line);

}
