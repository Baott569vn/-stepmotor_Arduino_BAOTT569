# Điều Khiển Động Cơ Bước Arduino

**Mô tả:** Đoạn mã Arduino này mô phỏng việc điều khiển một động cơ bước sử dụng các nút nhấn ngoại vi (chuyển động tiến, chuyển động lùi và dừng) và dữ liệu nhập từ Serial Monitor. Động cơ bước có thể di chuyển theo hướng tiến hoặc lùi với số bước được xác định, và có nút dừng để dừng động cơ bất cứ lúc nào.

**Nhóm Tác Giả:** Gia Bảo, Huy Hoàng, Thanh Tùng

**Ngày:** 29-11-2023

**Phiên Bản:** 1.0

## Kết Nối Chân:

- **Pulse (puL_):** Kết nối đến đầu vào Pulse của trình điều khiển động cơ bước
- **Direction (diR_):** Kết nối đến đầu vào Direction của trình điều khiển động cơ bước
- **Nút Tiến (forward_):** Kết nối đến đầu vào nút tiến
- **Nút Lùi (reverse_):** Kết nối đến đầu vào nút lùi
- **Nút Dừng (stop_):** Kết nối đến đầu vào nút dừng (không được thay đổi)

## Lệnh Serial:

- Nhập một số nguyên dương hoặc âm để di chuyển động cơ theo hướng tiến hoặc lùi.

## Ghi Chú:

- Mã sử dụng ngắt để phát hiện khi nào nút dừng được nhấn.
- Hãy đảm bảo kết nối đúng và cung cấp nguồn điện phù hợp cho trình điều khiển động cơ bước.

## Hướng Dẫn Sử Dụng:

1. **Chuẩn Bị:**
   - Kết nối đúng chân theo hướng dẫn.
   - Cung cấp nguồn điện cho động cơ bước.

2. **Chạy Chương Trình:**
   - Nạp chương trình vào Arduino.
   - Mở Serial Monitor.
   - Nhập số bước và nhấn Enter để di chuyển động cơ.

3. **Dừng Động Cơ:**
   - Nhấn nút dừng hoặc nhập giá trị 0 từ Serial Monitor để dừng động cơ.

## Đóng Góp:

Chúng tôi rất hoan nghênh sự đóng góp của bạn! Hãy xem [Hướng Dẫn Đóng Góp](CONTRIBUTING.md) để biết thêm chi tiết.

## Báo Lỗi:

Nếu bạn phát hiện lỗi, vui lòng tạo một [Báo Lỗi Mới](https://github.com/your-username/your-project/issues).

## Giấy Phép:

Mã nguồn này free.

## Liên Hệ:

Nếu bạn có bất kỳ câu hỏi hoặc đề xuất nào, hãy liên hệ chúng tôi qua email: your.email@example.com.

## Tài Nguyên Bổ Sung:

- [Hướng Dẫn Sử Dụng Động Cơ Bước](https://link-to-additional-resources.com)
- [Tài Liệu Kỹ Thuật Động Cơ Bước](https://link-to-additional-docs.com)