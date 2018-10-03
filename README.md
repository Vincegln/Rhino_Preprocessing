# Rhino_Preprocessing
AWK script for preprocessing large nurbs files before using them in Rhino

## What does it do ?
Basically, it explores every .nrb file in one given folder, extract about 700 lines among 3M in each file (by searching specific strings of text as start and stop flags) and copy these lines in new distinct .nrb fils in a "Done" folder.
