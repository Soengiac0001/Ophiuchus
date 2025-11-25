#!/bin/bash
make clean
make
if [ -d .git ]; then
    echo "🔁 Running git-update (repo detected)..."
    make git-update
else
	echo "⚠️  Skipping git-update: no .git directory (not a git repo)."
fi
