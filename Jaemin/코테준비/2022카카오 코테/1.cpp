#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'solution' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER x
 *  2. INTEGER y
 *  3. INTEGER z
 */

int solution(int x, int y, int z) {
    int dist = abs(x - y);
    if( z < dist){
        return -1;
    }
    
    
    int maximum = max(x, y);
    return maximum + (z - dist)/2;



}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string x_temp;
    getline(cin, x_temp);

    int x = stoi(ltrim(rtrim(x_temp)));

    string y_temp;
    getline(cin, y_temp);

    int y = stoi(ltrim(rtrim(y_temp)));

    string z_temp;
    getline(cin, z_temp);

    int z = stoi(ltrim(rtrim(z_temp)));

    int result = solution(x, y, z);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
