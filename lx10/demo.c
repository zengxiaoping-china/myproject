#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_LENGHT 20
#define FILE_NAME "students.txt"

typedef struct 
{
    int id;
    float chinese;
    float math;
    float english;
    float avargrade;
    char name[NAME_LENGHT];
}Stu;

void loadStudents(Stu **students,int *count){
    FILE *fp = fopen(FILE_NAME,"r");
    if (!fp)
    {
        printf("文件打开失败！");
        *students = NULL;
        *count = 0;
        return;
    }
    
    int lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n') lines++;
    }
    
    if (lines > 0 || ftell(fp) > 0)
    {
        rewind(fp);
        if (fgetc(fp) != EOF)
        {
            rewind(fp);
            if(lines == 0) lines = 1;
        }
        
    } else {
        lines = 0;
    }
    rewind(fp);
    
    if (lines == 0)
    {
        *students = NULL;
        *count = 0;
        fclose(fp);
        return;
    }

    *students = malloc(lines*sizeof(Stu));
    if (!*students)
    {
        fprintf(stderr,"❌ 内存分配失败！\n");
        *count = 0;
        fclose(fp);
        return;
    }
    
    char line[256];
    int i = 0;
    while (fgets(line,sizeof(line),fp))
    {
        line[strcspn(line,"\r\n")] = '\0';
        if(strlen(line) == 0) continue;
    }

    Stu s;
    char nameBuf[NAME_LENGHT];
    int items = sscanf(line,"%d|%[^|]|%f|%f|%f|%f",&s.id,s.name,&s.chinese,&s.math,&s.english,&s.avargrade);
    if (items == 6)
    {
        strncpy(s.name,nameBuf,NAME_LENGHT - 1);
        s.name[NAME_LENGHT - 1] = '\0';
        (*students)[i++] = s;
    }

    *count = i;
    fclose(fp);
    
}
