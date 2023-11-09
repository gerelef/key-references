#!/usr/bin/bash
# By default, awk does more than split the input on spaces. 
# It splits based on one or more sequence of space or tab or newline characters. 
# In addition, any of these three characters at the start or end of input gets trimmed 
# and won't be part of field contents. Newline characters come into play if the 
# record separator results in newline within the record content.


# https://earthly.dev/blog/awk-examples/
# Awk is a record processing tool written by Aho, Kernighan, and Weinberger in 1977. 
# Its name is an acronym of their names.

# They created it following the success of the line processing tools sed and grep. 
# Awk was initially an experiment by the authors into whether text processing tools 
# could be extended to deal with numbers. 
# If grep lets you search for lines, and sed lets you do replacements in lines 
# then awk was designed to let you do calculations on lines. 

# by default: input and output on stdin/out

# IMPORTANT NOTE: This data doesn't exist; only version I could find is a .json one but we need a tsv to be truthful to the original project; also awk doesn't play nice with json by default.

# format:
# marketplace customer_id review_id product_id product_parent product_title product_category star_rating helpful_votes total_votes vine verified_purchase review_headline review_body review_date
# US 22480053 R28HBXXO1UEVJT 0843952016 34858117 The Rising Books 5 0 0 N N Great Twist on Zombie Mythos I've known about this one for a long time, but just finally got around to reading it for the first time. I enjoyed it a lot!  What I liked the most was how it took a tired premise and breathed new life into it by creating an entirely new twist on the zombie mythos. A definite must read! 2012-05-03
readonly MOCK_AMAZON_DATA="$(curl https://s3.amazonaws.com/amazon-reviews-pds/tsv/amazon_reviews_us_Books_v1_00.tsv.gz | gzip -d | head -n 10000)"

hello-world () (
    echo "Hello World!" | awk '{ print }' # equivalent to { print $0 }
)

world-hello () (
    # $1, $2, $3 are awk "fields" (columns)
    # $0 is awk for bash's $*, displaying the entire awk "record" (line)
    echo "Hello World!" | awk '{ print $2, $1}'
    # $NF is the last column, "-1" from python, if you will
    # stands for [N]umber of [F]ields
    echo "Hello World!" | awk '{ print $NF, $1}' 
)

configuring-field-separator () (
    # an alternative with a file rather than stdin would be 
    # awk -F "\t" '{ print %6 }' filename.txt | head
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '{ print %6 }' | head
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '{ print $(NF-2) }' | head # same thing as above; equivalent to -3 index in python
    # this just print [N]umber of [R]ecords so far, and the total amount of columns afterwards
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '{ print NR, NF }' | head 
)

awk-regex () (
    echo "aa 10
          bb 20
          cc 30" | awk '/bb/ { print $2 }'
    # matches /Hunger Games/ anywhere on the record
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '/Hunger Games/ { print %6, $8 }' | head | sort | uniq
    
    # exact match on a specific field
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4 == "Hunger Games" { print %6, $8 }' | head 
    # regex on a specific field, not entire record
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ { print %6, $8 }' | head 
)

awk-printf () (
    # just like printf in C, %s is string specifier
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ { printf "%s \t %-20s \t %s \n", $15, $13, $8 }' | head 
    # with substring (shortened to N chars)
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ { printf "%s \t %-20s \t %s \n", $15, substr($13, 1, 20), $8 }' | head
)

awk-begin-end-sums () (
    # sums the ratings on the variable `total`
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ { total = total + $8 print total }'
    # average of all reviews; END runs an action at the end of processing
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ { total = total + $8 } END { print "Average book review:", total/NR, "stars" }'
    # BEGIN runs an action before AWK starts processing
    echo "$MOCK_AMAZON_DATA" | awk -F "\t" '$4~/Hunger Games/ BEGIN { print "Calculating Average ..." }{ total = total + $8 } END { print "Average book review:", total/NR, "stars" }'
)

# awk "file" section begins here:
# awk shebang: #!/usr/bin/env -S gawk -f
#  with .awk file extension

BEGIN { FS = "\t" }
$6~/\(The Hunger Games(, Book 1)?\)$/ { 
    title[$6]=$6 # dictionary
    count[$6]= count[$6] + 1 # dictionary
    total[$6]= total[$6] + $8 # dictionary
  
  
    # Global Average
    g_count = g_count + 1
    g_total = g_total + $8 
}
END {
    # # this modifies the for loop "sort"
    # see more special values here https://www.gnu.org/software/gawk/manual/html_node/Controlling-Scanning.html
    # The value of PROCINFO["sorted_in"] is global. That is, it affects all array traversal for loops.
    if ("sorted_in" in PROCINFO)
        save_sorted = PROCINFO["sorted_in"]
    
    PROCINFO["sorted_in"] = "@val_num_desc"  
    g_score = g_total/g_count 
    for (i in count) {
        printf "---------------------------------------\n"
        printf "%s\n", title[i]
        printf "---------------------------------------\n"
        printf "Ave: %.2f\t Count: %s \n\n", total[i]/count[i], count[i]  
        score = total[i]/count[i]
        printf "%-30s\t", substr(title[i],1,30)
        if (score - g_score > .5)
            printf "👍👍👍" 
        else if (score - g_score > .25)
            printf "👍👍" 
        else if (score - g_score > 0)
            printf "👍" 
        else if (g_score - score  > 1)
            printf "👎👎👎" 
        else if (g_score - score  > .5)
            printf "👎👎" 
        else if (g_score - score  > 0)
            printf "👎"
        printf "\n"
    }
    if (save_sorted)
        PROCINFO["sorted_in"] = save_sorted
    # maybe do other things here . . .
}
