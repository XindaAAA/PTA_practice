//树的同构

#include <iostream>
#include <stack>
using namespace std;
template <class T>
class TNode{
    //定义树形节点类
    public:
        T data;
        TNode<T>* leftChild;
        TNode<T>* rightChild;
        TNode(){leftChild = nullptr;rightChild=nullptr;}
        ~TNode(){delete data;}
};

template <class T>
TNode<T>* CreateTree(){
    //根据输入创建树
    TNode<T>* tree = nullptr;
    int n = 0;
    cin>>n;
    T* data = new T[n];
    int* left = new int[n];
    int* right = new int[n];
    for(int i = 0;i<n;i++){
        //将各节点信息存储到数组中
        char leftchar = ' ';
        char rightchar = ' ';
        cin>>data[i]>>leftchar>>rightchar;
        if(leftchar=='-'){
            left[i] = -1; //若子节点索引为-1，则表示没有对应的子节点
        }else{
            left[i] = leftchar - '0';
        }
        if(rightchar=='-'){
            right[i] = -1;
        }else{
            right[i] = rightchar - '0';
        }
    }
    
    TNode<T>* treeNode[n];
    for(int i = 0;i<n;i++){
        //为每个节点创建一个树形节点类型
        treeNode[i] = new TNode<T>;
        treeNode[i]->data = data[i];
    }
    for(int i = 0;i<n;i++){
        //构造节点间的父子关系
        if(left[i]!=-1){
            treeNode[i]->leftChild = treeNode[(left[i])];
        }
        if(right[i]!=-1){
            treeNode[i]->rightChild = treeNode[(right[i])];
        }
    }
    //寻找根节点位置
    int i = 0; 
    while(i<n){
        int j = 0;
        for(j;j<n;j++){
            if(i == left[j] || i == right[j]){
                break;
            }
        }
        if(j==n){
            //i为根节点所在位置
            break;
        }
        i++;
    }
    // cout<<"根节点位置："<<i<<endl;
    tree = treeNode[i];
    return tree;
}

int main(){
    auto tree1 = CreateTree<char>();
    auto tree2 = CreateTree<char>();
    auto p1 = tree1; auto p2 = tree2;
    stack<TNode<char>*> s1; //创建一个指针类型的栈，存放tree1的指针
    stack<TNode<char>*> s2; //创建一个指针类型的栈，存放tree2的指针

    while(p1!=nullptr && p2!=nullptr){
        if(p1->data != p2->data){
            cout<<"No";
            // cout<<p1->data<<" "<<p2->data;
            return 0;
        }
        if(p1->leftChild!=nullptr && p1->rightChild != nullptr && p2->leftChild!=nullptr && p2->rightChild != nullptr){
            //如果左右都还有结点
            if(p1->leftChild->data != p2->leftChild->data || p1->rightChild->data != p2->rightChild->data){
                auto t = p2->leftChild;
                p2->leftChild = p2->rightChild;
                p2->rightChild = t;
                //让tree2对调p2处的左右节点
            }
            if(p1->leftChild->data != p2->leftChild->data || p1->rightChild->data != p2->rightChild->data){
                //如果对调后还是不对，输出否定结果
                cout<<"No";
                return 0;
            }
            //如果没问题，把右边入栈，到时候要回头看的，然后往左边搜索
            s1.push(p1->rightChild);
            s2.push(p2->rightChild);
            p1 = p1->leftChild;
            p2 = p2->leftChild;
        }else if(p1->leftChild != nullptr && p1->rightChild == nullptr && p2->leftChild != nullptr && p2->rightChild == nullptr){
            //如果只有左边有节点，往左走
            p1 = p1->leftChild;
            p2 = p2->leftChild;
        }else if(p1->leftChild == nullptr && p1->rightChild != nullptr && p2->leftChild == nullptr && p2->rightChild != nullptr){
            //如果只有右边有节点，往右走
            p1 = p1->rightChild;
            p2 = p2->rightChild;
        }else if(p1->leftChild == nullptr && p1->rightChild == nullptr && p2->leftChild == nullptr && p2->rightChild == nullptr){
            //如果都没有节点，看看栈里有没有，没有就是对的，有就是回头
            if(!s1.empty()){
                p1 = s1.top();s1.pop(); //出栈
                p2 = s2.top();s2.pop(); //出栈
            }
            else{
                cout<<"Yes";
                return 0;
            }
        }else{
            //其他情况下
            //如果两棵树的子节点位置不一样，可能交换一下就是同构树，因此尝试交换
            auto t = p2->leftChild;
            p2->leftChild = p2->rightChild;
            p2->rightChild = t;
            if(p1->leftChild != nullptr){
                if(p2->leftChild != nullptr && p2->leftChild->data == p1->leftChild->data){
                    //若交换后节点值相同，则继续搜索
                    p1 = p1->leftChild;
                    p2 = p2->leftChild;
                    continue;
                }else{
                    //否则说明不是同构树
                    cout<<"No";
                    return 0;
                }
            }else if(p1->rightChild != nullptr){
                if(p2->rightChild != nullptr && p2->rightChild->data == p1->rightChild->data){
                    p1 = p1->rightChild;
                    p2 = p2->rightChild;
                    continue;
                }else{
                    cout<<"No";
                    return 0;
                }
            }
            cout<<"No";
            return 0;
        }
    }

    return 0;
}