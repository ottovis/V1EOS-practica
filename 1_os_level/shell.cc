#include "shell.hh"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void cd(const std::vector<std::string> & splitCommand){
    chdir(splitCommand[1].c_str());
    return;
}

void find(const std::vector<std::string> & splitCommand){
    if(splitCommand.size() != 2){
        std::cerr << "Find needs exactly one arg to search for" << std::endl;
        return;
    }
    int p[2];
    pid_t pid1, pid2;
    pipe(p);
    pid1 = fork();
    if(pid1 == 0){
        dup2(p[1], 1); //links cout en pipe in
        close(p[0]); //sluit oude file discripters
        close(p[1]);
        execlp("find", "find", ".", NULL);
    }
    pid2 = fork();
    if(pid2 == 0){
        dup2(p[0], 0); //links cin en pipe out
        close(p[0]); //sluit oude file discripters
        close(p[1]);
        execlp("grep", "grep", splitCommand[1].c_str(), NULL);
    }
    close(p[0]);
    close(p[1]); //sluiten van file discripters moet in elk process anders kan je shell hangen

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void execute(std::vector<std::string> &splitCommands){
    char *file;
    file = (char*) malloc(splitCommands[0].size()+1);
    memcpy(file, splitCommands[0].c_str(), splitCommands[0].size());
    *(file + splitCommands[0].size()) = 0;

    char **args;
    args = (char**) malloc(splitCommands.size());
    for(long unsigned int i = 0; i < splitCommands.size(); i++){
        *(args+i) = (char*) malloc(splitCommands[i].size());
        memcpy(*(args+i), splitCommands[i].c_str(), splitCommands[i].size());
    }
    *(args+splitCommands.size()) = (char*) malloc(1);
    *(args+splitCommands.size()) = 0;

    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0){
        execvp(file, args);
        std::cout << "failed to start process" << std::endl;
        free(file);
        free(args);
        exit(-1);
    }
    else{
        waitpid(pid, &status, 0);
    }

    free(file);
    free(args);
}

int main(){
    std::string prompt = "Shell > ";
    while(true){
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            std::cout << "Current dir unavalable ";
        }
        std::cout << cwd << " @ " << prompt;
        std::string command;
        std::string tmpStr;
        std::vector<std::string> splitCommands;
        std::getline(std::cin, command);
        for(long unsigned int i = 0; i < command.size(); i++){
            if(command[i] == ' '){
                splitCommands.push_back(tmpStr);
                tmpStr = "";
            }
            else if(i == command.size()-1){
                splitCommands.push_back(tmpStr + command[i]);
            }
            else{
                tmpStr += command[i];
            }
        }
        if (splitCommands[0] == "new_file") new_file();
        else if (splitCommands[0] == "src") src();
        else if (splitCommands[0] == "find") find(splitCommands);
        else if (splitCommands[0] == "cd") cd(splitCommands);
        else if (splitCommands[0] == "exit") return 0;
        else if (splitCommands[0] == "quit") return 0;
        else if (splitCommands[0] == "error") return 1;
        else if (!splitCommands.size()) return 0;
        else execute(splitCommands);

        if (std::cin.eof()) return 0; } }      // EOF is een exit

    void new_file(){
        std::string filename;
        std::string input;
        std::cout << "Give filename: ";
        std::getline(std::cin, filename);
        std::cout << "Give text for in the file: ";
        std::getline(std::cin, input);
        int fileDisc = open((filename.c_str()), O_CREAT | O_APPEND | O_WRONLY, 0777);
        if(fileDisc < 0){
            std::cout << "failed to open/create file: " << strerror(errno) << std::endl;
            return;
        }
        if(write(fileDisc, input.c_str(), input.size()) < 0){
            std::cout << "faited to write file: " << strerror(errno) << std::endl;
            return;
        }
        if(close(fileDisc) < 0){
            std::cout << "failed to close file: " << strerror(errno) << std::endl;
            return;
        }
    }


    void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
    { int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
      char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
      while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
        std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.



