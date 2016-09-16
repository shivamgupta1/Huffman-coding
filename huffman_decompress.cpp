/*
*NO Error checking or handling whatsoever in this code
*use at your own risk
*@author shivam gupta
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>

#define MAX_CODE_LENGTH 20   //max huffman code length i.e. length of 01011101 is 8
using namespace std;

struct trieNode {
	trieNode *child0, *child1;
	bool isValid;             //isValid to store if the current node is a valid word for eg. 10010 if its in the dictionary
	unsigned char value;      //value stores the corresponding byte value

	trieNode(bool v = false, unsigned char val = 0, trieNode* c0 = NULL, trieNode *c1 = NULL) : isValid(v), value(val), child0(c0), child1(c1) {}
};

void insertIntoTrie(trieNode *root, char *code, unsigned char byte) {
	if(strlen(code) == 0) return;
	int i = 0;
	while(code[i]) {
        if(code[i] == '0')  {
            if(!root->child0)
                root->child0 = new trieNode();
            root = root->child0;
        }
        else {
            if(code[i] != '1') {
                cout << "error present in codes";
                exit(1);
            }
            if(!root->child1)
                root->child1 = new trieNode();
            root = root->child1;
        }
        i++;
	}
	root->isValid = true;
	root->value = byte;
	cout << "inserted: " <<code << " " << (int) byte << endl;
}

class BitReader {
    FILE *fp;
    unsigned char byte;     //a byte is read into this variable
    int bit_count;          //no. of bits currently in variable byte
    long long int bitStreamLength;
public:
    BitReader(FILE *f, long long int bsl) : fp(f),byte(0),bit_count(0),bitStreamLength(bsl) {}

    unsigned char read() {   //returns '0' or '1'
        if(bit_count==0) {
            fread(&byte, 1, 1, fp);
            if(bitStreamLength >= 8) {
                bit_count = 8;
                bitStreamLength -= 8;
            }
            else {
                if(bitStreamLength == 0) cout << "\nerror: read more than available" << endl;
                bit_count = bitStreamLength;
                bitStreamLength = 0;
            }
        }
        bit_count--;
        return '0' + ((byte>>bit_count)&1);           //note that bit_count was decremented earlier
    }
};

int main() {
	FILE *inp = fopen("compressed.myformat", "rb");
	FILE *out = fopen("decompressed.jpg", "wb");

	trieNode *root = new trieNode();       //making the trie

	char code[MAX_CODE_LENGTH]; //used to store the huffman codes temporarily
	unsigned char byte;          //used to store the corresponding byte

	int temp;
	while(fscanf(inp, "%s", code)!= EOF && strcmp(code, "|") != 0) {   //later on, we would assume that EOF never happened here, no error checking!
		fscanf(inp, "%d", &temp);
		byte = (unsigned char)temp;
		insertIntoTrie(root, code, byte);
	}

	long long int bitStreamLength;   //to store bit stream length in file
    fscanf(inp, "%lld", &bitStreamLength);
    char ch;
    fread(&ch, 1,1, inp);   //reading the trailing space

    BitReader br(inp, bitStreamLength);

    long long int cnt;
    trieNode *node;
    for(cnt = 0, node = root; cnt<bitStreamLength; cnt++) {
        unsigned char ch = br.read();
        //cout << ch;
        if(ch == '0') {
            if(!node->child0) {
                cout << "\nprefix error at 0\n";       //code was not stored in trie
                exit(1);
            }
            node = node->child0;
        }
        else {
            if(!node->child1) {
                cout << "\nprefix error at 1\n";
                exit(1);
            }
            if(ch != '1') {
                cout << "\nbit read error\n";
                exit(1);
            }
            node = node->child1;
        }
        if(node->isValid) {
            fwrite(&(node->value), 1, 1, out);
            node = root;
        }
    }
	return 0;
}
