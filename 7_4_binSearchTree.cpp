//相同二叉搜索树的判定
#include <iostream>
#include <stack>

using namespace std;

template <class T>
class TreeNode{
    public:
        T data;
        TreeNode<T>* left;
        TreeNode<T>* right;
        TreeNode(){left = nullptr;right = nullptr;};
        ~TreeNode(){delete left;delete right;}; 
};

template <class T>
bool checkTree(TreeNode<T>* tree1,TreeNode<T>* tree2){
    //检查两棵树是否完全相同
    TreeNode<T>* p1 = tree1,* p2 = tree2;
    stack<TreeNode<T>*> s1,s2;
    while(true){
        if(p1->data != p2->data){
            return false;
        }
        if(p1->left != nullptr && p1->left != nullptr && p2->left != nullptr && p2->right != nullptr){
            //如果左右都还有节点
            //则把右节点入栈，去左节点
            s1.push(p1->right); s2.push(p2->right);
            p1 = p1->left; p2 = p2->left;
        }else if(p1->left == nullptr && p1->right == nullptr && p2->left == nullptr && p2->right == nullptr){
            //如果都没有节点
            if(!s1.empty()){
                //栈不空，就从栈里取出来
                p1 = s1.top();p2 = s2.top();
                s1.pop();s2.pop();
            }else{
                //栈空了，说明完全一样
                return true;
            }
        }else if(p1->left != nullptr && p1->right == nullptr && p2->left != nullptr && p2->right == nullptr){
            //如果左边不空而右边空，去左边
            p1 = p1->left;
            p2 = p2->left;
        }else if(p1->left == nullptr && p1->right != nullptr && p2->left == nullptr && p2->right != nullptr){
            //如果左边空而右边不空，去右边
            p1 = p1->right;
            p2 = p2->right;
        }else{
            //其他情况，说明不一样
            return false;
        }
    }

}

template <class T>
void setRightPos(TreeNode<T>* root,TreeNode<T> *node){
    TreeNode<T>* p = root;
    while(p!=nullptr){
        if(node->data < p->data){
            //往左边找
            if(p->left == nullptr){
                p->left = node;
                return;
            }else{
                p = p->left;
            }
        }else{
            //往右边找
            if(p->right == nullptr){
                p->right = node;
                return;
            }else{
                p = p->right;
            }
        }
    }
}

void buildSBinTreeAndCheck(int* series,int n,int l){
    //构造树，并判断是否完全相同
    TreeNode<int>* root = new TreeNode<int>;
    root->data = series[0];
    for(int i = 1;i<n;i++){
        //构建用来被比较的初始二叉树
        TreeNode<int>* newNode = new TreeNode<int>;
        newNode->data = series[i];
        setRightPos(root,newNode);
    }
    TreeNode<int>* rroot = nullptr;
    for(int j = 1;j<l+1;j++){
        //每次重新构建一个和初始二叉树比较的二叉树
        delete rroot; //先前构建的二叉树需要释放内存
        rroot = new TreeNode<int>;
        rroot->data = series[j*n];
        for(int i = 1;i<n;i++){
            TreeNode<int>* newNode = new TreeNode<int>;
            newNode->data = series[j*n+i];
            setRightPos(rroot,newNode); //调用函数，找到对应的位置
        }
        bool flag = checkTree(root,rroot); //检查比较是否完全相同
        if(flag){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
}

int main(){
    int n = 0,l = 0;
    int *series = nullptr;
    while(true){
        cin>>n;
        if(n==0){
            //遇到n = 0就退出
            break;
        }else{
            cin>>l;
            delete[] series; //删除原有的序列，释放内存
            series = new int[n*(l+1)]; //用一元数组表示二元数组
            for(int i=0;i<n*(l+1);i++){
                cin>>series[i];
            }
        }
        buildSBinTreeAndCheck(series,n,l);
    }
    return 0;
}
