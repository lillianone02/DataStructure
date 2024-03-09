#include <iostream>
#include <string>
using namespace std;
const int MAX = 100000;
class Stack
{
private:
    int top; //計算陣列目前計算到哪邊
public:
    int arr[MAX];
    //constructor建構子，也就是給一開始的Stack一些初始條件
    Stack()
    {
        top = -1; //一開始先設為-1，因為我們要讓陣列從0開始。
    }
    bool isEmpty();
    void push(int val);
    int pop();  //這邊設計的pop會回傳回去我們pop的值
    int topVal();
 
};

int Stack::topVal(){
    return arr[top];
}

bool Stack::isEmpty()
{
    if(top >= 0)
        return false;
    else
        return true;//這裡注意TF的條件
}

int Stack::pop()
{
    return arr[top--]; // 後置減法，先把arr[top]的直取走之後，top在減一
}

void Stack::push(int val)
{
    arr[++top] = val; // 這邊前置加法，先把top+1 之後在執行arr[top] = val的動作   	
}
/*
//製作stack
class StackNode{
private:
    int data;
    StackNode *next;
public:
    StackNode():data(0){ next = 0;}
    StackNode(int x):data(x){ next = 0;}
    StackNode(int x, StackNode *nextNode):data(x), next(nextNode){};
    friend class StackList;
};
//實作stack功能
class StackList{
private:
    StackNode *top;
    int size;
public:
    StackList():size(0),top(0){};
    void Push(int x);
    int Pop();
    bool IsEmpty();
    int Top();
    int getSize();
};

void StackList::Push(int x){
    if(IsEmpty()){
        top = new StackNode(x);//S為空則建新點
        size++;
        return;
    }
    StackNode *newNode = new StackNode(x);
    newNode->next = top;
    top = newNode;
    size++;
}

int StackList::Pop(){
    if(IsEmpty()){
        return -1;//S為空則不做任何動作
    }
    StackNode *delNode = top;
    int val = top->data;
    top = top->next;
    delete delNode;
    size--;
    return val;
}

bool StackList::IsEmpty(){
    return (size == 0);
}

int StackList::Top(){
    if(IsEmpty()){
        return -1;
    }
    return top->data;
}

int StackList::getSize(){
    return size;
}
*/
int LVP(string s){
    class Stack st;
    int n = s.length();
    //進行括號配對
    for(int i = 0; i < n; ++i){
        if(s[i] == ')'){
            if(st.isEmpty()== 0){
                int j = st.topVal();
                st.pop();
                s[i] = '*';
                s[j] = '*';
            }
        }
        if(s[i] == '('){
            st.push(i);
        }
    }
    //計算已經正確配對的括號數量
    int ans = 0;
    for(int i=0; i<n; i++){
        if(s[i] == '*'){
            int cnt = 1;
            i++;
            while(s[i] == '*'){
                cnt++;
                i++;
            }
            i--;
            ans = max(ans, cnt);
        }
    }
    //回傳最大的長度
    return ans;
}

void Enc(int ans){
    ans /= 2;
    ans %= 26;
    ans += 97;
    cout << (char)ans;
}

int main(){
    int N; 
    cin >> N;
    while(N > 0){
        string SS;
        cin >> SS;
        int maxnum = LVP(SS);
        Enc(maxnum);
        N--;
    }
    cout << "\n";
    return 0;
}


