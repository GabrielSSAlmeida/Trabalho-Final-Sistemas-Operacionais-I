#ifndef PALAVRA_H

	#define PALAVRA_H

    // ANSI escape codes for text color
    #define RESET   "\033[0m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"

    #include <iostream>
    #include <map>
    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <algorithm>

    extern int numTentativas;

    typedef std::map<char, std::vector<int> > tabela;
	
    void IniciarJogo(std::string obj);
    	
#endif