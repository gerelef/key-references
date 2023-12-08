#!/usr/bin/env bash
# TIL https://stackoverflow.com/a/69982088
# Another solution is to use a ramdisk, a filesystem that lives in ram. 
# I always compile my LaTeX on a ramdisk to save disk writes, and also use one for 
# Portage software builds on Gentoo for the same reason.
# sudo mkdir /mnt/ramdisk sudo mount -t tmpfs -o size=2G ramdisk /mnt/ramdisk

bg-job () (
    bash -c "sleep $(( 1 + $RANDOM % 5 )); echo JOB OUTPUT NUMBER: $RANDOM" 
)

# make a temp file safely
ftemp="$(mktemp)"
echo $ftemp

# trap COMMAND SIGNALS, execute comamnd when script exits
trap "rm $ftemp && echo deleted $ftemp" EXIT

thing=$(bg-job >> $ftemp &)

echo "saved $thing from started job"

# number of jobs
nojs=$(( 1 + $RANDOM % 10 ))
for (( c=1; c<=nojs; c++ )) do
    bg-job &
    bg-job >> $ftemp & 
done

echo "waiting on these jobs:"
jobs

wait

echo "FILE $ftemp :: $(cat $ftemp)"
echo "\$thing is still $thing after all of this"
################################################################################
echo "pure process subtitution test"
echo <(bg-job &)
wait

# https://stackoverflow.com/a/20018118
# Note that this has slightly different semantics than having the background job write to a drive backed 
#  file: the background job will be blocked when the buffer is full (you empty the buffer by 
#  reading from the fd). By contrast, writing to a drive-backed file is only blocking 
#  when the hard drive doesn't respond.
echo "process subtitution test with temporary file in memory as input fd 3"
exec 3< <(yes)
for i in 1 2 3; do 
    read <&3 line
    echo "$line"
done

#jobs

echo "killing yes (job id $!)..."
kill $!

echo $(cat <&3)
# disclaimer: if we don't wait, potentially the stdout of the bg job will popout after the
#  "main thread" is done; you can see this in valve's bash scripts, where there will be a dump 
#  because it thinks it sigsegv'd or something else
