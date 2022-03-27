%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <vector>

    std::vector<std::string> integers;
    std::vector<std::string> real_numbers;
    std::vector<std::string> comments;
    std::vector<std::string> operators;
    std::vector<std::string> variables;
    
%}

%%

[1-9][0-9]+[ \n]                                    {integers.push_back(yytext);}       //integers
[+-]?[1-9][0-9]*(\.)[ \n]                           {real_numbers.push_back(yytext);}   //real numbers
[+-]?[1-9][0-9]*(\.)[0-9]*[ \n]                     {real_numbers.push_back(yytext);}   //real numbers
[+-]?[1-9][0-9]*(\.)[0-9]*[Ee][+-]?[0-9]+[ \n]      {real_numbers.push_back(yytext);}   //real numbers
[+-]?[0-9](\.)[ \n]                                 {real_numbers.push_back(yytext);}   //real numbers
[+-]?[0-9]?(\.)[0-9]*[ \n]                          {real_numbers.push_back(yytext);}   //real numbers 
[+-]?[0-9]?(\.)[0-9]*[Ee][+-]?[0-9]+[ \n]           {real_numbers.push_back(yytext);}   //real numbers  
[=+*/^-][ \n]                                       {operators.push_back(yytext);}      //operators
(\/){2}.*[\n]                                       {comments.push_back(yytext);}       //comments
[a-zA-Z][0-9a-zA-Z_]*[ \n]                          {variables.push_back(yytext);}      //variables
.                                  ;

%%

int main(int argc, char* argv[]){

    yyin = fopen(argv[1], "r"); //file to read input

    yylex();

    for(int i = 0; i < integers.size(); i++){
        std::cout << "integer: " << integers[i] << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < real_numbers.size(); i++){
        std::cout << "real number: " << real_numbers[i] << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < variables.size(); i++){
        std::cout << "variable: " << variables[i] << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < operators.size(); i++){
        std::cout << "operator: " << operators[i] << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < comments.size(); i++){
        std::cout << "comment: " << comments[i] << std::endl;
    }

    return 0;
}