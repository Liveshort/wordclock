
import math

vert_order = []

for i in range(11):
    for j in range(11):
        if i % 2 == 0:
            vert_order.append(11*i + j + 1)
        else:
            vert_order.append(11*i + 11 - j)

print("vert_order:", vert_order)

temp_order = []

for i in range(11):
    for j in range(11):
        temp_order.append(vert_order[11*j + i])

hor_order = []

for i in range(11):
    if i % 2 == 0:
        hor_order.extend(temp_order[11*i:11*(i+1)])
    else:
        hor_order.extend(reversed(temp_order[11*i:11*(i+1)]))

hor_order.extend([126, 125, 124, 123, 122])

print("hor_order:", hor_order)

sqrt = []

for i in range(256):
    sqrt.append(int(i*i/255))

print("sqrt:", sqrt)

vert_to_row = [0]*(11*11)

for i in range(11):
    for j in range(11):
        vert_to_row[vert_order[11*i+j]-1] = j
for _ in range(5):
    vert_to_row.append(11)

print("vert_to_row:", vert_to_row)
