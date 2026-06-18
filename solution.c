/* Разработать программу solution, которая по заданному pid, осуществляет поиск пути 
в дереве процессов до процесса с идентификатором 1 (init). 
Для каждого найденного процесса печатается в отдельной строке его идентификатор. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Проверка: передан ли аргумент командной строки
    if (argc < 2) {
        fprintf(stderr, "Ошибка: укажите PID в аргументах командной строки\n");
        return 1;
    }
    // Преобразование строкового аргумент в целое число
    int pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Ошибка: неверный PID\n");
        return 1;
    }
    char path[64];       // Буфер для пути к файлу /proc/PID/stat
    FILE *f;             // Указатель на файл
    int p, ppid;         // p - текущий PID, ppid - родительский PID
    char comm[256];      // Имя команды процесса
    char state;          // Состояние процесса
    // Идем вверх по дереву процессов, пока не достигнем init
    while (pid != 1) {
        // Печать текущего PID
        printf("%d\n", pid);
        // Формирование пути к файлу статистики процесса
        sprintf(path, "/proc/%d/stat", pid);
        // Открытие файла статистики
        f = fopen(path, "r");
        if (!f) {
            fprintf(stderr, "Ошибка: не удалось открыть /proc/%d/stat\n", pid);
            return 1;
        }
        // Чтение первых 4 полей: PID, имя, состояние, родительский PID
        if (fscanf(f, "%d %s %c %d", &p, comm, &state, &ppid) != 4) {
            fprintf(stderr, "Ошибка: неверный формат данных для PID %d\n", pid);
            fclose(f);
            return 1;
        }
        fclose(f);
        pid = ppid;
    }
    printf("1\n");
    return 0;
}
