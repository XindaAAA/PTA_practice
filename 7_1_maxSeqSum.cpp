//最大子列和问题

#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int* data = new int[n];
    for(int i=0;i<n;i++){
        cin>>data[i];
    }
    int maxsum = 0,sum = 0;
    for(int i=0;i<n;i++){
        if(sum+data[i]<0){
            sum = 0;
            continue;
        }
        sum += data[i];
        if(sum > maxsum){
            maxsum = sum;
        }
    }
    cout<<maxsum<<endl;
    return 0;
}