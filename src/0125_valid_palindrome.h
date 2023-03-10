#include "utils/base.h"

using std::string;

class Solution {
public:
    bool _isPalindrome(string s) {
        int i = 0;
        int j = s.size() - 1;
        while (i < j) {
            while (i < j && !isalnum(s[i])) ++i;
            while (i < j && !isalnum(s[j])) --j;

            if (tolower(s[i++]) != tolower(s[j--]))
                return false;
        }
        return true;
    }

    // Recursive solution if the stack size is permitted
    bool isPalindrome(string s) {
        int lo = 0;
        int hi = s.size() - 1;
        return isPalindrome(s, lo, hi);
    }

    bool isPalindrome(string const& s, int lo, int hi) {

        while (!isalnum(s[lo])) ++lo;
        while (!isalnum(s[hi])) --hi;

        if (lo >= hi) { return true; }

        if (tolower(s[lo++]) == tolower(s[hi--])) {
            return isPalindrome(s, lo, hi);
        }
        return false;
    }
};
