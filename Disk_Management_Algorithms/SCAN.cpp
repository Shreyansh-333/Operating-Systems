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
    int totalSeekTime=0, current=initialHeadPosition;
    cout << "The average rotational delay is " << (30000)/RPM << "ms"<<endl;
    sort(requestTrack.begin(),requestTrack.end());
    totalSeekTime=numberOfTracks-initialHeadPosition;
    if(requestTrack[0]<initialHeadPosition){
        totalSeekTime+=numberOfTracks-requestTrack[0];
    }
    cout<<"The total seek time is: "<<totalSeekTime*averageSeekTime<<"ms"<<endl;
}