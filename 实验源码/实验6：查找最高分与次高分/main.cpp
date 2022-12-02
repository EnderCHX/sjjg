#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int num;
    int score;
}Person;

int random(int max, Person *check, int n)//生成0-max的不重复随机数
{
    int rand_num;
    while(true)
    {
        rand_num = rand() % (max+1);
        bool flag = false;
        for(int i = 0; i < n; i++)
        {
            if(check[i].score == rand_num)
            {
                flag = true;
                break;
            }
        }
        if(flag){continue;}
        else{break;}
    }
    return rand_num;
}

void Find_Max(Person *arr, int n)
{
    int i;
    int max1, max2, max1_num, max2_num;
    max1 = 0;
    for(i = 0; i < n; i++)
    {
        if(max1 < arr[i].score)
        {
            max1 = arr[i].score;
            max1_num = i;
        }
    }
    max2 = 0;
    for(i = 0; i < n; i++)
    {
        if(max2 < arr[i].score && arr[i].score < max1)
        {
            max2 = arr[i].score;
            max2_num = i;
        }
    }
    cout << "顺序查找：" << endl;
    printf("最高分：%3d，编号：%3d\n最低分：%3d，编号：%3d\n",  arr[max1_num].score, arr[max1_num].num, arr[max2_num].score, arr[max2_num].num);
}

void Tournament(Person arr[], int len)
{
    int k = log2(len);//k为比赛场次
    int p = 1, q;//p表示和比赛对手的间隔，q表示两场比赛的间隔
    for (int i = 0; i < k; i++) //i可表示当前比赛的小跟班个数
    {
        q = p * 2;//两场比赛的间隔是和对手间隔的两倍
        for (int j = 0; j < len; j += q)//模拟每场比赛
        {
            if (arr[j].score < arr[j + p].score)//如果后面的大
            {
                for (int t = 0; t < i + 1; t++)//比赛的数字和他的小跟班一起交换，所以是交换i+1次
                {
                    Person temp = arr[j + t];
                    arr[j + t] = arr[j + p + t];
                    arr[j + p + t] = temp;
                }
            }
            Person temp = arr[j + p];//把进行比较的数字中后者换到前者后面做跟班
            arr[j + p] = arr[j + i + 1];
            arr[j + i + 1] = temp;
        }
        p = q;//上一场比赛的间隔等于下一场比赛和对手的间隔
    }
    Person max1 = arr[0]; //最大的被换到开头
    Person max2 = arr[1]; //第二大的在最大的跟班中产生
    for (int i = 1; i <= k; i++)
        if (arr[i].score > max2.score)
            max2 = arr[i];
    cout << "锦标赛法：" << endl;
    printf("最高分：%3d，编号：%3d\n最低分：%3d，编号：%3d\n",  max1.score, max1.num, max2.score, max2.num);
}

void max_heap(Person *arr, int start, int end) {
    //建立父节点指标和子节点指标
    int father = start;
    int son = father * 2 + 1;
    while (son <= end) //若子节点指标在范围内才做比较
    { 
        if (son + 1 <= end && arr[son].score < arr[son + 1].score) //先比较两个子节点大小，选择最大的
            son++;
        if (arr[father].score > arr[son].score) //如果父节点大于子节点代表调整完毕，直接跳出函数
        {    
            return;
        }
        else //否则交换父子内容再继续子节点和孙节点比较
        { 
            swap(arr[father], arr[son]);
            father = son;
            son = father * 2 + 1;
        }
    }
}

void heap(Person *arr, int len) {
    //初始化，i从最后一个父节点开始调整
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heap(arr, i, len - 1);
    // 先将第一个元素和已经排好的元素前一位做交换，再从新调整刚调整的元素之前的元素，直到排序完毕
    for (int i = len - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        max_heap(arr, 0, i - 1);
    }
    cout << "堆排序：" << endl;
    printf("最高分：%3d，编号：%3d\n最低分：%3d，编号：%3d\n", arr[len-1].score, arr[len-1].num, arr[len-2].score, arr[len-2].num);
}

int main()
{
    Person * players = new Person[512];
    srand((int)time(0));
    for(int i = 0; i < 512; i++)
    {
        players[i].score = random(999, players, i);
        players[i].num = i + 1;
        printf("\033[34m\033[1m%4d：%-4d\033[0m", players[i].num, players[i].score);
        if((i+1) % 8 == 0) cout << endl;
    }
    cout << "\033[33m";
    Find_Max(players, 512);
    cout << "\033[0m\033[32m";
    Tournament(players, 512);
    cout << "\033[0m\033[35m";
    heap(players, 512);
    cout << "\033[0m";
}
