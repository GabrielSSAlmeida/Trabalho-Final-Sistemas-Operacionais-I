#ifndef GLOBALS_H
    #define GLOBALS_H

    #include <mutex>
    #include <map>
    #include <vector>
    #include <thread>

    // ANSI escape codes for text color
    #define RESET   "\033[0m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"

    typedef std::map<char, std::vector<int>> tabelaLetras;


    void console_pegaTela();

    void console_largaTela();

    extern int contadorInicial;
    extern int contador;
    extern bool gameOver;
    extern int numTentativasRestantes;
    extern int acertos;
    extern bool leituraPronta;
    extern std::vector<std::string> palavrasAcertadas;
    extern std::string buffer;

    // mutex relacionados à controle de variáveis compartilhadas
    extern std::mutex mutexBuffer;
    extern std::mutex mutexTentativas;
    extern std::mutex mutexAcertos;
    extern std::mutex gameOverMutex;
    extern std::mutex mutexArquivo;
    extern std::mutex letrasMutex;
    extern std::mutex mutexContador;

    //mutex relacionados à controle de regiões compartilhadas
    extern std::mutex proxRodadaMutex;
    extern std::mutex tela;

    extern tabelaLetras letras;

#endif