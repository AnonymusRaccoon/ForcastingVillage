#!/usr/bin/python3
import sys, random

try:
    min_width = int(sys.argv[1])
    min_height = int(sys.argv[2])
    max_width = int(sys.argv[3])
    max_height = int(sys.argv[4])
    prob = int(sys.argv[5])
    entities =  sys.argv[6:]
except IndexError:
    print(f"Usage: {sys.argv[0]} y x min y x max entities name")
    sys.exit(1)
print("<gc_entities>")
for i in range(max_height - min_height + 1):
    for j in range(max_width - min_width + 1):
        if prob < random.randint(0, 101):
            continue
        x = i + min_width
        y = j + min_height
        entity = random.choice(entities)
        print(f"""<gc_entity>
    <transform_component>
        <Position x="0" y="0" />
        <Size x="150" y="200" />
    </transform_component>
    <renderer src="{entity}">
        <Rect height="auto" width="auto" top="0" left="0" />
    </renderer>
    <map_linker x="{x}" y="{y}" />
</gc_entity>""")
print("</gc_entities>")