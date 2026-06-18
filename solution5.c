/* Разработать программу solution, которая при запуске себя "демонизирует" и остается в памяти. 
Перед закрытием стандартного потока вывода stdout унаследованного от родителя, 
программа должна вывести в него Pid процесса-демона. */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // fork - отделение от терминала
    if (fork() > 0) return 0;
    // Создание нового сеанса и группы процессов
    setsid();
    // Вывод PID демона в stdout
    printf("%d\n", getpid());
    fflush(stdout);
    // Закрытие stdout
    fclose(stdout);
    // Переход в корневую директорию
    chdir("/");
    // Сброс маски создания файлов
    umask(0);
    // Перенаправление STDIN, STDOUT, STDERR в /dev/null
    close(STDIN_FILENO);   // Закрытие stdin
    open("/dev/null", O_RDWR);  // Открытие /dev/null как новый stdin
    close(STDOUT_FILENO);  // Закрытие stdout
    close(STDERR_FILENO);  // Закрытие stderr
    // Бесконечный цикл - демон работает в фоне
    while (1) sleep(1);
    return 0;
}
