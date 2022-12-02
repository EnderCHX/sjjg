#include <bits/stdc++.h>
using namespace std;

typedef struct Node
{
	int weight;                 //权值
	int parent;                 //父节点的序号，为-1的是根节点
	int lchild, rchild;         //左右孩子节点的序号，为-1的是叶子节点
    char data;                  //字符
    string code;                //字符编码
}HTNode, *HuffmanTree;          //用来存储赫夫曼树中的所有节点

void Get_min(HuffmanTree HT, int &min1, int &min2)
{
    int i = 0, tmp;
    while(HT[i].parent != -1) i++;
    tmp = HT[i].weight;
    min1 = i;
    for(; HT[i].weight > 0; i++)
    {
        if(HT[i].parent == -1 && HT[i].weight < tmp)
        {
            tmp = HT[i].weight;
            min1 = i;
        }
    }
    HT[min1].parent = 1;

    i = 0;
    while(HT[i].parent != -1) i++;
    tmp = HT[i].weight;
    min2 = i;
    for(; HT[i].weight > 0; i++)
    {
        if(HT[i].parent == -1 && HT[i].weight < tmp)
        {
            tmp = HT[i].weight;
            min2 = i;
        }
    }
    HT[min1].parent = 1;
}

HuffmanTree Get_HuffmanTree(string chars,int *weights, int n)
{
    int total = 2*n-1;
    HuffmanTree HT = new HTNode[total];
    int i;
    for(i = 0; i < n; i++)
    {
        HT[i].weight = weights[i];
        HT[i].data = chars[i];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for(; i< total; i++)
    {
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    int min1, min2;
    for(i = n; i < total; i++)
    {
        Get_min(HT,min1,min2);
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].lchild = min1;
        HT[i].rchild = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight;
    }
    return HT;
}

void Save_HuffmanTree(HuffmanTree HT, int n, string filename)
{
    ofstream file(filename);
    if(file.good())
    {
        for(int i = 0; i < n; i++)
        {
            file << HT[i].weight << " " 
                 << HT[i].parent << " " 
                 << HT[i].lchild << " " 
                 << HT[i].rchild << endl;
        }
        file.close();
        cout << "写入成功! " << filename << endl;
    }
    else
    {
        cout << "写入失败! " << filename << endl;
    }
}

HuffmanTree Read_HufTree(string filename)
{
    HuffmanTree HT;
    ifstream file(filename);
    if(file.good())
    {
        int i = 0, tmp;
        while(!file.eof())
        {
            file >> tmp;
            i++;
        }
        file.close();
        int n = i / 4;
        file.open(filename);
        HT = new HTNode[n];
        for(i = 0; i < n; i++)
        {
            file >> HT[i].weight
                 >> HT[i].parent
                 >> HT[i].lchild
                 >> HT[i].rchild;
        }
        file.close();
        cout << "读取成功! " << filename << endl;
    }
    else
    {
        cout << filename << " 文件不存在 " << filename << endl;
    }
    return HT;
}

string* Get_HuffmanCode(HuffmanTree HT, int n)
{
    int cur, i = 0, code_len = 0;
    cur = 2 * n - 2;
    string *HC = new string[n];
    char *code = new char[n];
    for(i = 0; i < cur + 1; i++) HT[i].weight = 0; //weight = 0 未遍历 1 遍历左孩子 2遍历右孩子
    while(cur != -1)
    {
        if(HT[cur].weight == 0)//左右孩子均未被遍历，先向左遍历  
        {
            HT[cur].weight = 1;
            if (HT[cur].lchild != -1)//如果当前节点不是叶子节点，则记下编码，并继续向左遍历
            {   
                code[code_len++] = '0';
                cur = HT[cur].lchild;
            }
            else//如果当前节点是叶子节点，则终止编码，并将其保存起来  
            {
                code[code_len] = '\0';
                HC[cur] = code;  //复制编码串  
            }
        }
        else if (HT[cur].weight == 1)//左孩子已被遍历，开始向右遍历右孩子  
        {
            HT[cur].weight = 2;
            if (HT[cur].rchild != -1)//如果当前节点不是叶子节点，则记下编码，并继续向右遍历
            {   
                code[code_len++] = '1';
                cur = HT[cur].rchild;
            }
        }
        else//左右孩子均已被遍历，退回到父节点，同时编码长度减1  
        {
            HT[cur].weight = 0;
            cur = HT[cur].parent;
            --code_len;
        }
    }
    return HC;
}

void Save_HuffmanCode(string *HC, string chars, string filename)
{
    ofstream file(filename);
    if(file.good())
    {
        for(int i = 0; i < chars.length(); i++)
        {
            file << chars[i] << " " << HC[i] << endl;
        }
        cout << "写入成功! " << filename << endl;
        file.close();
    }
    else
    {
        cout << "写入失败! " << filename << endl;
    }
}

void Save_Zip(HuffmanTree HT, string str, string filename)
{
    int len = 0;
    ofstream file1(filename, ios::trunc);
    file1.close();
    ofstream file(filename, ios::app);
    while(HT[len].data > 0) len++;
    if(file.good())
    {
        for(int i = 0; i < str.length(); i++)
        {
            for(int j = 0; j < len; j++)
            {
                if(str[i] == HT[j].data)
                {
                    file << HT[j].code ;
                }
            }
        }
        file.close();
        cout << "写入成功! " << filename << endl;
    }
    else
    {
        cout << "写入失败! " << filename << endl;
    }
}

string Unzip(string filename, HuffmanTree HT)
{
    string str;
    ifstream file(filename);
    if(file.good())
    {
        string code_read, code = "";
        file >> code_read;
        int i, j, len;
        len = code_read.length();
        for(i = 0; i < len; i++)
        {
            code += code_read[i];
            for(j = 0; HT[j].data > 0; j++)
            {
                if(HT[j].code == code)
                {
                    str += HT[j].data;
                    code = "";
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        str = "error";
    }
    return str;
}

void Save_Uzip_Str(string txt, string filename)
{
    ofstream file(filename);
    if(file.good())
    {
        file << txt << endl;
        file.close();
        cout << "写入成功! " << filename << endl;
    }
    else
    {
        cout << "写入失败! " << filename << endl;
    }
}

int main()
{
    string str, chars, str_filename;
    bool f = true;
    cout << "输入需要压缩字符串的文件：";
    cin >> str_filename;
    while(f)
    {
        ifstream file(str_filename);
        if(file.good())
        {
            string tmp; bool if_enter = false;
            while(getline(file,tmp))
            {
                if(if_enter)
                {
                    str += "\n" + tmp;
                }
                else
                {
                    str += tmp;
                    if_enter = true;
                }
            }
            file.close();
            f = false;
        }
        else
        {
            cout << "文件不存在，请重新输入：";
            cin >> str_filename;
        }
    }
    cout << str << endl;
    chars += str[0];
    for(int i = 1; i < str.length(); i++)
    {
        bool flag = true;
        for(int j = 0; j < chars.length(); j++)
        {
            if(str[i] == chars[j])
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            chars += str[i];
        }
    }
    int weights[chars.length()];
    for(int i = 0; i < chars.length(); i++)
    {
        weights[i] = 0;
        for(int j = 0; j < str.length(); j++)
        {
            if(str[j] == chars[i])
            {
                weights[i]++;
            }
        }
    }
    HuffmanTree HT = Get_HuffmanTree(chars, weights, chars.length());
    // cout << str << " " << chars << endl;
    // for(int i = 0; i < chars.length(); i++)
    // {
    //     cout << weights[i] << " " ;
    // }
    // cout << endl;
    Save_HuffmanTree(HT, 2*chars.length()-1, "HufTree.dat");
    HuffmanTree HT2 = Read_HufTree("HufTree.dat");
    string *HC = Get_HuffmanCode(HT2, chars.length());
    Save_HuffmanCode(HC, chars, "HufCode.txt");
    for(int i = 0; i < chars.length(); i++) //将字符和对应的编码写入HT
    {
        HT[i].code = HC[i];
        HT2[i].data = chars[i];
        HT2[i].code = HC[i];
    }
    // for(int i = 0; i < 2*chars.length() -1; i++)
    // {
    //     cout << HT2[i].weight << " "
    //          << HT2[i].parent << " "
    //          << HT2[i].rchild << " "
    //          << HT2[i].lchild << " "
    //          << HT2[i].data << " "
    //          << HT2[i].code << endl;
    // }
    Save_Zip(HT2, str, "CodeFile.dat");
    string uzip_str = Unzip("CodeFile.dat",HT2);
    Save_Uzip_Str(uzip_str, "uzip." + str_filename);
    pause();
}

