#include <stdio.h>
int main()
{   //�ɮ׫��� fout=fopen("�ɦW","�Ҧ�"); �}�ɮ�
    FILE*fout=fopen("file.txt","w");  //w:write
    printf("Hello World\n");
    fprintf(fout,"Hello World�b�ɮ׸�\n");
}
