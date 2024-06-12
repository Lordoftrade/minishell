#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// Функция для инициализации переменных окружения (пример)
t_env *init_env() {
    t_env *env_list = malloc(sizeof(t_env));
    if (!env_list) return NULL;
    env_list->value = strdup("HOME=/home");
    env_list->next = NULL;
    return env_list;
}

// Пример функции для обработки ввода и выполнения команды cd
void display_prompt(t_env *env) {
    char *input;
    char *args[3]; // Пример для команды cd с максимум одним аргументом
    while (1) {
        input = readline("minishell> ");
        if (input && *input) {
            add_history(input);
            args[0] = strtok(input, " "); // Получаем первое слово из ввода
            args[1] = strtok(NULL, " "); // Получаем второе слово из ввода
            args[2] = NULL;
            if (args[0] && strcmp(args[0], "cd") == 0) {
                if (shell_cd(args, env) == FAILURE) // но может возвращен быть и - 1 елси чдир не откроет (0 и 1 )
				{
                    fprintf(stderr, "cd command failed\n");
                }
            } else if (args[0] && strcmp(args[0], "pwd") == 0) {
                if (shell_pwd() == FAILURE) {
                    fprintf(stderr, "pwd command failed\n");
                }
            } else {
                printf("minishell: command not found: %s\n", args[0]);
				// или другое использование вывода ошибки
            }

//
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current directory: %s\n", cwd);
            } else {
                perror("getcwd() error");
            }

             t_env *cur = env;
            while (cur)
            {
                char *value = cur->value;
                if (strncmp(value, "OLDPWD=", 7) == 0)
                {
                    printf("OLDPWD=%s\n", value + 7); // Выводим значение после "OLDPWD="
                    break; // Выходим из цикла, так как нашли переменную
                }
                cur = cur->next;
            }
//

            free(input);
        } else {
            free(input);
            break;
        }
    }
}

int main() {
    t_env *env = init_env();
    if (!env) {
        fprintf(stderr, "Failed to initialize environment variables\n");
        return FAILURE;
    }
    display_prompt(env);

    // Освобождение памяти
    t_env *cur = env;
    while (cur) {
        t_env *tmp = cur;
        cur = cur->next;
        free(tmp->value);
        free(tmp);
    }

    return SUCCESS;
}
