#include <iostream>
#include <string>
#include <vector>

int getShift(std::string const& text, int len) {
	if(len==0) return -1;
	if(len<3) return 0;
	for(int i=len/2; i>0; i--)
		if(text.substr(0,i)==text.substr(len-i,i))
			return i;
	return 0;

	// algorithm avoiding substr() //
	//if(len==0) return -1;
	//if(len<3) return 0;
	//for(int i=len/2; i>=0; i--) {
	//	for(int j=0; j<i; j++) {
	//		if(text[j]!=text[len-i+j]) {
	//			break;
	//		}
	//		if(j+1==i) {
	//			return i;
	//		}
	//	}
	//}
	//return 0;
}

std::vector<int> genTable(std::string const& text) {
	std::vector<int> table;
	int shift;
	for(int i=0; i<=text.size(); i++) {
		shift = getShift(text, i);
		table.push_back(shift);
	}
	return table;
}

std::vector<int> kmpSearch(std::string const& text, std::string const& pattern) {
	std::vector<int> shift = genTable(pattern);
	std::vector<int> matches;
	int ppos = 0;
	for(int tpos=0; tpos<text.size(); tpos++) {
		while(ppos>=0 && text[tpos]!=pattern[ppos])
			ppos = shift[ppos];
		ppos++;
		if(ppos==pattern.size()-1) {
			ppos = shift[ppos];
			matches.push_back(tpos);
		}
	}
	return matches;
}

int main(int argc, char** argv) {
		std::string text;
		std::string pattern;
	try {
		pattern = argv[2];
		text = argv[1];
	} catch(...) {
		std::cerr << "ERROR: cannot parse command line arguments!" << std::endl;
		return 1;
	}
	// ERROR-HANDLING!!! //
	std::vector<int> matches = kmpSearch(text,pattern);
	if(matches.size()<1) {
		std::cout << "No matches found." << std::endl;
		return 0;
	}
	std::cout << matches.size() << " matches found at position(s): ";
	for(int e : matches)
		std::cout << e << " ";
	std::cout << std::endl;
	return 0;
}
