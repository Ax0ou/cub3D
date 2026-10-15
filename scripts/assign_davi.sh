#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# Assigns Davi to his issues (label "Davi (parsing)") and to the "Duo" ones.
# GitHub refuses it until Davi has ACCEPTED the invitation:
#     https://github.com/Ax0ou/cub3D/invitations
# Then run once from the repo root:   ./scripts/assign_davi.sh
# ---------------------------------------------------------------------------
set -euo pipefail

DAVI=DaVy0903

if ! gh api "repos/{owner}/{repo}/collaborators/$DAVI" --silent 2>/dev/null; then
	echo "$DAVI has not accepted the invitation yet."; exit 1
fi

for label in "Davi (parsing)" "Duo"; do
	for n in $(gh issue list --state open --limit 100 --label "$label" --json number -q '.[].number'); do
		gh issue edit "$n" --add-assignee "$DAVI" >/dev/null
		echo "  #$n -> $DAVI"
	done
done
echo "Done."
