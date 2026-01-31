from cs50 import get_int

while True:
    h = get_int("Height: ")
    if (h > 0 and h <= 8):
        break

brick = "#"

for i in range(1, h+1):
    print(f"{' '*(h-i)}{brick*i}  {brick*i}")
