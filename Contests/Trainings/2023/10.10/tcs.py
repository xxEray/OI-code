from math import *

n = int(input())

cnt = 0
x = -1
y = 0
for i in range(n + 1):
	if i < 2 ** (n - i) - 1 or 2 ** i < 2 ** (2 ** (n - i)) - 1:
		cnt += 2 ** i
	else:
		if x == -1:
			x = 2 ** (i - 1)
			y = 2 ** (n - i)
		cnt += 2 ** (2 ** (n - i)) - 1

print(f'{x = }, {y = }')

if x < 2 ** y - 1:
	mn = y * (2 ** (y - 1))
	mx = mn + y
else:
	mn = y * (2 ** (y - 1))
	mx = y * (2 ** (y - 1)) + y * (2 ** y - 1)
	print(f'initial {mn = }, {mx = }')
	z = x - 2 ** y + 1
	for i in range(1, 2 * y + 1):
		v = min(comb(2 * y, i) - comb(y, i), z)
		mn += i * v
		z -= v
		print(f'{mn = }')
	z = x - 2 ** y + 1
	for i in range(2 * y, 0, -1):
		v = min(comb(2 * y, i) - (0 if i < y else comb(y, i - y)), z)
		mx += i * v
		z -= v
print(cnt, mn, mx)
