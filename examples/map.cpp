#include <iostream>
#include <map>
using namespace std;

int main() {

	string test = "Hello world, my name is Ian! Wwwhhhhaaaaooooo!";

	map <char, int> freq;

	for (int i = 0 ; i < test.length() ; i++) {

		char letter = test[i];

		if (freq.find(letter) == freq.end()){
			freq[letter] = 0;
		}
		
		freq[letter]++;

		// cout << freq[letter] << ", " << letter<< endl;
	}


	for (auto itr = freq.begin() ; itr != freq.end() ; itr++) { 
		cout << itr->first << ": " << itr->second << endl; 
	}

}
