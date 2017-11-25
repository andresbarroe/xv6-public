#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PASSWD "/passwd"
#define BUF_SIZE 512

int readLine( int fd, char *buf, int size )
{
    int i = 0, n = 0;
    char c;

    while ( read( fd, &c, 1 ) > 0) 
    {
        n++;
        if ( c != '\n' )
        {
            buf[i] = c;
            i++;
            if ( i == size - 1)
            {
                break;
            }
        }
        else {
            break;
        }
    }
    buf[i] = '\0';
    return n;
}

int checkUname(int fd, char *uname)
{
    char buff[BUF_SIZE];
    char *buf;
    buf = buff;
    // fd = open(PASSWD, 0);
    while (readLine(fd, buf, sizeof(buff)) > 0)
    {
        // printf(1, buf);
        // printf(1, "\n");
        char *name;
        name = uname;
        // printf(1, name);
        // printf(1, "\n");
        while (*(buf++) == *(name++))
            ;
        // printf(1, buf);
        // printf(1, "\n");
        if (*(name - 1) == '\0' && *(buf - 1) == ':')
        {
            return -1;
        }
        buf = buff;
    }
    // printf(1, "\nDone1\n");
    return 0;
}

char *
itoa(int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0)
        *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf(1, "Please input both username and password.\n");
        exit();
    }
    int fd;
    char buff[BUF_SIZE], num[BUF_SIZE];
    char *buf = buff;
    int id = -2;
    fd = open(PASSWD, O_RDONLY);
    if (checkUname(fd, argv[1]) == -1)
    {
        printf(1, "Username already used. Please run the command again.\n");
        exit();
    }
    close(fd);
    fd = open(PASSWD, O_RDWR);
    while (readLine(fd, buf, sizeof(buff)) > 0)
    {
        // printf(1, buf);
        // printf(1, "HII\n");
        char *tmp;
        tmp = num;
        tmp = buff;
        while (*(tmp++) != ':')
            ;
        char *tmp2;
        tmp2 = tmp;
        while (*(tmp2++) != ':')
            ;
        *(tmp2 - 1) = '\0';
        // printf(1, "HII\n");
        // printf(1, tmp);
        id = atoi(tmp);
        // printf(1, "\n");
        // printf(1, num);
        // printf(1, "\n");
    }
    // printf(1, "\nDone2\n");
    id++;
    char *line = buff;
    int i;
    int len = 1;
    for (i = 0; argv[1][i] != '\0'; ++i)
    {
        *line = argv[1][i];
        ++line;
        ++len;
    }
    *line = ':';
    ++line;
    ++len;
    // char *tmp =
    itoa(id, line, 10);
    while (*(line++) != '\0')
    {
        ++len;
    }
    --line;
    *line = ':';
    ++line;
    for (i = 0; argv[2][i] != '\0'; ++i)
    {
        *line = argv[2][i];
        ++line;
        ++len;
    }
    *line = '\n';
    ++line;
    ++len;
    *line = '\0';

    write(fd, buff, len);

    close(fd);
    exit();
}
