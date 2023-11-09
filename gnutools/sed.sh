#!/usr/bin/bash
# https://www.grymoire.com/Unix/Sed.html#uh-0
# [S]tream [ED]itor

# sed substitute command
sed-substitute () (
    # s stands for substitute (obv), / are delimiters; three delimiters are required.
    # changes all occurences of the regex into a new value, from the "old"to the "new" file
    sed 's/day/night' <old >new
    # same thing as above
    sed 's/day/night' old >new
    # same thing, for stdin/out
    echo day | sed 's/day/night'
    # line oriented, will change the FIRST occurence of the match only (i lied earlier) 
    echo "one two three, one two three
        four three two one
        one hundred" | sed 's/one/ONE'
    # can be set to global (change every word)
    echo "one two three, one two three
        four three two one
        one hundred" | sed 's/one/ONE/g'
    # this just escapes the delimiter
    sed 's/\/usr\/local\/bin/\/common\/bin/' <old >new 
    # other delimiters can be defined, three examples: 
    sed 's_/usr/local/bin_/common/bin_' <old >new
    sed 's:/usr/local/bin:/common/bin:' <old >new
    sed 's|/usr/local/bin|/common/bin|' <old >new
    
    # & is a wildcard for "whatever matched the regex"
    # substituting (unknown) matches, and putting (for example) parentheses around it:
    sed 's/[a-z]*/(&)/' <old >new
    
    # extended regex (for example, with +)
    # note: without extended regex, parentheses need to be escaped \(like this\)
    echo "123 abc" | sed -r 's/[0-9]+/& &/'
    
    # multiple remembered patterns
    # switch two words around
    # this is cancer
    # Note the space between the two remembered patterns. This is used to make sure
    # two words are found. However, this will do nothing if a single word 
    # is found, or any lines with no letters.
    sed -r 's/([a-z]*) ([a-z]*)/\2 \1/'
    
    # sed is not recursive! no infinite loops.
    
    # case insensitive 
    sed -n 's/foo/bar/I' <old >new
    
    # multiple substitutions
    sed -e 's/a/A/g' \
        -e 's/e/E/g' \
        -e 's/i/I/g' \
        -e 's/o/O/g' \
        -e 's/u/U/g'  <old >new
)

sed-printing () (
    # this will print everything, and lines which have PATTERN will print twice
    sed 's/PATTERN/&/p' file
    # -n disables printing, this will print nothing
    sed -n 's/PATTERN/&/' file
    # this is just like grep, only lines that match PATTERN will print
    sed -n 's/PATTERN/&/p' file
    
)
