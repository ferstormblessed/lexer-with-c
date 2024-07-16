%{
    // C++ PYHTON SWIFT

    #include <iostream>
    #include <stdio.h>
    #include <string>
    #include <fstream>
    #include <vector>

    using namespace std;

    vector<pair<string, string> > token_type;

%}

%%

[0-9]*                                     {token_type.push_back(make_pair<string, string>(yytext, "integer"));}       //integer
[+-]?[1-9][0-9]*(\.)                       {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number
[+-]?[1-9][0-9]*(\.)[0-9]*                 {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number
[+-]?[1-9][0-9]*(\.)[0-9]*[Ee][+-]?[0-9]+  {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number
[+-]?[0-9]?(\.)[0-9]+                      {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number
[+-]?[0-9](\.)[0-9]*                       {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number 
[+-]?[0-9](\.)[0-9]*[Ee][+-]?[0-9]+        {token_type.push_back(make_pair<string, string>(yytext, "real_number"));}   //real number
[=+*/^<>!-]|(<<)|(>>)                       {token_type.push_back(make_pair<string, string>(yytext, "operator"));}      //operator
(\").+(\")                                 {token_type.push_back(make_pair<string, string>(yytext, "string"));}        //string
(\/){2}.*(\n)                              {token_type.push_back(make_pair<string, string>(yytext, "comment"));}       //comment c++
(#)\^(include).*(\n)                       {token_type.push_back(make_pair<string, string>(yytext, "comment"));}       //comment py/ruby
[\(\)]                                     {token_type.push_back(make_pair<string, string>(yytext, "parenthesis"));}   //parenthesis
[\[\]]                                     {token_type.push_back(make_pair<string, string>(yytext, "bracket"));}       //bracket
[\{\}]                                     {token_type.push_back(make_pair<string, string>(yytext, "curly_brace"));}   //curly_brace
[a-zA-Z][0-9a-zA-Z_]*                      {token_type.push_back(make_pair<string, string>(yytext, "identifier"));}    //identifier
(;)                                        {token_type.push_back(make_pair<string, string>(yytext, "semicolon"));}     //semicolon
(:)                                        {token_type.push_back(make_pair<string, string>(yytext, "colon"));}         //colon
(,)                                        {token_type.push_back(make_pair<string, string>(yytext, "coma"));}          //coma
#include|import                            {token_type.push_back(make_pair<string, string>(yytext, "library"));}       //library

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
    file << "\t\t<p> SHOWING ONLY VALID TOKENS </p>";
    file << "\t\t<p></p>";

    for(int i = 0; i < token_type.size(); i++){
        file << "\t\t<p class='" << token_type[i].second << "'> " << token_type[i].first << "   ----------->   " << token_type[i].second << " </p>\n";
    }

    file.close();

    return 0;
}
