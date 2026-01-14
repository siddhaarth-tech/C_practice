/*Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry.*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#define MAX_PATH 1024

void fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *));

void print_permissions(mode_t mode)
{
    char perms[11];

    perms[0] = S_ISDIR(mode) ? 'd' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';

    printf("%s ", perms);
}

void fsize(char *name)
{
    struct stat st;
    char timebuf[64];
    struct tm *tm_info;

    if(stat(name, &st) == -1)
    {
        perror(name);
        return;
    }

    if(S_ISDIR(st.st_mode))
    {
        dirwalk(name, fsize);
    }

    print_permissions(st.st_mode);

    printf("%3ld ", (long)st.st_nlink);
    printf("%5d %5d ", st.st_uid, st.st_gid);
    printf("%8ld ", (long)st.st_size);

    tm_info = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm_info);
    printf("%s ", timebuf);

    printf("%s\n", name);
}

void dirwalk(char *dir, void (*fcn)(char *))
{
    DIR *dp;
    struct dirent *entry;
    char path[MAX_PATH];

    if((dp = opendir(dir))==NULL)
    {
      perror(dir);
      return;
    }

    while((entry =readdir(dp))!= NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
          continue;
        }

        if(strlen(dir) +strlen(entry->d_name) + 2>sizeof(path))
        {
            fprintf(stderr, "path too long\n");
        }
        else
        {
            sprintf(path, "%s/%s", dir,entry->d_name);
            (*fcn)(path);
        }
    }

    closedir(dp);
}

int main(int argc,char *argv[])
{
    if(argc == 1)
    {
        fsize(".");
    }
    else
    {
        while(--argc > 0)
        {
          fsize(*++argv);
        }
    }

    return 0;
}
