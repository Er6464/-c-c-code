import time

start = time.time()

# โค้ดที่อยากจับเวลา
for i in range(10_000_000):
    pass

end = time.time()
print("time:", end - start, "sec")
