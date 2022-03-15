/*
[-1, 0, 1, 2, -1, -4]，
-4, -1, -1, 0, 1, 2
0, 5, 2
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() <= 2) {
            return vector<vector<int>>();
        }

        // Sort
        sort(nums.begin(), nums.end());

        // Find
        vector<vector<int>> out;
        int last_i = 0x7FFFFFFF;
        bool bEnd = false;
        for (int i = 0; i < nums.size() - 2; i++) {
            if (nums[i] > 0) {
                bEnd = true;
                break;
            }

            if (nums[i] == last_i) {
                continue;
            }
            else {
                last_i = nums[i];
            }

            int last_j = 0x7FFFFFFF;
            for (int j = nums.size() - 1; j >= i + 1; j--) {
                if (j < 0) {
                    bEnd = true;
                    break;
                }

                if (nums[j] == last_j) {
                    continue;
                }
                else {
                    last_j = nums[j];
                }

                int k = 0 - i - j;
                if (findK(nums, i, j, k)) {
                    // Create new
                    vector<int> item;
                    item.push_back(nums[i]);
                    item.push_back(nums[k]);
                    item.push_back(nums[j]);
                    out.push_back(item);
                }
            }

            if (bEnd) {
                break;
            }
        }

        return out;
    }

    bool findK(const vector<int>& nums, int begin, int end, int k) {
        if (begin == end) {
            if (nums[begin] == nums[k]) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (nums[(begin + end) / 2] == nums[k]) {
                return true;
            }
            else if (nums[(begin + end) / 2] > nums[k]) {
                return findK(nums, begin, (begin + end) / 2, k);
            }
            else {
                return findK(nums, (begin + end) / 2, end, k);
            }
        }
    }
};