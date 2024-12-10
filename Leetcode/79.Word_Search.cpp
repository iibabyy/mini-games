#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	bool	valid_index(int x, int y, int m, int n, char next_char, const vector< vector<bool> >& visited, const vector< vector<char> >& board) {
		if (x < 0 || y < 0)
			return false;
		if (x >= n || y >= m)
			return false;
		if (board[y][x] != next_char)
			return false;
		if (visited[y][x] == true)
			return false;
		return true;
	}

    bool	find_next_from_last(int x, int y, const int m, const int n, const string& word, int index, vector<vector<bool>>& visited, const vector<vector<char>>& board) {

		if (index == 0)
			return (true);

		if (visited[y][x] == true)	{ return false; }
		else	{ visited[y][x] = true; }
		char	next_char = word[index - 1];

		if (valid_index(x + 1, y, m, n, next_char, visited, board)) {
			if (find_next_from_last(x + 1, y, m, n, word, index - 1, visited, board) == true) { return true; }
		} if (valid_index(x - 1, y, m, n, next_char, visited, board)) {
			if (find_next_from_last(x - 1, y, m, n, word, index - 1, visited, board) == true) { return true; }
		} if (valid_index(x, y + 1, m, n, next_char, visited, board)) {
			if (find_next_from_last(x, y + 1, m, n, word, index - 1, visited, board) == true) { return true; }
		} if (valid_index(x, y - 1, m, n, next_char, visited, board)) {
			if (find_next_from_last(x, y - 1, m, n, word, index - 1, visited, board) == true) { return true; }
		}
		visited[y][x] = false;
		return false;
	}

	bool	find_word_from_last(int x, int y, int m, int n, const vector< vector<char> >& board, const string& word, vector< vector<bool> > visited) {
        int index = word.size() - 1;
        if (board[y][x] != word[index])
            return false;

		return (find_next_from_last(x, y, m, n, word, index, visited, board));
	}

   bool	find_next_from_first(int x, int y, const int m, const int n, const string& word, int index, vector<vector<bool>>& visited, const vector<vector<char>>& board) {

		if (index == word.size() - 1)
			return true;

		if (visited[y][x] == true)	{ return false; }
		else	{ visited[y][x] = true; }

		char	next_char = word[index + 1];

		if (valid_index(x + 1, y, m, n, next_char, visited, board)) {
			if (find_next_from_first(x + 1, y, m, n, word, index + 1, visited, board) == true) { return true; }
		} if (valid_index(x - 1, y, m, n, next_char, visited, board)) {
			if (find_next_from_first(x - 1, y, m, n, word, index + 1, visited, board) == true) { return true; }
		} if (valid_index(x, y + 1, m, n, next_char, visited, board)) {
			if (find_next_from_first(x, y + 1, m, n, word, index + 1, visited, board) == true) { return true; }
		} if (valid_index(x, y - 1, m, n, next_char, visited, board)) {
			if (find_next_from_first(x, y - 1, m, n, word, index + 1, visited, board) == true) { return true; }
		}
		visited[y][x] = false;
		return false;
	}

	bool	find_word_from_first(int x, int y, int m, int n, const vector< vector<char> >& board, const string& word, vector< vector<bool> >& visited) {
        int index = 0;
        if (board[y][x] != word[index])
            return false;

		return (find_next_from_first(x, y, m, n, word, index, visited, board));
	}

	bool exist(vector<vector<char>>& board, string word) {
		int	m, n;

		int first_count = 0;
		int last_count = 0;
		for (; word[first_count] && word[first_count] == word[0]; first_count++);
		for (int i = word.size() - 1; i && word[i] == word[word.size() - 1]; i--)
			++last_count;

		bool from_first = first_count > last_count;

		m = board.size();
		n = board[0].size();
		
		vector< vector<bool> > visited(m, vector(n, false));

		for (int y = 0; y < m; y++) {
			for (int x = 0; x < n; x++) {
				if (from_first? find_word_from_last(x, y, m, n, board, word, visited) : find_word_from_first(x, y, m, n, board, word, visited))
					return true;
			}
		}

		return false;
    }
};