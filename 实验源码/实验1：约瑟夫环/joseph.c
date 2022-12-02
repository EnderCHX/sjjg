#include <stdio.h>
#include <stdlib.h>

/*定义链表*/
typedef struct LinkList
{
    int data;
    struct LinkList *next;
}LinkList;

/*初始化约瑟夫环*/
LinkList * InitLoop(int n)
{
    LinkList *p = (LinkList*)malloc(sizeof(LinkList));
    p->data = 1;
    p->next = NULL;
    LinkList *q, *r;
    q = p;
    for(int i = 1; i < n; i++)
    {
        LinkList *s = (LinkList*)malloc(sizeof(LinkList));
        s->data = i+1;
        s->next = NULL;
        q->next = s;
        q = q->next;
    }
    r = q;
    q->next = p;
    return r;//返回最后元素地址
}

/*输出出圈顺序*/
void OutPut(LinkList *L, int m)
{
    if(!L) exit(0);
    LinkList *p, *q; p = L;
    int i;
    while(p->next !=p)
    {
        for(i = 1;i<m;i++){p = p->next;}
        printf("%d ", p->next->data);
        q = p->next;
        p->next = p->next->next;
        free(q);
    }
    printf("%d\n", p->data);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    LinkList *L = InitLoop(n);
    OutPut(L, m);
    return 0;
}