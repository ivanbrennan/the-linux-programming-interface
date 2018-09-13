#! /usr/bin/env bash

set -eu

trap cleanup EXIT

main() {
    printf '%sTest empty file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_empty_file

    printf '%sTest small file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_small_file

    printf '%sTest large file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_large_file

    printf '%sTest small sparse file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_small_sparse_file

    printf '%sTest sparse file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_sparse_file

    printf '%sTest large sparse file%s\n' $(tput bold) $(tput sgr0)
    echo     '---------------'
    test_large_sparse_file
}

test_empty_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=0 count=0 2>/dev/null
    compare_file_sizes
}

test_small_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=0 count=4 2>/dev/null
    compare_file_sizes
}

test_large_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=0 count=12 2>/dev/null
    compare_file_sizes
}

test_small_sparse_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=1 count=0 2>/dev/null
    compare_file_sizes
}

test_sparse_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=8 count=0 2>/dev/null
    compare_file_sizes
}

test_large_sparse_file() {
    dd if=/dev/urandom of=old-file bs=512 seek=9 count=0 2>/dev/null
    compare_file_sizes
}

compare_file_sizes() {
    local old_blocks old_bytes new_blocks new_bytes

    fileio/sparse-copy old-file new-file
    (
        trap cleanup EXIT

        old_blocks=$(disk_blocks old-file)
        old_bytes=$(file_bytes old-file)
        new_blocks=$(disk_blocks new-file)
        new_bytes=$(file_bytes new-file)

        if [ "$old_blocks" != "$new_blocks" ] || \
            [ "$old_bytes" != "$new_bytes" ]
        then
            echo "blocks on disk:"
            echo "  old-file $old_blocks"
            echo "  new-file $new_blocks"

            echo "file bytes:"
            echo "  old-file $old_bytes"
            echo "  new-file $new_bytes"

            printf '%s✗%s\n\n' $(tput setaf 1) $(tput sgr0)

            exit 1
        elif ! diff --brief old-file new-file >/dev/null
        then
            echo "file contents differ"

            printf '%s✗%s\n\n' $(tput setaf 1) $(tput sgr0)

            exit 1
        else
            printf '%s✓%s\n\n' $(tput setaf 2) $(tput sgr0)
        fi
    )
}

disk_blocks() {
    du --block-size=$(stat --format=%o "$1") "$1" | cut -f 1
} 2>/dev/null

file_bytes() {
    du --apparent-size --bytes "$1" | cut -f 1
} 2>/dev/null

cleanup() {
    rm -f old-file new-file
}

main
