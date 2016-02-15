#!/bin/bash
echo "upload..."
scp -r `ls | grep -v 'bin' | grep -v 'upload.sh'` spm1510@r720-phi.itc.unipi.it:SPM-project
echo "done!"
