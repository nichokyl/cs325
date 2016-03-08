d = []
T = []


# Thanks to senderle on Stack Overflow for help with I/O
fi = open("Data.txt", "r")

for columns in (row.strip().split("\t") for row in fi):
   print columns[0] + "\t" + columns[1]
