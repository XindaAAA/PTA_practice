//一元多项式的加法与乘法运算

#include <iostream>
#include <list>
using namespace std;

void add(list<int>* p_coef1,list<int>* p_coef2,list<int>* p_degree1,list<int>* p_degree2,list<int>** p_rescoef,list<int>** p_resdegree){
    list<int>::iterator it1_d = (*p_degree1).begin();
    list<int>::iterator it2_d = (*p_degree2).begin();
    list<int>::iterator it1_c = (*p_coef1).begin();
    list<int>::iterator it2_c = (*p_coef2).begin();
    list<int>* rescoef = new list<int>;
    list<int>* resdegree = new list<int>;
    bool flag = true;
    while(flag){
        if(it1_d != (*p_degree1).end() && it2_d != (*p_degree2).end()){
            if((*it1_d)==(*it2_d)){
                if((*it1_c)+(*it2_c)!=0){
                    (*rescoef).push_back((*it1_c)+(*it2_c));
                    (*resdegree).push_back(*it1_d);
                }
                it1_c++;it1_d++;it2_c++;it2_d++;
            }else if((*it1_d)>(*it2_d)){
                (*rescoef).push_back(*it1_c);
                (*resdegree).push_back(*it1_d);
                it1_c++;it1_d++;
            }else if((*it1_d)<(*it2_d)){
                (*rescoef).push_back(*it2_c);
                (*resdegree).push_back(*it2_d);
                it2_c++;it2_d++;
            }
        }

        if(it1_d == (*p_degree1).end()){
            for(it2_d;it2_d!=(*p_degree2).end();it2_d++){
                (*rescoef).push_back(*it2_c);
                (*resdegree).push_back(*it2_d);
                // n++;
                it2_c++;
            }
            flag = false;
        }else if(it2_d == (*p_degree2).end()){
            for(it1_d;it1_d!=(*p_degree1).end();it1_d++){
                (*rescoef).push_back(*it1_c);
                (*resdegree).push_back(*it1_d);
                // n++;
                it1_c++;
            }
            flag = false;
        }
    }
    delete(*p_rescoef);
    delete(*p_resdegree);
    (*p_rescoef) = rescoef;
    (*p_resdegree) = resdegree;

}
void multi(list<int>* p_coef1,list<int>* p_coef2,list<int>* p_degree1,list<int>* p_degree2,list<int>** p_rescoef,list<int>** p_resdegree){
    list<int>::iterator it1_d = (*p_degree1).begin();
    list<int>::iterator it2_d = (*p_degree2).begin();
    list<int>::iterator it1_c = (*p_coef1).begin();
    list<int>::iterator it2_c = (*p_coef2).begin();
    list<int>* rescoef = new list<int>;
    list<int>* resdegree = new list<int>;
    list<int> tcoef;
    list<int> tdegree;
    while(it1_d != (*p_degree1).end()){
        it2_d = (*p_degree2).begin();
        it2_c = (*p_coef2).begin();
        while(it2_d != (*p_degree2).end()){
            tcoef.push_back((*it1_c)*(*it2_c));
            tdegree.push_back((*it1_d)+(*it2_d));
            it2_d++;it2_c++;
        }
        add(&tcoef,rescoef,&tdegree,resdegree,&rescoef,&resdegree);
        tcoef.clear();
        tdegree.clear();
        it1_d++;it1_c++;
    }
    delete(*p_rescoef);
    delete(*p_resdegree);
    (*p_rescoef) = rescoef;
    (*p_resdegree) = resdegree;
}
void output(list<int>* p_coef,list<int>* p_degree){
    list<int>::iterator it_coef = (*p_coef).begin();
    list<int>::iterator it_degree = (*p_degree).begin(); 
    if(it_degree == (*p_degree).end()){
        cout<<"0 0";
    }
    while(it_degree!=(*p_degree).end()){
        if(it_degree!=(*p_degree).begin())
            cout<<" "; //空格控制
        cout << *it_coef << " "<< *it_degree;
        it_coef++; 
        it_degree++;
    }
}
int main(){
    //read input
    int n1=0,n2=0;
    cin>>n1;
    list<int> poly1coef;
    list<int> poly1degree;
    int t1 = 0,t2 = 0;
    for(int i=0;i<n1;i++){
        cin>>t1>>t2;
        poly1coef.push_back(t1);
        poly1degree.push_back(t2);
    }
    cin>>n2;
    list<int> poly2coef;
    list<int> poly2degree;
    for(int i=0;i<n2;i++){
        cin>>t1>>t2;
        poly2coef.push_back(t1);
        poly2degree.push_back(t2);
    }
    //multi
    list<int>* p_rescoef_mul = nullptr;
    list<int>* p_resdegree_mul = nullptr;
    multi(&poly1coef,&poly2coef,&poly1degree,&poly2degree,&p_rescoef_mul,&p_resdegree_mul);

    //add
    list<int>* p_rescoef = nullptr;
    list<int>* p_resdegree = nullptr;
    
    add(&poly1coef,&poly2coef,&poly1degree,&poly2degree,&p_rescoef,&p_resdegree);

    output(p_rescoef_mul,p_resdegree_mul);
    cout<<endl;
    output(p_rescoef,p_resdegree);

    
    return 0;
}
