import sys
import random
import time

def run_simulation(iterations=100000):
    """
    ฟังก์ชันสำหรับสุ่มตัวเลขหลักร้อยและคำนวณสมการ n ** 2 * (x % y)
    พร้อมจับเวลาการทำงานทั้งหมด
    """
    
    # เก็บผลลัพธ์รวม (ถ้าต้องการนำไปใช้ต่อ)
    total_sum = 0
    
    print(f"กำลังเริ่มการคำนวณจำนวน {iterations:,} ครั้ง...")
    
    # เริ่มจับเวลา
    start_time = time.time()
    
    for _ in range(iterations):
        # สุ่มเลขหลักร้อย (100 ถึง 999)
        n = random.randint(100, 999)
        x = random.randint(100, 999)
        y = random.randint(100, 999)
        
        # ป้องกันการหารด้วยศูนย์ (Division by zero) แม้เลขหลักร้อยจะไม่เป็น 0 ก็ตาม
        if y == 0:
            continue
            
        # คำนวณสมการ n^2 * (x % y)
        # หมายเหตุ: ในภาษา Python x % y คือ x modulo y
        result = (n ** 2) * (x % y)
        total_sum += result

    # สิ้นสุดการจับเวลา
    end_time = time.time()
    duration = end_time - start_time

    print("-" * 30)
    print(f"เสร็จสิ้นการทำงาน!")
    print(f"เวลาที่ใช้ทั้งหมด: {duration:.4f} วินาที")
    print(f"ค่าเฉลี่ยต่อการคำนวณ: {duration/iterations:.8f} วินาที")
    print(f"ผลรวมตัวอย่าง (Total Sum): {total_sum}")
    print("-" * 30)
    
    # แสดงข้อมูลของระบบเบื้องต้นโดยใช้ sys
    print(f"เวอร์ชันของ Python: {sys.version}")
    print(f"แพลตฟอร์ม: {sys.platform}")

if __name__ == "__main__":
    run_simulation()