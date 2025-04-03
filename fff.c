#include<stdio.h>
#include<string.h>
#include<ctype.h>
char input[10][100];
char ans[10][100];
char id[10];
int n;
void first(char c,int y)
{
    int j=strlen(ans[y]);
    int x=-1;
    for(int i=0;i<n;i++)
    {
        if(c==id[i])
        {
            x=i;
            break;
        }
    }
    for(int i=0;i<strlen(ans[x]);i++)
    {
        ans[y][j+i]=ans[x][i];
    }
}
void cfg()
{
    
    for(int i=0;i<n;i++)
    {
        int j=0;
        ans[i][j++]=input[i][3];
        for(int x=3;x<strlen(input[i]);x++)
        {
            if(input[i][x]=='|')
            {
                ans[i][j++]=input[i][++x];
                ans[i][j]='\0';
                break;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<strlen(ans[i]);j++)
        {
            printf("%c ",ans[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<strlen(ans[i]);j++)
        {
            if(ans[i][j]>=65&&ans[i][j]<=91)
            {
                first(ans[i][j],i);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        char ch[100];
        int x=0;
        for(int j=0;j<strlen(ans[i]);j++)
        {
            if(ans[i][j]>=95&&ans[i][j]<=122)
            {
                if(x==0)
                {
                    ch[x++]=ans[i][j];
                }
                else{
                    int f=0;
                    for(int l=0;l<x;l++)
                    {
                        if(ch[l]==ans[i][j])
                        {
                            f=1;
                            break;
                        }
                    }
                    if(f==0)
                    ch[x++]=ans[i][j];
                }

            }
        }
        printf("first of %c: ",id[i]);
        for(int l=0;l<x;l++)
        printf("%c ",ch[l]);
        printf("\n");
    }
}
int main()
{
    scanf("%d",&n);
    n++;
    for(int i=0;i<n;i++){
        fgets(input[i],sizeof(input[i]),stdin);
        input[i][strcspn(input[i],"\n")]='\0';
        id[i]=input[i][0];
    }
    cfg();
}