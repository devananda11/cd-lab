#include<stdio.h>
#include<ctype.h>
#include<string.h>

int keyword(char s[])
{
    char *k[]={"int","float","char","if","else","while","for","return","void"};
    int n=9;
    for(int i=0;i<n;i++)
        if(strcmp(s,k[i])==0)
            return 1;
    return 0;
}

int main()
{
    char str[1000],word[50];
    int i=0,j,ch;
    FILE *input;

    input = fopen("my_input.txt", "r");
    if (input == NULL)
    {
        perror("Unable to open input file");
        return 1;
    }

    while (i < (int)sizeof(str) - 1 && (ch = fgetc(input)) != EOF)
        str[i++] = (char)ch;
    fclose(input);
    str[i]='\0';
    i=0;

    while(str[i]!='\0')
    {
        if(str[i]==' '||str[i]=='\t'||str[i]=='\n')
        {
            i++;
            continue;
        }

        if(isalpha(str[i]))
        {
            j=0;
            while(isalnum(str[i]))
                word[j++]=str[i++];
            word[j]='\0';

            if(keyword(word))
                printf("%s : Keyword\n",word);
            else
                printf("%s : Identifier\n",word);
        }
        else if(isdigit(str[i]))
        {
            while(isdigit(str[i]))
                putchar(str[i++]);
            printf(" : Number\n");
        }
        else if(strchr("+-*/=%<>",str[i]))
        {
            printf("%c : Operator\n",str[i]);
            i++;
        }
        else if(strchr(";,(){}",str[i]))
        {
            printf("%c : Special Symbol\n",str[i]);
            i++;
        }
        else
            i++;
    }
}

