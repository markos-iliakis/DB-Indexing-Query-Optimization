#! bin/bash
lines=$( wc -l < "$1" )
echo "$lines"
while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "./submission/workloads/small/$line"
done < "$1"