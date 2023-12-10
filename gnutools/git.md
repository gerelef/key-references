# tldr
most if not all examples were taken by `tldr`
```
sudo dnf install tldr && tldr git
```
## status
- current status of the local repo
`git status`
## add
Adds changed files to the index.
- Add a file to the index:
`git add path/to/file`

- Add all files (tracked and untracked):
`git add -A`

- Only add already tracked files:
`git add -u`

- Also add ignored files:
`git add -f`

- Interactively stage parts of files:
`git add -p`

- Interactively stage parts of a given file:
`git add -p path/to/file`

- Interactively stage a file:
`git add -i`
## restore
Restore working tree files. Requires Git version 2.23+.
- Restore an unstaged file to the version of the current commit (HEAD):
`git restore path/to/file`

- Restore an unstaged file to the version of a specific commit:
`git restore --source commit path/to/file`

- Discard all unstaged changes to tracked files:
`git restore :/`

- Unstage a file:
`git restore --staged path/to/file`

- Unstage all files:
`git restore --staged :/`

- Discard all changes to files, both staged and unstaged:
`git restore --worktree --staged :/`

- Interactively select sections of files to restore:
`git restore --patch`
## commit, push
git commit [-m "commit msg"]
git push [remote_name] [branch_name]
## revert 
Create new commits which reverse the effect of earlier ones.
- Revert the most recent commit:
`git revert HEAD`

- Revert the 5th last commit:
`git revert HEAD~4`

- Revert a specific commit:
`git revert 0c01a9`

- Revert multiple commits:
`git revert branch_name~5..branch_name~2`

- Don't create new commits, just change the working tree:
`git revert -n 0c01a9..9a1743`

## fetch
Download objects and refs from a remote repository.

- Fetch the latest changes from the default remote upstream repository (if set):
`git fetch`

- Fetch new branches from a specific remote upstream repository:
`git fetch remote_name`

- Fetch the latest changes from all remote upstream repositories:
`git fetch --all`

- Also fetch tags from the remote upstream repository:
`git fetch --tags`

- Delete local references to remote branches that have been deleted upstream:
`git fetch --prune`

## pull

Fetch branch from a remote repository and merge it to local repository.

- Download changes from default remote repository and merge it:
`git pull`

- Download changes from default remote repository and use fast-forward:
`git pull --rebase`

- Download changes from given remote repository and branch, then merge them into HEAD:
`git pull remote_name branch`


## branch 
Main Git command for working with branches.

- List all branches (local and remote; the current branch is highlighted by `*`):
`git branch --all`

- List which branches include a specific Git commit in their history:
`git branch --all --contains commit_hash`

- Show the name of the current branch:
`git branch --show-current`

- Create new branch based on the current commit:
`git branch branch_name`

- Create new branch based on a specific commit:
`git branch branch_name commit_hash`
## switch  
Switch between Git branches. Requires Git version 2.23+.
- Switch to an existing branch:
`git switch branch_name`

- Create a new branch and switch to it:
`git switch --create branch_name`

- Create a new branch based on an existing commit and switch to it:
`git switch --create branch_name commit`

- Switch to the previous branch:
`git switch -`

- Switch to a branch and update all submodules to match:
`git switch --recurse-submodules branch_name`

- Switch to a branch and automatically merge the current branch and any uncommitted changes into it:
`git switch --merge branch_name`

## reset
Undo commits or unstage changes, by resetting the current Git HEAD to the specified state.
If a path is passed, it works as "unstage"; 
if a commit hash or branch is passed, it works as "uncommit".

- Unstage everything:
`git reset`

- Unstage specific file(s):
`git reset path/to/file1 path/to/file2 ...`

- Interactively unstage portions of a file:
`git reset --patch path/to/file`

- Undo the last commit, keeping its changes (and any further uncommitted changes) in the filesystem:
`git reset HEAD~`

- Undo the last two commits, adding their changes to the index, i.e. staged for commit:
`git reset --soft HEAD~2`

- Discard any uncommitted changes, staged or not (for only unstaged changes, use `git checkout`):
`git reset --hard`

- Reset the repository to a given commit, discarding committed, 
staged and uncommitted changes since then:
`git reset --hard commit`

## config

git config [--global] user.name "name"
git config [--global] user.email "email@domain.org"

## merge
`git` will attempt merge commit if not fast-forwardable

### steps for fast forward merge 
1. `git checkout [branch we will merge into]`
2. `git merge --ff-only [previous branch]`
3. [OPTIONAL] `git branch -d [previous branch] `

### steps for merge commit 
1. `git checkout [branch we will merge into]`
2. `git merge --no-ff [previous branch]`
3. [OPTIONAL] `git branch -d [previous branch]`

## rebase
Reapply commits from one branch on top of another branch.
Commonly used to "move" an entire branch to another base, 
creating copies of the commits in the new location.

- Rebase the current branch on top of another specified branch:
`git rebase new_base_branch`

- Start an interactive rebase, which allows the commits to be reordered, omitted, combined or modified:
`git rebase -i target_base_branch_or_commit_hash`

- Continue a rebase that was interrupted by a merge failure, after editing conflicting files:
`git rebase --continue`

- Continue a rebase that was paused due to merge conflicts, by skipping the conflicted commit:
`git rebase --skip`

- Abort a rebase in progress (e.g. if it is interrupted by a merge conflict):
`git rebase --abort`

- Move part of the current branch onto a new base, providing the old base to start from:
`git rebase --onto new_base old_base`

- Reapply the last 5 commits in-place, stopping to allow them to be reordered, omitted, combined or modified:
`git rebase -i HEAD~5`

- Auto-resolve any conflicts by favoring the working branch version (`theirs` keyword has reversed meaning in this case):
`git rebase -X theirs branch_name`
