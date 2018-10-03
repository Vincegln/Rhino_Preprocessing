# Rhino_Preprocessing
AWK script for preprocessing large nurbs files before using them in Rhino

## What does it do ?
Basically, it explores every .nrb file in one given folder, extract about 700 lines among 3 millions in each file (by searching specific strings of text as start and stop flags) and copy these lines in new distinct .nrb fils in a "Done" folder.

## Is it efficient ?

Compared to a C++ naive solution I made before, it processes 70 files in 1mn16s when it took around 2 minutes to go through 3 files.
