import random

hidden_number = random.randint(1, 1_000_000)

while True:
  n = int(input())

  if n == hidden_number:
    print("Found!")
    break
  elif n > hidden_number:
    print("Too high!")
  else:
    print("Too low!")