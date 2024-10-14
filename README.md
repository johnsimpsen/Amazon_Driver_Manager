Amazon Driver Manager by John Simpsen
Manages drivers (name and area) in a linked list by inputting a list of coordinates from a file and outputting data based on an input from a command file

Input Information:
Inputs driver info based a name and list of coordinates in the format <name><space><coord1><space><coord2><...><coordn><space><coord1>
Each coordinate will be in the format <x><,><y> (note that these can contain negatives)
If the line is not in the format, the driver will be marked as invalid and will not be added to the linked list

Commands:
sort <name/area> - Sorts the list in ascending order on either name or area
<name> - Searches for a specific name in the list
<area> - Searches for a specific area in the list

Output:
Sorting prints the list in the format <name><tab><area><endline> in ascending order
When searching and if found <name><space><area>
When searching and if not found <name/area><space><not found>
