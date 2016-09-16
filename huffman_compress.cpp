/*
*NO Error checking or handling whatsoever in this code
*use at your own risk
*@author shivam gupta
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

#define OUT_OF_RANGE 256         //256 is out of range of a byte and is used in place of null

using namespace std;

struct treeNode {
    int ch;
    long long int freq;
    treeNode *left, *right;
    treeNode(int c, long long int f, treeNode *l, treeNode *r) : ch(c),freq(f),left(l),right(r) {}
    treeNode(const treeNode &t) : ch(t.ch), freq(t.freq),left(t.left),right(t.right) {}
    bool operator< (const treeNode &rhs) const {
        return this->freq > rhs.freq;
	}
};

void codegenerator(treeNode *root, string &s, vector<string> &code) {
    if(!root) {
        return;
    }
    if(root->ch != OUT_OF_RANGE) { // ch not null
        code[root->ch] = s;
        cout << root->ch << " " << s<< endl;
    }
    s.push_back('0');
    codegenerator(root->left, s, code);
    s.erase(s.end()-1);
    s.push_back('1');
    codegenerator(root->right, s, code);
    s.erase(s.end()-1);
}

class BitWriter {
	int bit_counter;        //how many bits in current byte
	unsigned char curr_byte;  //curr_byte to write later
	FILE *fp;
public:
	BitWriter(FILE *f) : bit_counter(0), curr_byte(0), fp(f) {}
	void write(unsigned char bit) {
		curr_byte <<= 1;
		curr_byte |= bit;
		if(++bit_counter == 8) {
			fwrite(&curr_byte, 1, 1, fp);
			bit_counter = 0;
			curr_byte = 0;
		}
	}
	void flush() {       //used to flush last byte
        if(bit_counter>0) {
            fwrite(&curr_byte, 1,1 ,fp);
        }
	}
};

int main() {
	FILE *inp = fopen("binary_file.jpg", "rb");
	FILE *out = fopen("compressed.myformat", "wb");

    vector<long long int> freq_store(256, 0);
    vector<string> code(256);
    vector<int> store;

	unsigned char buffer[1];
	while(fread(buffer, 1, 1, inp)>0) {  //arguments : character address to read to, size(in bytes) of each element to read, number of such elements to read, file desc
        if(freq_store[(int)buffer[0]] == 0 ) { //storing all the bytes present to push into queue later
            store.push_back((int)buffer[0]);
        }
		freq_store[(int)buffer[0]]++;
	}
	rewind(inp);

	for(int i = 0; i<store.size(); i++) {
        cout << store[i] << " " << freq_store[store[i]] << endl;
	}

    priority_queue<treeNode> pq;
    for(int i = 0; i<store.size(); i++) {  //pushing all the stored bytes into the priority queue
        pq.push(treeNode(store[i], freq_store[(int)store[i]], NULL, NULL));
    }

    treeNode *root;

    while(pq.size() > 1) { //need to extract 2 elements
        treeNode t1 = pq.top();
        pq.pop();
        treeNode t2 = pq.top();
        pq.pop();

        treeNode *l = new treeNode(t1);
        treeNode *r = new treeNode(t2);

        root = new treeNode(OUT_OF_RANGE, l->freq+r->freq, l, r);

        pq.push(*root);
    }

    string s = "";
    codegenerator(root, s, code);

    for(int i = 0; i<store.size(); i++) {  //all this is stored as text, so each character takes 1 byte, which is too much space(5-6 KB max)
        fprintf(out, "%s %d ", code[store[i]].c_str(), store[i]);
	}
	fprintf(out, "| ");

	long long int bitStreamLength = 0;  // after | store the bit stream length in the file itself
	while(fread(buffer, 1, 1, inp)>0) {
		bitStreamLength += code[(int)buffer[0]].length();
	}
	rewind(inp);

	fprintf(out, " %lld ", bitStreamLength); //actually printing the size of the bit stream to the file, binary data starts immediately after |

	BitWriter bw(out);

	while(fread(buffer, 1, 1, inp) > 0) {
		string cd = code[(int)buffer[0]];
		for(int i = 0; i<cd.length(); i++) {
			bw.write(cd[i]-'0');        //gives 0 or 1 integer value to write function instead of chars '0' or '1'
		}
	}
	rewind(inp);

    bw.flush(); //write any remaining bits in buffer

    return 0;
}
