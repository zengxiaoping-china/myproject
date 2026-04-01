#include<stdio.h>

int main(){
    FILE *fp=NULL;
    remove("test.txt");

    fp = fopen("test.txt","w+");
    if(fp==NULL){
        printf("Error in opening file\n");
    }

    fprintf(fp,"This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n",fp);
    fclose(fp);

    FILE *fp2=NULL;
    fp2 = fopen("test.txt","r");
    if(fp2==NULL){
        printf("Error in opening file\n");
    }
    char ch[255];
    fscanf(fp2,"%s",ch);
    printf("%s\n\n",ch);
    fgets(ch,255,fp2);
    printf("%s\n",ch);
    fgets(ch,255,fp2);
    printf("%s\n",ch);
    fclose(fp2);

    return 0;
}