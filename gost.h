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

	unsigned int sZero = 0x0;
	unsigned int sTmp,tmpAfter,rightKey,padTmp;
	int j = 0,index = 0;

public:

	std::ifstream plaintextFile;
	std::ofstream outFile;
	std::ifstream keyFile;
	std::ifstream vectorFile;

	int msgLen;
	int numOfBlock;
	
	union Block{
		long long  B_pad;
		unsigned int B[2]; // 0 left,1 - right
		unsigned char b[8];
	}block;

	union BlockVector{
		long long  B_pad;
		unsigned int B[2]; // 0 left,1 - right
		unsigned char b[8];
	}blockVector;

	union BlockText{
		long long  B_pad;
		unsigned int B[2]; // 0 left,1 - right
		unsigned char b[8];
	}blockText;

	unsigned long int padding[7] = {0x0000000000000001,0x0000000000000202,0x0000000000030303,0x0000000004040404,
	0x0000000505050505,0x0006060606060606,0x0007070707070707};
	int C2 = 0x1010101;
	int C1 = 0x1010104;
	
	Magma(char* plaintextFilename, char* outFilename, char* keyFilename);
	~Magma();

	void readKey();

	void ECB();
	void CTR();

	void rounds(int mode);
	
	int messageLen();
	int outMsgLen();
};
#endif
