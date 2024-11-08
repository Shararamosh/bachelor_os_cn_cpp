#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "locale.h"

int main(int argc, char* argv[])
{
    int maxlen=0;
    char maxsym = 0;
    int count_read;
    int curlen=0;
    int pos=0;
    int curpos=0;
    int maxpos=0;
    char buf[1]; //Очередной символ, который мы считали.
    char n = 0; //Символ, который мы считаем повторяющимся.
    setlocale(LC_ALL, "RU");
    int fin=open(argv[1], O_RDONLY);
    if (fin==-1)
    {
        perror("Файл не может быть открыт.");
        return EXIT_FAILURE;
    }
    while ((count_read=_read(fin, buf, 1)!=0))
    {
        pos++;
        if (n!=buf[0])
        {
            if (curlen>maxlen)
            {
                maxpos=curpos;
                maxlen=curlen;
                maxsym=n;
            }
            curlen=1;
            curpos=pos;
            n=buf[0];
        }
        else
        {
            curlen++;
        }
    }
    _close(fin);
    if (pos == 0)
        printf("Файл пустой.");
    else
        printf("Самая длинная последовательность: начало - позиция %d, длина - %d, символ - %c.", maxpos, maxlen, maxsym);
    return 0;
}