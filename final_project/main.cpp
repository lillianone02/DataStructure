#define FILE_EXTENSION ".txt" //最新版本
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <memory>
#include <cctype>
#include <filesystem>
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

void insert(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

void insertReverse(TrieNode *root, const string &word) {
    TrieNode *pCrawl = root;
    
    // Use a reverse iterator to go through the word in reverse order
    for (auto rit = word.rbegin(); rit != word.rend(); ++rit) {
        int index = tolower(*rit) - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}

// exact_search
bool search(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}

// prefix_search
bool prefix_search(struct TrieNode *root, const string &prefix)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i] - 'a';
        if (!pCrawl->children[index])
            return false; // Return false immediately if the current part of prefix is not present.

        pCrawl = pCrawl->children[index];
    }

    return true; // If we've successfully traversed the prefix without encountering a NULL, the prefix is present.
}

// suffix_search
bool suffixSearch(TrieNode *root, const string &suffix) {
    TrieNode *pCrawl = root;
    for (int i = suffix.length() - 1; i >= 0; i--) {
        int index = tolower(suffix[i]) - 'a';
        if (!pCrawl->children[index])
            return false; // If the current character is not found, return false.
        pCrawl = pCrawl->children[index];
    }
    return pCrawl != nullptr && pCrawl->isEndOfWord; // Check if we're at the end of a word.
}

// wildcard_search 
bool wildcardSearch(TrieNode* root, const string& word, int index) {
    if (!root) {
        return false;
    }
    
    if (index == word.size()) {
        return root->isEndOfWord;
    }
    
    if (word[index] == '*') {
        // Try all possible paths
        for (auto &child : root->children) {
            if (wildcardSearch(child, word, index + 1) || (child && wildcardSearch(child, word, index))) {
                return true;
            }
        }
    } else {
        int charIndex = tolower(word[index]) - 'a';
        return wildcardSearch(root->children[charIndex], word, index + 1);
    }

    return false;
}

// string parser : output vector of strings (words) after parsing
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}
// string split
vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;

	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}

	return res;
}

int main(int argc, char *argv[])
{
    clock_t start, end_time;
    start = clock();
    cout << "debug 1"<< endl;

    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);
    cout << "debug 2"<< endl;
	// Read File & Parser Example


	TrieNode* t[10000];
    for (int i = 0; i < 10000; ++i) {
        t[i] = getNode(); // Each t[i] is now pointing to a root node of a Trie
    }
	TrieNode* t_reverse[10000];
    for (int i = 0; i < 10000; ++i) {
        t_reverse[i] = getNode(); // Each t[i] is now pointing to a root node of a Trie
    }
	vector<string> directory(10000);

    int how_many_txt = 0;
    string file, title_name, tmp;
    fstream fi;
    ofstream fout;
    char buf[128], buffer[128];
    for(int i = 0; i < data_dir.size(); i++)
        buffer[i] = data_dir[i];
    sprintf(buf, "%s%d.txt", buffer, how_many_txt);
    fi.open(buf, ios::in);
	while(fi.is_open())
    {
        if (!fi) {
            cerr << "Failed to open file: " << buf << endl;
            break; // Exit the loop if we fail to open the next file
        }

        vector<string> tmp_string;
        cout << "debug 5"<< endl;
        // GET TITLENAME
        getline(fi, title_name);
        directory[how_many_txt] = title_name;

        // GET TITLENAME WORD ARRAY
        tmp_string = split(title_name, " ");
        cout << "debug 6"<< endl;
        vector<string> title = word_parse(tmp_string);
        cout << "debug 7"<< endl;
        for(auto &word : title){
            insert(t[how_many_txt], word);

            reverse(word.begin(), word.end());
            insert(t_reverse[how_many_txt], word);
        }
        cout << "debug 8"<< endl;
        // GET CONTENT LINE BY LINE
        while(getline(fi, tmp)){
            cout << "debug 9"<< endl;
            // GET CONTENT WORD VECTOR
            tmp_string = split(tmp, " ");

            // PARSE CONTENT
            vector<string> content = word_parse(tmp_string);

            for(auto &word : content){
                insert(t[how_many_txt], word);

                reverse(word.begin(), word.end());
                insert(t_reverse[how_many_txt], word);
            }
            cout << "debug 10"<< endl;
        }
        cout << "debug 3"<< endl;
        // CLOSE FILE
        fi.close();
        cout << "debug 4"<< endl;
        how_many_txt++;
        sprintf(buf, "%s%d.txt", buffer, how_many_txt);
        fi.open(buf, ios::in);
    }
    //cout << how_many_txt << endl;

    // read query 
    string whole_line;

    fi.open(query, ios::in);
    fout.open(output, ios::out);
    while(getline(fi, whole_line))
    {
        //cout << endl << whole_line << endl;

        int now_pos = 0;
        int len = whole_line.size();
        int and_or_mode = 0; // 0是無, 1是且, 2是或, 3是差
        bool total_result[10000] = {0};

        while(now_pos < len)
        {
            // 且
            if(whole_line[now_pos] == '+')
            {
                now_pos += 2;
                and_or_mode = 1;
            }

            // 或
            else if(whole_line[now_pos] == '/')
            {
                now_pos += 2;
                and_or_mode = 2;
            }

        	// 差
			else if(whole_line[now_pos] == '-')
			{
				now_pos += 2;
				and_or_mode = 3;
			}

            // 完整搜尋
            else if(whole_line[now_pos] == '"')
            {
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '"')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 2;



                transform(test.begin(), test.end(), test.begin(), ::tolower);

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(search(t[i], test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }
        		else if(and_or_mode == 3) 
				{
            		for(int i = 0; i < how_many_txt; i++)
                		total_result[i] = total_result[i] && !result[i];
        		}
            }

            // suffix 搜尋
            else if(whole_line[now_pos] == '*')
            {
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '*')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 2;


                transform(test.begin(), test.end(), test.begin(), ::tolower);
                reverse(test.begin(), test.end());

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(suffixSearch(t_reverse[i], test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }
        		else if(and_or_mode == 3) 
				{
            		for(int i = 0; i < how_many_txt; i++)
                		total_result[i] = total_result[i] && !result[i];
        		}
            }
			// wildcard 搜尋
			else if (whole_line[now_pos] == '<') 
			{
            	int right_boundary;
            	for (right_boundary = now_pos + 1; right_boundary < len; right_boundary++) {
                	if (whole_line[right_boundary] == '>') {
                	    break;
            		}
            	}

            	string wildcard_query = whole_line.substr(now_pos + 1, right_boundary - now_pos - 1);
            	now_pos = right_boundary + 2;

            	// Convert wildcard_query to lowercase
            	transform(wildcard_query.begin(), wildcard_query.end(), wildcard_query.begin(), ::tolower);

            	bool result[10000] = {0};
            	for (int i = 0; i < how_many_txt; i++) {
                	if (wildcardSearch(t[i], wildcard_query, 0)) {
                    	result[i] = 1;
                	}
            	}

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }
        		else if(and_or_mode == 3) 
				{
            		for(int i = 0; i < how_many_txt; i++)
                		total_result[i] = total_result[i] && !result[i];
        		}
        	}

            // prefix 搜尋
            else
            {
                int right_boundry;
                for(right_boundry = now_pos; right_boundry < len; right_boundry++)
                    if( whole_line[right_boundry] == ' ' )
                        break;

                string test;
                test = whole_line.substr(now_pos, right_boundry - now_pos);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 1;


                transform(test.begin(), test.end(), test.begin(), ::tolower);

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(prefix_search(t_reverse[i], test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }
        		else if(and_or_mode == 3) 
				{
            		for(int i = 0; i < how_many_txt; i++)
                		total_result[i] = total_result[i] && !result[i];
        		}
            }
        }
        // 最終輸出
        int all_zero = 1;
        for(int i = 0; i < how_many_txt; i++)
            if(total_result[i])
            {
                fout << directory[i] << "\n";
                all_zero = 0;
            }

        if(all_zero)
            fout << "Not Found!" << "\n";

    }
    fi.close();
    fout.close();

    end_time = clock();
    cout << (double) (end_time - start) / CLOCKS_PER_SEC << " S" << endl;
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C


