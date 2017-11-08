#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int inputs=6;


int i;
int j;


/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
Of course you will almost certainly need other functions.

You may vary this program provided it reads 6 formulas in a file called "input.txt" and outputs in the way indicated below to a file called "output.txt".
*/

int isProp(char c)
{
    if (c == 'p' || c == 'q' || c == 'r') 
        return 1;
    return 0;
}
int isNegation(char *g)
{
    if (g[0] == '-')
        return 1;
    return 0;
}


int isBinary(char *g)
{
    if (g[0] == '(')
        return 1;
    return 0;
}


int isValid(char *g)
{
    if (isProp(g[0]) && g[1] == '\0')
        return 1;
    if (isNegation(g)){
        printf("here \n");
        int length = strlen(g);
        char *c = (char*)malloc(sizeof(char) * (length -1));
        int i;
        for (i = 0; i < length; i++)
            c[i] = g[i + 1];
        c[i] = '\0'; // flag here
        return isValid(c);
    }
    if (g[0] == '(' && g[strlen(g) - 1] == ')')
    {
        int operatorIndex = -1;
        int openParentheses = 0;
        int length = strlen(g);
        int i;
        for (i = 1; i < length; i++)
        {
            if (g[i] == '(') openParentheses++;
            if (g[i] == ')') openParentheses--;
            if (g[i] == 'v' || g[i] == '>' || g[i] == '^')
            {
                if (!openParentheses)
                {
                    operatorIndex = i;
                    break;
                }
            }
        }
        if (operatorIndex == -1) return 0;
        char *c = (char*)malloc(sizeof(char) * (operatorIndex - 1));
        char *d = (char*)malloc(sizeof(char) * (length -operatorIndex - 2));
        for (i = 0; i < operatorIndex - 1; i++)
            c[i] = g[i+1];
        c[i] = '\0';
        for (i = 0; i < length - operatorIndex - 2; i++)
            d[i] = g[i + operatorIndex + 1];
        d[i] = '\0';
        return isValid(c) && isValid(d);
    }
    return 0;
}



int parse(char *g)
{
	if (isValid(g)){
        if (isProp && g[1] == '\0')
            return 1;
        if (isNegation(g))
            return 2;
        if (isBinary(g))
            return 3;
    }
    return 0;
}


int main()
{ /*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/



  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
 
  /*lets check your parser*/
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
	{
	case(0):fprintf(fpout,"%s is not a formula\n", names[i]);break;
	case(1):fprintf(fpout,"%s is a proposition\n",names[i]);break;
	case(2):fprintf(fpout,"%s is a negation\n",names[i]);break;
	case(3):fprintf(fpout,"%s is a binary formula\n",names[i]);break;
	default:fprintf(fpout,"%s is not a formula\n",names[i]);break;
	}
    }
 
 
  fclose(fp);
  fclose(fpout);
 
  return(0);
}