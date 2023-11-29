#ifndef PALAVRA_H

	#define PALAVRA_H

    #define ESC "\033["
    #define VERDE "42"
    #define AMARELO "43"
    #define RESET "\033[m"

    #include <iostream>
    #include <map>

    typedef std::map<char,std::vector<int> > tabela;
	
    void IniciarJogo(std::string obj);
    	
#endif