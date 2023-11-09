#!/usr/bin/bash
# https://earthly.dev/blog/jq-select/
readonly jq_json="$(curl -L --header "X-GitHub-Api-Version:2022-11-28" https://api.github.com/repos/jqlang/jq)"
readonly jq_issues_json="$(curl -L --header "X-GitHub-Api-Version:2022-11-28" https://api.github.com/repos/jqlang/jq/issues?per_page=5)"

jq-pretty-print () (
    # '.' is identity filter
    echo '{"key1":{"key2":"value1"}}' | jq '.'
)

jq-get-values () (
    # by name
    echo "$jq_json"
    echo "$jq_json" | jq ' .name'
    echo "$jq_json" | jq ' .owner'
    echo "$jq_json" | jq ' .owner.login'
    
    # by index
    echo "$jq_issues_json" | jq '.[4]'
    echo "$jq_issues_json" | jq '.[2:4]'
    echo "$jq_issues_json" | jq '.[2:]'
    echo "$jq_issues_json" | jq '.[-2:]'
    echo "$jq_issues_json" | jq '.[:4]'
    
    # hybrid
    echo "$jq_issues_json" | jq '.[4].title'
    # [] selects everything
    # gets the title from all elements
    echo "$jq_issues_json" | jq '.[].title' 
)

jq-flags () (
    # raw strings
    echo '["1","2","3"]' | jq -r '.[]'
    # join strings
    echo '["1","2","3"]' | jq -j '.[]'
)

jq-valid-json () (
    echo "$jq_issues_json" | jq '[ .[].title ]'
)

jq-multiple-values () (
    # this prints all titles, then all numbers, etc...
    echo "$jq_issues_json" | jq '.[].title, .[].number'
    # NOT the same thing as above! this prints both results (just on a different line)
    echo "$jq_issues_json" | jq '[] | .title .number'
)

jq-object-constructor () (
    echo "$jq_issues_json" | jq '{ title: .title, number: .number, labels: .labels}'
)

jq-builtins () (
    echo '["3","2","1"]' | jq 'sort'
    echo '["3","2","1"]' | jq 'reverse'
    echo '["3","2","1"]' | jq 'length'
)
