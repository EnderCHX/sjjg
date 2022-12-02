#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 100
#define INCREMENT 10

typedef struct {
  char *base;
  char *top;
  int size;
} OpStack;

typedef struct {
  double *base;
  double *top;
  int size;
} NuStack;

OpStack InitOpStack() 
{
  OpStack p;
  p.base = (char *)malloc(INIT_SIZE * sizeof(char));
  p.top = p.base;
  p.size = INIT_SIZE;
  return p;
}

NuStack InitNuStack() 
{
  NuStack p;
  p.base = (double *)malloc(INIT_SIZE * sizeof(double));
  p.top = p.base;
  p.size = INIT_SIZE;
  return p;
}

void PushOp(OpStack &p, char ch) 
{
  if (p.top - p.base >= p.size)
  {
    p.base = (char *)realloc(p.base, (p.size + INCREMENT) * sizeof(char));
    p.top = p.base + p.size;
    p.size += INCREMENT;
  }
  *p.top = ch;
  p.top++;
}

void PushNu(NuStack &p, double ch) 
{
  if (p.top - p.base >= p.size)
  {
    p.base = (double *)realloc(p.base, (p.size + INCREMENT) * sizeof(double));
    p.top = p.base + p.size;
    p.size += INCREMENT;
  }
  *p.top = ch;
  p.top++;
}

char PopOp(OpStack &p) 
{
  if (p.base == p.top)
    return 0;
  char ch = *(p.top - 1);
  p.top--;
  return ch;
}

double PopNu(NuStack &p) 
{
  if (p.base == p.top)
    return 0;
  double ch = *(p.top - 1);
  p.top--;
  return ch;
}

char GetopOp(OpStack &p) 
{
  if (p.top == p.base)
  {
    return 0;
  }
  else
  {
    return *(p.top - 1);
  }
}

double GetopNu(NuStack &p) 
{
  if (p.top == p.base)
  {
    return 0;
  }
  else
  {
    return *(p.top - 1);
  }
}

char Precede(char a, char b) 
{
  int i, j;
  char pre[][8] = {/*运算符之间的优先级制作成一张表格*/
                   {'>', '>', '<', '<', '<', '>', '>', '<'},
                   {'>', '>', '<', '<', '<', '>', '>', '<'},
                   {'>', '>', '>', '>', '<', '>', '>', '>'},
                   {'>', '>', '>', '>', '<', '>', '>', '>'},
                   {'<', '<', '<', '<', '<', '=', '0', '<'},
                   {'>', '>', '>', '>', '0', '>', '>', '>'},
                   {'<', '<', '<', '<', '<', '0', '=', '<'},
                   {'>', '>', '>', '>', '<', '>', '>', '>'}};
  switch (a) {
  case '+':i = 0;break;
  case '-':i = 1;break;
  case '*':i = 2;break;
  case '/':i = 3;break;
  case '(':i = 4;break;
  case ')':i = 5;break;
  case '#':i = 6;break;
  case '%':i = 7;break;}
  switch (b) {
  case '+':j = 0;break;
  case '-':j = 1;break;
  case '*':j = 2;break;
  case '/':j = 3;break;
  case '(':j = 4;break;
  case ')':j = 5;break;
  case '#':j = 6;break;
  case '%':j = 7;break;}
  return pre[i][j];
}

int prio(char op) //给运算符优先级排序
{
  int priority;
  if (op == '*' || op == '/' || op == '%')
    priority = 2;
  if (op == '+' || op == '-')
    priority = 1;
  if (op == '(' || op == ')' || op == '#')
    priority = 0;
  return priority;
}

double Operate(double i, char b, double j)
{
  double result;
  switch (b) {
  case '+':result = i + j;break;
  case '-':result = i - j;break;
  case '*':result = i * j;break;
  case '/':result = i / j;break;
  case '%':result = fmod(i, j);break;
  }
  return result;
}

void Infix()
{
  OpStack OPTR = InitOpStack(); //运算符栈
  NuStack OPND = InitNuStack(); //运算数栈
  PushOp(OPTR, '#');
  char chx, op;
  double num;
  int i, j;
  printf("输入中缀表达式(以#结束,不加=):\n");
  scanf("%c", &chx);
  while (chx != '#' || GetopOp(OPTR) != '#')
  {
    num = 0;
    i = 0;
    char tmpn[100];
    while (chx <= '9' && chx >= '0' || chx == '.')
    {
      tmpn[i] = chx;
      scanf("%c", &chx);
      i++;
    }
    if (i)
    {
      num = atof(tmpn);
      PushNu(OPND, num);
      for (int j = 0; j < i; j++) tmpn[j] = '\0';
    }
    switch (Precede(GetopOp(OPTR), chx))
    {
    case '<':
      PushOp(OPTR, chx);
      scanf("%c", &chx);
      break;
    case '>':
      op = PopOp(OPTR);
      double a, b;
      b = PopNu(OPND);
      a = PopNu(OPND);
      PushNu(OPND, Operate(a, op, b));
      break;
    case '=':
      PopOp(OPTR);
      scanf("%c", &chx);
      break;
    }
  }
  printf("%g\n", GetopNu(OPND));
}

void Polish() 
{
  NuStack OPND = InitNuStack(); //运算数栈
  char chx[1000];
  double num;
  printf("输入前缀表达式(以#结束,不加=):\n");
  scanf("%[^\n]", chx);
  char *q = chx;
  while (*q != '#') q++;
  while (q != chx)
  {
    num = 0;
    char tmpn[100], tmpnn[100]; //tmpnn反转tmpn
    int j = 0;
    while (*q <= '9' && *q >= '0' || *q == '.')
    {
      tmpn[j] = *q;
      q--;
      j++;
    }
    if (j)
    {
      for (int i = 0; i < j; i++)
      {
        tmpnn[i] = tmpn[j - i - 1];
      }
      num = atof(tmpnn);
      PushNu(OPND, num);
      for (int k = 0; k < j; k++)
      {
        tmpn[k] = '\0';
        tmpnn[k] = '\0';
      }
    }
    if (*q == '+' || *q == '-' || *q == '*' || *q == '/' || *q == '%')
    {
      double a, b;
      a = PopNu(OPND);
      b = PopNu(OPND);
      PushNu(OPND, Operate(a, *q, b));
      q--;
    }
    q--;
  }
  double a, b;
  a = PopNu(OPND);
  b = PopNu(OPND);
  PushNu(OPND, Operate(a, *q, b));
  printf("%g\n", GetopNu(OPND));
}

void RePolish() 
{
  OpStack OPTR = InitOpStack(); //运算符栈
  NuStack OPND = InitNuStack(); //运算数栈
  char chx;
  double num;
  int i, j;
  printf("输入后缀表达式(以#结束,不加=):\n");
  scanf("%c", &chx);
  while (chx != '#') 
  {
    num = 0;
    i = 0;
    char tmpn[100];
    if (chx == '+' || chx == '-' || chx == '*' || chx == '/' || chx == '%')
    {
      PushNu(OPND, Operate(PopNu(OPND), chx, PopNu(OPND)));
    } else {
      while (chx <= '9' && chx >= '0' || chx == '.')
      {
        tmpn[i] = chx;
        scanf("%c", &chx);
        i++;
      }
      if (i)
      {
        num = atof(tmpn);
        PushNu(OPND, num);
        for (int j = 0; j < i; j++) tmpn[j] = '\0';
      }
    }
    scanf("%c", &chx);
  }
  printf("%g\n", GetopNu(OPND));
}

void Infix_to_Polish()
{
  OpStack OPTR = InitOpStack();  //运算符栈
  OpStack OPTR2 = InitOpStack(); //中间结果
  PushOp(OPTR, '#');
  PushOp(OPTR2, '#');
  char chx[1000];
  printf("中缀->前缀:\n输入中缀表达式(以#结束,不加=):\n");
  scanf("%[^\n]", chx);
  int n = strlen(chx) - 2;
  while (n != -1)
  {
    int i = 0;
    while (chx[n] <= '9' && chx[n] >= '0' || chx[n] == '.')
    {
      PushOp(OPTR2, chx[n]);
      --n;
      i++;
    }
    if (i) PushOp(OPTR2, '|');
    if (chx[n] == ')')
    {
      PushOp(OPTR, chx[n]);
      --n;
    }
    if (chx[n] == '(')
    {
      while (GetopOp(OPTR) != ')') PushOp(OPTR2, PopOp(OPTR));
      PopOp(OPTR);
      --n;
    }
    if (chx[n] == '+' || chx[n] == '-' || chx[n] == '*' || chx[n] == '/' || chx[n] == '%')
    {
      if (prio(chx[n]) >= prio(GetopOp(OPTR)))
      {
        PushOp(OPTR, chx[n]);
        --n;
      } else if (prio(chx[n]) < prio(GetopOp(OPTR)))
      {
        PushOp(OPTR2, PopOp(OPTR));
      }
    }
  }
  while(GetopOp(OPTR) != '#')
  {
    if(OPTR.top - OPTR.base != 2)
    {
      printf("%c ", PopOp(OPTR));
    }
    else
    {
      printf("%c", PopOp(OPTR));
    }
  }
  while (GetopOp(OPTR2) != '#')
  {
    if (GetopOp(OPTR2) == '|')
    {
      PopOp(OPTR2);
      printf(" ");
    }
    if(GetopOp(OPTR2) <= '9' && GetopOp(OPTR2) >= '0' || GetopOp(OPTR2) == '.')
    {
      printf("%c", PopOp(OPTR2));
    }
    else
    {
       printf(" %c", PopOp(OPTR2));
    }
  }
  printf("\n");
}

void Infix_to_RePolish() 
{
    OpStack OPTR = InitOpStack(); //运算符栈
    PushOp(OPTR, '#');
    char chx;
    double num;
    int i, j;
    printf("中缀->后缀:\n输入中缀表达式(以#结束,不加=):\n");
    scanf("%c", &chx);
    while (chx != '#')
    {
        if (chx == ' ')
        {
            scanf("%c", &chx);
        }
        num = 0;
        i = 0;
        char tmpn[100];
        while (chx <= '9' && chx >= '0' || chx == '.')
        {
            tmpn[i] = chx;
            scanf("%c", &chx);
            i++;
        }
        if (i)
        {
            num = atof(tmpn);
            printf("%g ", num);
            for (int j = 0; j < i; j++) tmpn[j] = '\0';
        }
        if (chx == ')')
        {
            while (GetopOp(OPTR) != '(') printf("%c ", PopOp(OPTR));
            PopOp(OPTR);
            scanf("%c", &chx);
        }
        if (chx == '(')
        {
            PushOp(OPTR, chx);
            scanf("%c", &chx);
        }
        if (chx == '+' || chx == '-' || chx == '*' || chx == '/' || chx == '%')
        {
            if (prio(chx) > prio(GetopOp(OPTR)))
            {
                PushOp(OPTR, chx);
                scanf("%c", &chx);
            } else if (prio(chx) <= prio(GetopOp(OPTR)))
            {
                printf("%c ", PopOp(OPTR));
            }
        }
    }
    while (GetopOp(OPTR) != '#')
    {
        printf("%c ", PopOp(OPTR));
    }
    printf("\n");
}

int main() {
  // Infix();
  // Polish();
  // RePolish();
  // Infix_to_Polish();
  // Infix_to_RePolish();
  return 0;
}
