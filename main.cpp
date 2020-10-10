#include <iostream>
#include <fstream>

#include "gost.h"
#include "sbox.h"

/*class Magma
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

	Magma(char* plaintextFilename, char* outFilename, char* keyFilename){

		plaintextFile.open(plaintextFilename,std::ifstream::binary);
		outFile.open(outFilename,std::ios::out | std::ios::binary);
		keyFile.open(keyFilename,std::ifstream::binary);
		if(!plaintextFile || !outFile || !keyFile)
			std::cout << "File error";
	}
	~Magma(){

		plaintextFile.close();
		outFile.close();
		keyFile.close();
	}
	void readKey(){

		keyFile.read((char*)key.k,32);
	}
	int msgLen(){

	    plaintextFile.seekg (0, plaintextFile.end);
	    msg_len = plaintextFile.tellg();
	    plaintextFile.seekg (0, plaintextFile.beg);
		num_of_block = msg_len / 8;
		return msg_len;
	}

	void rounds(){
		while(num_of_block > 0)
		{
			plaintextFile.read((char*)block.b,8);

			if(k == num_of_block){
				pad_tmp = block.B_pad | padding[(msg_len) % 8 - 1];
				block.B_pad = pad_tmp;
				pad_tmp = 0;
			}

			for (int j = 0; j <= 31; j++)
			{
				if (j < 8){
					s_zero = 0x0;
					right_key = block.B[1] + key.K[j % 8];
				}
				else{
					s_zero = 0x0;
					right_key = block.B[1] + key.K[7 - (j % 8)];
				}
				for (int i = 7; i >= 0; i--){	
					index = (block.B[1] >> 4*i) & 0xF;
					s_tmp = sbox[i][index];
					s_zero = s_zero ^ s_tmp;
					if (i)
					s_zero = s_zero << 4;
				}
				
				s_zero = (s_zero << 11) | (s_zero >> 21);
				
				s_zero = s_zero ^ block.B[0];
				block.B[0] = block.B[1]; //s_zero = res of the round
				block.B[1] = s_zero;
			}

			num_of_block--;
			printf("%d\n",num_of_block );

			tmp_after = block.B[1];
			block.B[1] = block.B[0]; //s_zero = res of the round
			block.B[0] = tmp_after;
			outFile.write((char*)block.b,8);
		}

	}

	int outMsgLen(){
:
	    outFile.seekp (0, outFile.end);
    	int out_len = outFile.tellp();
    	outFile.seekp (0, outFile.beg);

		return out_len;
	}
};*/

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