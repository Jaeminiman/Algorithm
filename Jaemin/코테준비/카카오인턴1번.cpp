#include <string>
#include <vector>

using namespace std;

int output[8];
string types = "RTCFJMAN";
int parse(char type){
    switch (type)
    {
    case 'R':
        return 0;
    case 'T':
        return 1;
    case 'C':
        return 2;
    case 'F':
        return 3;
    case 'J':
        return 4;
    case 'M':
        return 5;
    case 'A':
        return 6;
    case 'N':
        return 7;
    default:
        return -1;
    }
}
string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    
    for(int i = 0; i < survey.size() ; i++){
        if(choices[i] > 4){
            output[parse(survey[i][1])] += choices[i] - 4;
        }
        else{
            output[parse(survey[i][0])] += 4 - choices[i];
        }
    }
    for(int i = 0; i<8; i = i + 2){
        if(output[i] >= output[i+1]){
            answer.push_back(types[i]);
        }
        else {
            answer.push_back(types[i+1]);
        }
    }
    
    
    return answer;
}