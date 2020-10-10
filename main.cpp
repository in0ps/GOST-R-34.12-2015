#include <iostream>
#include <fstream>

#include "gost.h"
#include "sbox.h"

int main(int argc, char *argv[]){
	if (argc != 4){
	printf("USAGE : ./magma input output key\n");
	exit(0);
	}
	Magma magma(argv[1],argv[2],argv[3]);

	magma.readKey();
	std::cout << magma.msgLen();
	magma.rounds();
	std:: cout << magma.outMsgLen() << "\n";
}
