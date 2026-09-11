#!/usr/bin/env bash
# Clone a list of repos into one folder and strip their git history,
# so the result can become a single new repo.
#
# Usage:   ./merge-repos.sh repos.txt [target-dir]
# repos.txt format (one per line):
#   <git-url-or-local-path> [folder-name]
# Blank lines and lines starting with # are ignored.

set -euo pipefail

list="${1:?usage: $0 repos.txt [target-dir]}"
target="${2:-42-projects}"

mkdir -p "$target"

# read from fd 3 so git/ssh can't swallow the rest of the list via stdin
while read -r url name <&3 || [[ -n "${url:-}" ]]; do
    [[ -z "$url" || "$url" == \#* ]] && continue

    name="${name:-$(basename "$url" .git)}"
    dest="$target/$name"

    if [[ -e "$dest" ]]; then
        echo "skip: $dest already exists"
        continue
    fi

    echo "==> cloning $url -> $dest"
    if git clone --depth 1 --recurse-submodules "$url" "$dest"; then
        # remove every .git (dirs and submodule .git files) + .gitmodules
        find "$dest" -name .git -prune -exec rm -rf {} +
        rm -f "$dest/.gitmodules"
        echo "    done, .git removed"
    else
        echo "FAILED: $url" >&2
    fi
done 3< "$list"

echo
echo "All done. Next:"
echo "  cd $target && git init && git add . && git commit -m 'Add 42 projects'"
