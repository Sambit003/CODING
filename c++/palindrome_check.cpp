// WAP IN C++ TO CHECK WHETHER A NUMBER / STRING IS PALINDROME OR NOT

#include<iostream>
using namespace std;

int main(){
    char choice;
    while(1) {
        cout<<"\n\t1. Number\n\t2. String\n\t3. Exit\n\tEnter your choice: ";
        cin>>choice;

        switch(choice){
            case '1':{
                int n;
                cout<<"\n\tEnter a number: ";
                cin>>n;
                int temp=n, rev=0;
                while(temp>0){
                    rev = rev*10 + temp%10;
                    temp /= 10;
                }
                if(rev==n){
                    cout<<"\n\t"<<n<<" is a palindrome number";
                }
                else{
                    cout<<"\n\t"<<n<<" is not a palindrome number";
                }
                break;
            }
            case '2':{
                string s;
                cout<<"\n\tEnter a string: ";
                cin>>s;
                int i, len=s.length();
                for(i=0; i<len/2; i++){
                    if(s[i]!=s[len-i-1]){
                        cout<<"\n\t"<<s<<" is not a palindrome string";
                        break;
                    }
                }
                if(i==len/2){
                    cout<<"\n\t"<<s<<" is a palindrome string";
                }
                break;
            }
            case '3':{
                exit(1);
            }
            default:{
                cout<<"\n\tInvalid choice";
            }
        }
    }
    return 0;
}