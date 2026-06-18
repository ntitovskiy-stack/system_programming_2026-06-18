// Разработать программу solution, которая осуществляет поиск и подсчет числа процессов 
// с именем genenv в системе Linux на которой выполняется программа.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int main()
{
    // Открытие директории /proc, где хранится информация о всех процессах
    DIR *d = opendir("/proc");
    if (d == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть /proc\n");
        return 1;
    }
    // Переменная для чтения записей директории
    struct dirent *e;
    // p - путь к файлу comm, l - буфер для чтения имени
    char p[256], l[256];
    int c = 0;
    // Чтение записей в /proc
    while ((e = readdir(d))) {
        // Пропуск записей, которые не начинаются с цифры (не PID)
        if (!isdigit(e->d_name[0])) continue;
        // Формирование пути
        sprintf(p, "/proc/%s/comm", e->d_name);
        // Открытие файла, содержащего имя процесса
        FILE *f = fopen(p, "r");
        if (f && fgets(l, 256, f) && strcmp(l, "genenv\n") == 0) 
            c++;
        // Закрытие файла, если он был открыт
        if (f) fclose(f);
    }
    closedir(d);  // Закрытие директории
    printf("%d\n", c);
    return 0;
}
