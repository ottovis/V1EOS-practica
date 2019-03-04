/*#include <iostream>
#include <string>

std::string translate(int arg, std::string variabele)
{ for(long unsigned int i = 0; i < variabele.size(); i++){
        variabele[i] *= arg;}
  return variabele; }

int main(int argc, char *argv[])
{ std::string s;
    int arg;

  if(argc != 2)
  { std::cerr << "Deze functie heeft exact 1 argument nodig" << std::endl;
    return -1; }

  try{
      arg = std::stoi(argv[1]);
  }
  catch(...){
      std::cerr << "Deze functie wil een int als argument" << std::endl;
      return -1;
  }

  while(true)
  { std::cin >> s;
    if(std::cin.eof()){ return 0; }
    std::cout << translate(arg, s) << std::endl; } }

*/
