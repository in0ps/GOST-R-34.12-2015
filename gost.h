#include <iostream>
#include <fstream>

#ifndef GOST_H
#define GOST_H

class Magma
{
	union Key{
		unsigned int K[8];
		unsigned char k[32];
	}key;

	unsigned int s_zero = 0x0;
	unsigned int s_tmp,tmp_after,right_key,pad_tmp;
	int j = 0,index = 0,tmp_index = 0,n = 0,k = 0;

public:

	std::ifstream plaintextFile;
	std::ofstream outFile;
	std::ifstream keyFile;

	int msg_len;
	int num_of_block;

	
	union Block{
		long long  B_pad;
		unsigned int B[2]; // 0 left,1 - right
		unsigned char b[8];
	}block;
	// unsigned long int padding[7] = {0x0000000000000001,0x0000000000000202,0x0000000000030303,0x0000000004040404,
	// 	0x0000000505050505,0x0006060606060606,0x0007070707070707};
	unsigned long int padding[7] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0};

	Magma(char* plaintextFilename, char* outFilename, char* keyFilename);
	~Magma();
	void readKey();
	int msgLen();

	void rounds();

	int outMsgLen();
};
#endif