%{
    #include <iostream>
    #include <stdio.h>
    #include <string>
    #include <fstream>
    #include <vector>
    #include <unordered_map>
    #include <algorithm>

    using namespace std;

    unordered_map<string, string> token_type;
%}

%%

[^ ][1-9][0-9]+[ \n]                            {token_type.insert(make_pair<string, string>(yytext, "integer"));}       //integers
[+-]?[1-9][0-9]*(\.)[ \n]                       {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers
[+-]?[1-9][0-9]*(\.)[0-9]*[ \n]                 {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers
[+-]?[1-9][0-9]*(\.)[0-9]*[Ee][+-]?[0-9]+[ \n]  {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers
[+-]?[0-9](\.)[ \n]                             {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers
[+-]?[0-9]?(\.)[0-9]*[ \n]                      {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers 
[+-]?[0-9]?(\.)[0-9]*[Ee][+-]?[0-9]+[ \n]       {token_type.insert(make_pair<string, string>(yytext, "real_number"));}   //real numbers
[=+*/^-][ \n]                                   {token_type.insert(make_pair<string, string>(yytext, "operator"));}      //operators
(\/){2}.*[\n]                                   {token_type.insert(make_pair<string, string>(yytext, "comment"));}       //comments
[^ ][a-zA-Z][0-9a-zA-Z_]*[ \n]                  {token_type.insert(make_pair<string, string>(yytext, "identifier"));}      //variables
.                                  ;

%%

int yywrap(){
    return 1;
}

int main(int argc, char* argv[]){
    yyin = fopen(argv[1], "r"); //file to read
    yylex();

    //Writting html

    string file_name = "output.html"; //name of html file
    ofstream file;
    file.open(file_name);

    file << "<!DOCTYPE HTML>\n";
    file << "<html>\n";
    file << "\t<head>\n";
    file << "\t\t<link rel='stylesheet' href='style.css'>\n";
    file << "\t</head>\n";
    file << "\t<body>\n";

    unordered_map<string, string>::iterator it = token_type.begin();

    while(it != token_type.end()){
        file << "\t\t<p class=\"" << it->second << "\"> " << it->first << " </p>\n";
        it++;
    }

    file.close();

    return 0;
}
