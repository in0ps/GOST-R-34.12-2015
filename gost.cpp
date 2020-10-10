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
	int Magma::msgLen(){

	    plaintextFile.seekg (0, plaintextFile.end);
	    msg_len = plaintextFile.tellg();
	    plaintextFile.seekg (0, plaintextFile.beg);
		num_of_block = msg_len / 8;
		return msg_len;
	}

	void Magma::rounds(){
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

	int Magma::outMsgLen(){
	    outFile.seekp (0, outFile.end);
    	int out_len = outFile.tellp();
    	outFile.seekp (0, outFile.beg);

		return out_len;
	}
