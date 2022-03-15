class Solution {
public:
    const string TABLE[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    } 

    vector<string> letterCombinations(string digits) {
        // Check input
        if (digits.length() == 0) {
            return vector<string>();
        }

        vector<string> out;
        out.push_back("");

        for (int i = 0; i < digits.length(); i++) {
            // cout << TABLE[digits[i] - '0'] << endl;

            vector<string> tmp;
            for (int j = 0; j < out.size(); j++) {
                string old_str = out.pop_front();

                const string& str = TABLE[digits[i] - '0'];
                for (int k = 0; k < str.length(); k++) {
                    tmp.push_back(old_str.push_back(str[k]));
                }
            }

            out = tmp;
        }

        return out;
    }
};