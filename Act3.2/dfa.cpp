#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

const char zero = '0'; //zero character                                                 value = 0
const string nums1 = "1234567"; // numbers 1 to 7                                       value = 1
const string nums2 = "89"; // numbers 8 and 9                                           value = 2
const string u_letters1 = "ABCDF"; //uppercase letters A to F minus E                   value = 3
const string u_letters2 = "GHIJKLMNOPQRSTUVWXYZ"; //uppercase letters G to Z            value = 4
const string l_letters1 = "abcdf"; //lowercase letters a to f minus e                   value = 5
const string l_letters2 = "ghijklmnopqrstuvwyz"; //lowercase letters g to z minus x     value = 6
const string e = "Ee"; //upper and lowercase letter e                                   value = 7
const char x = 'x'; //lowercase letter x                                                value = 8
const char underscore = '_'; //underscore character                                     value = 9
const string parenthesis = "()"; //parenthesis character                                value = 10,11
const char point = '.'; //point character                                               value = 12
const string operators = "=+-*/^"; //operators characters                               value = 13,14,15,16,17,18
const char space = ' '; //space character                                               value = 19
const char end_l = '\n'; //\n or end of line character == endl                          value = 20

unordered_map<char, int> sigma; //alphabet or sigma of dfa
unordered_map<int, bool> final_states; //set of final states of dfa
unordered_map<int, string> token; //final state -> token

int delta[25][21] = { // transition table
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
    { 2,  1,  1, 16, 16, 16, 16, 16, 16, 24, 21, 22,  3, 17,  4,  5, 18, 19, 20,  0,  0}, //q0
    { 1,  1,  1, 24, 24, 24, 24, 24, 24, 24, 24, 24,  6, 24, 24, 24, 24, 24, 24,  0,  0}, //q1
    {24, 13, 24, 24, 24, 24, 24, 24, 14, 24, 24, 24,  6, 24, 24, 24, 24, 24, 24,  0,  0}, //q2
    { 7,  7,  7, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q3
    { 8,  9,  9, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q4
    { 8,  9,  9, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q5
    { 7,  7,  7, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q6
    { 7,  7,  7, 24, 24, 24, 24, 10, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q7
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  3, 24, 24, 24, 24, 24, 24,  0,  0}, //q8
    { 9,  9,  9, 24, 24, 24, 24, 24, 24, 24, 24, 24,  6, 24, 24, 24, 24, 24, 24,  0,  0}, //q9
    {24, 12, 12, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 11, 11, 24, 24, 24,  0,  0}, //q10
    {24, 12, 12, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q11
    {12, 12, 12, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q12
    {24, 13, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q13
    {15, 15, 15, 15, 24, 15, 24, 15, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q14
    {15, 15, 15, 15, 24, 15, 24, 15, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q15
    {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q16
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q17
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q18
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24,  0,  0}, //q19
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q20
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q21
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}, //q22
    {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,  0}, //q23
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0}  //q24
};

int num_f = 16;
//set of final states
int f[] = {1, 4, 5, 6, 7, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23};
//name of token
string token_name[] = {"INTEGER", //1
                       "SUM", //4
                       "SUBSTRACTION", //5
                       "REAL NUMBER", //6
                       "REAL NUMBER", //7
                       "REAL NUMBER", //12
                       "OCTAL NUMBER", //13
                       "HEXADECIMAL NUMBER", //15
                       "VARIABLE", //16
                       "ASSIGNMENT", //17
                       "MULTIPLICATION", //18
                       "DIVISION", //19
                       "POWER", //20
                       "LEFT PARENTHESIS", //21
                       "RIGHT PARENTHESIS", //22
                       "COMMENT" //23
                       };

//values for the sigma map
int zero_v = 0,
    nums1_v = 1,
    nums2_v = 2,
    u_letters1_v = 3,
    u_letters2_v = 4,
    l_letters1_v = 5,
    l_letters2_v = 6,
    e_v = 7,
    x_v = 8,
    undescore_v = 9,
    parenthesis_v = 10,
    point_v = 12,
    operator_v = 13,
    space_v = 19,
    endl_v = 20;

//function to fill the hash maps sigma, final states and token
void fillMaps(){ 
    //filling sigma
    //0
    sigma[zero] = 0;
    //[1,7]
    for(int i = 0; i < nums1.size(); i++){
        sigma[nums1[i]] = nums1_v;
    }
    //[9,8]
    for(int i = 0; i < nums2.size(); i++){
        sigma[nums2[i]] = nums2_v;
    }
    //[A,Z]-E
    for(int i = 0; i < u_letters1.size(); i++){
        sigma[u_letters1[i]] = u_letters1_v;
    }
    //[G,Z]
    for(int i = 0; i < u_letters2.size(); i++){
        sigma[u_letters2[i]] = u_letters2_v;
    }
    //[a,f]-e
    for(int i = 0; i < l_letters1.size(); i++){
        sigma[l_letters1[i]] = l_letters1_v;
    }
    //[g,z]-x
    for(int i = 0; i < l_letters2.size(); i++){
        sigma[l_letters2[i]] = l_letters2_v;
    }
    //Ee
    for(int i = 0; i < e.size(); i++){
        sigma[e[i]] = e_v;
    }
    //x
    sigma[x] = x_v;
    //underscore
    sigma[underscore] = 9;
    //parenthesis ()
    for(int i = 0; i < parenthesis.size(); i++){
        sigma[parenthesis[i]] = parenthesis_v + i;
    }
    //point .
    sigma[point] = point_v;
    //operators =+-*/^
    for(int i = 0; i < operators.size(); i++){
        sigma[operators[i]] = operator_v + i;
    }
    //space
    sigma[space] = space_v;
    //end line \n
    sigma[end_l] = endl_v;

    //filling final_states
    for(int i = 0; i < num_f; i++){
        final_states[f[i]] = true;
    }

    //filling token
    for(int i = 0; i < num_f; i++){
        token[f[i]] = token_name[i];
    }
}

//function to traverse the transition table and determine the token type and validity
void dfa(string s){
    int state = 0,
        last_space_pos = -1, //last space position or new line
        token_len = 0, //length of the current token
        comment_state = 23, //number of the comment token/state
        trap_state = 24; //number of the trap state

    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        state = delta[state][sigma[c]]; //current state

        if(state == 0){
            last_space_pos = i; //update last space position
            token_len = 0; //reseting the token length
        }
        else{
            token_len++; //update token length
        }

        //check if the state is a final state AND (the next character in the string is a space OR \n)
        if(final_states[state] && state != comment_state && (s[i + 1] == space || s[i + 1] == end_l)){
            //print a substring, the token, of s from the last space position + 1 
            cout << s.substr(last_space_pos + 1, token_len) << " -> " << token[state] << endl << endl;
        }
        //check if the token is a comment
        else if(state == comment_state && s[i + 1] == end_l){
            cout << s.substr(last_space_pos + 1, token_len) << " -> " << token[state] << endl << endl;
        }
        //check if the token is invalid
        else if(state == trap_state && (s[i + 1] == space || s[i + 1] == end_l)){
            cout << "--------- ERROR ---------" << endl;
            cout << s.substr(last_space_pos + 1, token_len) << " -> NOT A VALID TOKEN" << endl;
            cout << "-------------------------" << endl << endl;
        }
    }
}

void lexerAritmetico(string archivo){
    fillMaps(); //fill hash maps

    string s; //string for the dfa function
    char c; //individual character of the file

    ifstream ifs;
    ifs.open(archivo);
    while(ifs.get(c)){
        s += c;
    }
    ifs.close();

    cout << endl << "| TOKEN || TIPO |" << endl << endl;
    dfa(s);
    cout << endl;
}

int main(){
    string archivo = "test.txt"; //nombre del archivo a leer
    lexerAritmetico(archivo);
    
    return 0;
}