#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int delete_lastline(char *path)
{
    FILE *fp;
    int ch;
    int cnt=1;
    long filelength;
    int nnum=0;
    int filemody;
    //struct stat sfilelength;
    //int slen;
    //stat(path,&sfilelength);
    //slen=sfilelength.st_size;
    fp=fopen(path,"rw");
    if(fp==NULL)
    {
        printf("Open %s error!\n",path);
        return -1;
    }
    fseek(fp,-1,SEEK_END);
    filelength=ftell(fp)+1;
    printf("fseek length = %ld",filelength);
    while(cnt<=filelength)
    {
        ch=fgetc(fp);
        printf("NO %d : ch= %c\n",cnt,ch);
        if(ch=='\n')
        {
            nnum++;
            if(nnum==2)
                break;
        }
        fseek(fp,-2,SEEK_CUR);
        //if(cnt==12)
        //{
        //fseek(fp,-2,SEEK_CUR);
        //fseek(fp,-2,SEEK_CUR);
        //    ch=fgetc(fp);
        //    printf("interesting: %c\n",ch);
        //}
        cnt++;
    }
    printf("cnt = %d",cnt);
    filemody=filelength-(cnt-1);
    printf("filemody=%d",filemody);
    fseek(fp,0,SEEK_SET);
    truncate(path,filemody);
    if(fclose(fp)!=0)
        printf("close failed.");
    //ch=fgetc(fp);
    //putchar(ch);
    //filelength=ftell(fp)+1;
    //printf("ftell: file length is %ld\n",filelength);
    //printf("stat: file length is %d\n",slen);
    return 0;
}

int main(int argc,char *argv[])
{
    char *path=argv[1];
    delete_lastline(path);
    return 0;
}
