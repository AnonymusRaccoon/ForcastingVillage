#!/usr/bin/python3
import sys

try:
    width = int(sys.argv[1])
    height = int(sys.argv[2])
except IndexError:
    print(f"Usage: {sys.argv[0]} width height")
    sys.exit(1)

print("<gc_map >\n\t<vertex_data>")
for i in range(width):
    print("\t\t<line>")
    for i in range(height):
        print("\t\t\t<row height=\"0\" />")
    print("\t\t</line>")
print("\t</vertex_data>\n\t<tiles_data>\n\t</tiles_data>\n</gc_map>")