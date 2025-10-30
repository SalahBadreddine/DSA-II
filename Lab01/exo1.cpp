#include <iostream>
#include <vector>
#include <string>

using namespace std ;

bool* wordPuzzle(vector<vector<char>> M, vector<string> words) {
    int n = words.size();
    bool* res = new bool[n];  // Result array to store if each word is found or not
    int row = M.size();
    int col = M[0].size();

    // Initialize result array with false (i.e., none of the words found yet)
    for (int i = 0; i < n; i++) {
        res[i] = false;
    }

    for (int w = 0; w < n; w++) {
        string word = words[w];
        int word_len = word.length();

        // Loop through each character in the matrix
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // Check if current matrix character matches the first character of the word
                if (M[i][j] == word[0]) {
                    // We have 8 possible paths
                    int path[8][2] = {{1, 0},  {1, -1}, {1, 1},  {0, 1}, {0, -1},
                                      {-1, 1}, {-1, -1}, {-1, 0}};
                    for (int t = 0; t < 8; t++) {
                        int k = i + path[t][0], q = j + path[t][1];  // Next step on path
                        int s = 1;  // Start from the second character
                        
                        // Check if the word can be matched along this path
                        while (s < word_len && k < row && k >= 0 && q < col && q >= 0 && M[k][q] == word[s]) {
                            s++;
                            k += path[t][0];
                            q += path[t][1];
                        }

                        // If we successfully matched the whole word, mark it as found
                        if (s == word_len) {
                            res[w] = true;
                            break;  // No need to check further if word is found
                        }
                    }
                }
                // If word was found, no need to continue for this word
                if (res[w]) break;
            }
            if (res[w]) break;
        }
    }

    return res;  
}

int main() {
    // Matrix of characters
    vector<vector<char> > M;
    
    // Row by row initialization using push_back()
    M.push_back({'J', 'S', 'O', 'L', 'U', 'T', 'I', 'S'});
    M.push_back({'S', 'U', 'N', 'A', 'R', 'U', 'U', 'A'});
    M.push_back({'N', 'E', 'P', 'T', 'U', 'N', 'E', 'T'});
    M.push_back({'S', 'O', 'N', 'I', 'E', 'I', 'S', 'U'});
    M.push_back({'R', 'C', 'E', 'V', 'T', 'R', 'E', 'R'});
    M.push_back({'A', 'H', 'T', 'R', 'A', 'E', 'S', 'N'});
    M.push_back({'M', 'M', 'E', 'R', 'C', 'U', 'R', 'Y'});

    // Array of words
    vector<string> words;
    words.push_back("EARTH");
    words.push_back("JUPITER");
    words.push_back("MARS");
    words.push_back("MERCURY");
    words.push_back("NEPTUNE");
    words.push_back("SATURN");
    words.push_back("URANUS");
    words.push_back("VENUS");
    bool* res = wordPuzzle(M, words);

    // Output the results
    for (int i = 0; i < 8; i++) {
        cout << words[i] << " found: " << (res[i] ? "Yes" : "No") << endl;
    }

    return 0;
}


