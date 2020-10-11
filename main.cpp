#include <iostream>
#include <fstream>
#include <cstring>

#include "gost.h"
#include "sbox.h"


int main(int argc, char *argv[]){
	if (argc != 5){
	printf("USAGE : ./magma {INPUT} {OUTPUT} {KEY} {MODE}\n");
	exit(0);
	}

	Magma magma(argv[1],argv[2],argv[3]);

	magma.readKey();
	std::cout << magma.messageLen() << "\n";
	if (!strcmp(argv[4],"0"))
		magma.ECB();
	if (!strcmp(argv[4],"1"))
		magma.CTR();
	
	std:: cout << magma.outMsgLen() << "\n";
}