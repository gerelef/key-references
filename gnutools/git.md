`HEAD^^` is the father of the father (grandparent) commit
`HEAD~2` is the same.
`HEAD^2` is the second father of the most recent commit.
## Modern git commands
- git switch [-c] [branchName] [--detach commit] 
Switch to a branch, using `git switch branchName`, to switch to new branch`git switch -c branchName`, to detatch HEAD from a branch and switch to a specific commit, `git switch --detach hash`.
- git rm [--cached] [-r] thing
Remove a file from index & fs (same as `rm file` and `git add file`) `git rm file`, to remove directory `git rm -r dir`, to remove a file from the index (but not locally/file) `git rm --cached thing`
- git grep [--recurse-submodules] STRING [hash]
Recursively search for `string`
- git restore [--staged] file
Restore file in staged or working tree.
- git diff [--staged] 
Diff staged files to HEAD.
- git diff branch1 -- branch2
Diff HEAD of two different branches
- git diff [HEAD~] [HEAD]
Diff commit1 and commit2.
- git stash push [-m "message"]
Stash current changes in tracked files. Optionally add a message with ``-m`
- git stash pop 
Pop latest stash added. 
- git stash list
View list of current stashes saved.
## cool git commands
- git config --edit [--global]
Edit local config. Optionally edit global config.
- git status --short --branch
View short status, with branch name included
- git log [--oneline] [--graph]
View log, optionally squashed to oneliners, optionally view the tree visually as well.
- git cherry-pick
- git commit --amend
Update the last commit by adding the currently staged changes, changing the commit's hash.
- git tag [-a v0.0.0 [-m "My message"] [hash]]
Tag HEAD with a tag v0.0.0. Optionally add message, otherwise editor is opened. Optionally tag a specific `commit`.
- git branch --delete `branchName`
Delete local branch `branchName`.
- git push --delete origin branchName
Delete remote (`origin`) branch `branchName`
- git fetch [--prune]
Delete local references to remote branches that have been deleted from remote
- git pull [--rebase | --ff-only] [--autostash]
Pull changes in remote branch. Optionally, rebase only. Optionally, fast-forward only (no conflict resolution). Optionally, autostash changes in staged & working tree.

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

- Revert a specific commit:
`git revert 0c01a9`

- Revert multiple commits:
`git revert branch_name~5..branch_name~2`

## pull

Fetch branch from a remote repository and merge it to local repository.

- Download changes from default remote repository and merge it:
`git pull`

- Download changes from default remote repository and use rebase:
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
## switch  
Switch between Git branches. Requires Git version 2.23+.
- Switch to an existing branch:
`git switch branch_name`

- Switch to the previous branch:
`git switch -`

## reset
Undo commits or unstage changes, by resetting the current Git HEAD to the specified state.
If a path is passed, it works as "unstage"; 
if a commit hash or branch is passed, it works as "uncommit".

- Unstage everything:
`git reset`

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
