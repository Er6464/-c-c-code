import time

start = time.perf_counter()

# algorithm
for i in range(10_000_000):
    pass

end = time.perf_counter()
print(end - start)
