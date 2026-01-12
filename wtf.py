l = int(input("Enter l: "))
r = int(input("Enter r: "))
x = int(input("Enter x: "))
y = int(input("Enter y: "))



for i in range(l, r + 1):
    if i % x == 0 or i % y == 0:
        print(i)
