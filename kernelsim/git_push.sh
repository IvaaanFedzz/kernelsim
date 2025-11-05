#!/bin/bash
REMOTE_URL=$1
if [ -z "$REMOTE_URL" ]; then
  echo "Usage: $0 <git-remote-url>"
  exit 1
fi
git init
git add .
git commit -m "Initial KernelSim"
git branch -M main
git remote add origin "$REMOTE_URL"
git push -u origin main
