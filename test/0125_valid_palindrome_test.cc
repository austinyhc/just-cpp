#include "0125_valid_palindrome.h"

TEST(_125, Demo) {
    Solution s;
    EXPECT_EQ(s.isPalindrome("A man, a plan, a canal: Panama"),
              s._isPalindrome("A man, a plan, a canal: Panama"));
    EXPECT_EQ(s.isPalindrome("race a car"),
              s._isPalindrome("race a car"));
    EXPECT_EQ(s.isPalindrome(" "),
              s._isPalindrome(" "));
    EXPECT_EQ(s.isPalindrome(".,"),
              s._isPalindrome(".,"));
}
