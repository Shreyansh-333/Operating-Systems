#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file;
    file.open("input.txt");
    int input, num = 0;
    vector<int> requestTrack;
    int numberOfTracks, numberOfSectors, bytesPerSector, RPM, averageSeekTime, initialHeadPosition;
    // 250
    // 10
    // 50
    // 5000
    // 200
    // 50
    // 82 170 43 140 24 16 190
    while(file >> input) {
        if(num == 0) numberOfTracks = input;
        else if(num == 1) numberOfSectors = input;
        else if(num == 2) bytesPerSector = input;
        else if(num == 3) RPM = input;
        else if(num == 4) averageSeekTime = input;
        else if(num == 5) initialHeadPosition = input;
        else {
            do{
                requestTrack.push_back(input);
            }while(file >> input);
        }
        num++;
    }
    int totalSeekTime=0, current=initialHeadPosition, mini=INT_MAX;
    cout << "The average rotational delay is " << (30000)/RPM << "ms"<<endl;
    mini=abs(requestTrack[0]-current);
    while(requestTrack.size()){
        int index=0;
        mini=INT_MAX;
        for(int i=0;i<requestTrack.size();i++){
            mini=min(abs(current-requestTrack[i]),mini);
            if(abs(current-requestTrack[i])==mini){
                index=i;
            }
        }
        totalSeekTime+= abs(requestTrack[index]-current);
        current=requestTrack[index];
        requestTrack.erase(requestTrack.begin()+index);
    }
    
    cout<<"The total seek time is: "<<totalSeekTime*averageSeekTime<<"ms"<<endl;
}