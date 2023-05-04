#include <stdio.h>
int main()
{   //檔案指標 fout=fopen("檔名","模式"); 開檔案
    FILE*fout=fopen("file.txt","w");  //w:write
    printf("Hello World\n");
    fprintf(fout,"Hello World在檔案裡\n");
}
