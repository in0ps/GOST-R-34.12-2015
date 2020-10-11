#include <iostream>
#include <fstream>

#include "gost.h"
#include "sbox.h"

Magma::Magma(char* plaintextFilename, char* outFilename, char* keyFilename){

	plaintextFile.open(plaintextFilename,std::ifstream::binary);
	outFile.open(outFilename,std::ios::out | std::ios::binary);
	keyFile.open(keyFilename,std::ifstream::binary);
	if(!plaintextFile || !outFile || !keyFile)
		std::cout << "File error";
}
Magma::~Magma(){

	plaintextFile.close();
	outFile.close();
	keyFile.close();
}
void Magma::readKey(){

	keyFile.read((char*)key.k,32);
}
int Magma::messageLen(){

    plaintextFile.seekg (0, plaintextFile.end);
    msgLen = plaintextFile.tellg();
    plaintextFile.seekg (0, plaintextFile.beg);
	numOfBlock = msgLen / 8;
	return msgLen;
}

void Magma::ECB(){
	while(numOfBlock > 0){
		if(numOfBlock == 0){
			padTmp = block.B_pad | padding[(msgLen) % 8 - 1];
			block.B_pad = padTmp;
			padTmp = 0;
		}
		Magma::rounds(0);
		numOfBlock--;
		outFile.write((char*)block.b,8);
	}
}

void Magma::CTR(){
	vectorFile.open("vector",std::ifstream::binary);
	if(!vectorFile)
		std::cout << "File error";
	Magma::rounds(1);
	blockVector.B_pad = block.B_pad;
	while(numOfBlock > 0){
		if(numOfBlock == 0){
			padTmp = block.B_pad | padding[(msgLen) % 8 - 1];
			block.B_pad = padTmp;
			padTmp = 0;
		}
		blockVector.b[0] += C1;
		blockVector.b[1] += C2;
		plaintextFile.read((char*)blockText.b,8);
		block.B_pad = blockText.B_pad ^ blockVector.B_pad;
		numOfBlock--;
		outFile.write((char*)block.b,8);
	}
	vectorFile.close();
}

void Magma::rounds(int mode){
	if (mode == 0)
		plaintextFile.read((char*)block.b,8);
	if (mode == 1)
		vectorFile.read((char*)block.b,8);
	
	for (int j = 0; j <= 31; j++)
	{
		if (j < 8){
			sZero = 0x0;
			rightKey = block.B[1] + key.K[j % 8];
		}
		else{
			sZero = 0x0;
			rightKey = block.B[1] + key.K[7 - (j % 8)];
		}
		for (int i = 7; i >= 0; i--){	
			index = (block.B[1] >> 4*i) & 0xF;
			sTmp = sbox[i][index];
			sZero = sZero ^ sTmp;
			if (i)
			sZero = sZero << 4;
		}
		
		sZero = (sZero << 11) | (sZero >> 21);
		
		sZero = sZero ^ block.B[0];
		block.B[0] = block.B[1]; //sZero = res of the round
		block.B[1] = sZero;
	}

	tmpAfter = block.B[1];
	block.B[1] = block.B[0]; //sZero = res of the round
	block.B[0] = tmpAfter;
}

int Magma::outMsgLen(){
    outFile.seekp (0, outFile.end);
	int outLen = outFile.tellp();
	outFile.seekp (0, outFile.beg);

	return outLen;
}

