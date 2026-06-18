// Разработать программу solution, которая по заданному pid, осуществляет поиск 
// всех потомков процесса с этим идентификатором и выводит их количество 
// (включая процесс с заданным pid).

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Рекурсивная функция подсчета всех потомков процесса
int count_processes(int pid) {
    int total = 1;  // Учитываем сам процесс
    char path[256];
    // Формирование пути к файлу children в директории task
    snprintf(path, sizeof(path), "/proc/%d/task/%d/children", pid, pid);
    // Открытие файла children
    FILE* f = fopen(path, "r");
    if (!f) return total;  // Если файл не открыт, возвращаем только текущий процесс
    int child_pid;
    // Чтение всех PID дочерних процессов из файла
    while (fscanf(f, "%d", &child_pid) == 1) {
        // Рекурсивно подсчитываем всех потомков каждого дочернего процесса
        total += count_processes(child_pid);
    }
    fclose(f);
    return total;
}

int main(int argc, char* argv[]) {
    // Проверка передан ли PID в аргументах командной строки
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    // Преобразование строкового аргумента в целое число
    int pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID\n");
        return 1;
    }
    // Проверка существования процесса по пути /proc/PID
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d", pid);
    DIR* dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "Process %d not found\n", pid);
        return 1;
    }
    closedir(dir);
    
    // Подсчет всех потомков
    int result = count_processes(pid);
    printf("%d\n", result);
    
    return 0;
}
