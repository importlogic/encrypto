#include <bits/stdc++.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

map<int, pair<int, int>> places = {	{0, {2,1}},
							    	{1, {2,0}},
									{2, {1,2}},
									{3, {1,1}},
									{4, {1,0}},
									{5, {0,2}},
									{6, {0,1}},
									{7, {0,0}}
								   	};


void encode(CImg<unsigned char> &src, string message, int w){
	int r,c;
	r = c = 0;
	for(int i = 0; i < message.length(); i++){
		int value = (int)message[i];

		for(int shift = 0; shift < 8; shift++){
			int x,y;
			tie(x,y) = places[shift];

			bool oddvalue = (value >> shift) & 1;
			bool oddbit = (int)src(c + x, r, y) & 1;

			int temp = (int)src(c + x, r, y);

			if(oddvalue ^ oddbit){
				if(oddvalue) src(c + x, r, y) = temp + 1;
				else src(c + x, r, y) = temp - 1;
			}
		}

		bool oddbit = (int)src(c + 2, r, 2) & 1;
		int temp = (int)src(c + 2, r, 2);

		if(i == message.length() - 1) {
			if(!oddbit) src(c + 2, r, 2) = temp + 1;
		}
		else {
			if(oddbit) src(c + 2, r, 2) = temp - 1;		
		}

		c += 3;
		if(c >= w){
			c = 0;
			++r;
		}
	}
}

string decode(CImg<unsigned char> &src, int w, int h){
	string toreturn = "";

	for(int r = 0; r < h; r++){
		for(int c = 0; c < w; c += 3){
			int value = 0;
			for(int i = 7; i > -1; i--){
				int x,y;
				tie(x, y) = places[i];

				if(src(c + x, r, y) & 1){
					value += (1 << i);
				}
			}

			toreturn += (char)value;
			if((int)src(c + 2, r, 2) & 1) goto end;
		}
		cout << "\n";
	}

	end:;

	return toreturn;
}

int main(){
	cout << "\nHide your secret message in an image.\n";
	string filename;
	cout << "\nEnter filename\n";
	cin >> filename;

	CImg<unsigned char> src(filename.c_str());
	int w = src.width();
	int h = src.height();
	w /= 3;
	w *= 3;

	cout << "\nChoose Option : \n1. Encrypt\n2. Decrypt\n";

	int option;
	cin >> option;
	if(option == 1){
		string message;
		cout << "\nEnter Message\n";
		cin.ignore();
		getline(cin, message);    	

		encode(src, message, w);
		src.save(filename.c_str());
		cout << "\nMessage hidden successfully.\n";
	}
	else{
		string result = decode(src, w, h);

		cout << "\nRetrieved Message : " << result << "\n";
	}
	return 0;
}

