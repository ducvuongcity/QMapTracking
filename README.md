# QMapTracking
## Task 1: Đọc Quỹ tích MMS
### Input :  2 file
- sample_Tizu.tif (Bản đồ)
- sample_DriveMMS.txt ( Đường đi ô tô tự lái goole) 4 Cột X,Y,Z,T(x,y,z là tọa độ ô tô tại thời điểm t trên bản đồ)

### Output
- File  sample_Tizu.tif hiển thị dưới dạng ảnh 2D
- File  sample_DriveMMS.txt hiển thị dưới dạng quỹ tích MMS(Quỹ tích MMS là đường đi của ô tự lái của google trên bản đồ )

### Yêu cầu: 
- Đọc file sample_DriveMMS.txt lấy ra 4 tọa độ X,Y,Z,T
- Dùng 2 tọa độ X,Y vẽ quỹ tích MMS lên bản đồ (sample_Tizu.tif)
- Sau Khi vẽ quỹ tích MMS ấn vào 1 điểm chỉ định trên bản đồ (trùng với quỹ tích MMS) sẽ lấy ra 3 tọa độ x,y,z theo t (tạm thời cứ lấy ra 4 lable để task 2 sẽ dùng)


## Task 2: Liên kết Quỹ tích MMS và Ảnh chụp ô tô tự lái
### Input: 
- File ảnh 2D( ảnh chụp từ ô tô tự lái google)
- Đọc File tọa độ GPS ( ĐỊnh dạng .txt ) 7 cột( Trong đó có 1 cột GPS)
### Output 
- Convert Ảnh 2D sang JPG (Đang nghiên cứu)
- Đọc file tọa độ GPS: Lấy ra tạo độ GPS ( Đang nghiên cứu xem GPS này và t ở file sample_DriveMMS.txt là một không)
- Khi click quỹ tích MMS thì ảnh tương ứng ở ảnh 2D sẽ hiện ra
