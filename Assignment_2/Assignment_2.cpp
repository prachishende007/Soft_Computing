#include<bits/stdc++.h>
#include<vector>
using namespace std;

class Slow{
    public:
        double getMembership(double speed){
            if(speed <= 20 ){
                return 1;
            }
            else if(speed > 20 && speed <= 40){
                return(40-speed)/20;
            }
            else{
                return 0;
            }
        }
};

class Fast{
    public:
        double getMembership(double speed){
            if(speed <= 20 ){
                return 0;
            }
            else if(speed > 40 && speed <= 60){
                return(60-speed)/20;
            }
            else{
                return 1;
            }
        }
};

int main(){
    double speed;
    Fast fuzzy;
    Slow fuzz;
    vector<double> Union;


    cout<<"Enter the speed"<<endl;
    cin>>speed;
    

    double membership1 = fuzzy.getMembership(speed);
    cout<<"The value for fast function is "<< membership1 <<endl;

    
    double membership2 = fuzz.getMembership(speed);
    cout<<"The value for slow function is "<< membership2 <<endl;

    Union.push_back(max(membership1, membership2));

    for (double it : Union){

        if(membership1 > membership2 ){
             cout<<"the value is "<<it<<" Fast"<<endl;
        }
        else{
              cout<<"the value is "<<it<<" Slow"<<endl;
        }
    }

    
    return 0;

}
