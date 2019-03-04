#include <iostream>
#include <unistd.h>  // syscall()
#include <syscall.h> // SysCall nummers
#include <fcntl.h>   // O_RDONLY
#include <vector>
#include <string>

int main();
void new_file();
void list();
void find(const std::vector<std::string> &);
void python();
void src();
void execute(std::vector<std::string> &);
void cd(const std::vector<std::string> &);
