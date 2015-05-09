class Solution:
    # @param {string} digits
    # @return {string[]}
    def letterCombinations(self, digits):
        mapper = [" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        graph = map(lambda x: mapper[ord(x) - ord('0')], digits)
        return [''.join(i) for i in itertools.product(*graph)] if digits else []