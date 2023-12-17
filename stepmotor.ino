/*
  Điều Khiển Động Cơ Bước Arduino Sketch

  Đây là đoạn mã Arduino mô phỏng việc điều khiển một động cơ bước sử dụng các nút nhấn
  ngoại vi (chuyển động tiến, chuyển động lùi và dừng) và dữ liệu nhập từ Serial Monitor.
  Động cơ bước có thể di chuyển theo hướng tiến hoặc lùi với số bước được xác định, và
  có nút dừng để dừng động cơ bất cứ lúc nào.

  Mã nguồn bao gồm các hàm tạo xung PWM để điều khiển động cơ bước, xử lý đầu vào từ nút,
  và hiển thị trạng thái hệ thống qua Serial Monitor. Ngoài ra, nó có thể nhận dữ liệu từ
  Serial Monitor để xác định số bước mà động cơ sẽ thực hiện ở mỗi hướng.

  Nhóm tác giả: [Gia Bảo, Huy Hoàng, Thanh Tùng]
  Ngày: [29-11-2023]
  Phiên bản: 1.0

  Kết Nối Chân:
  - Pulse (puL_): Kết nối đến đầu vào Pulse của trình điều khiển động cơ bước
  - Direction (diR_): Kết nối đến đầu vào Direction của trình điều khiển động cơ bước
  - Nút Tiến (forward_): Kết nối đến đầu vào nút tiến
  - Nút Lùi (reverse_): Kết nối đến đầu vào nút lùi
  - Nút Dừng (stop_): Kết nối đến đầu vào nút dừng

  Lệnh Serial:
  - Nhập một số nguyên dương hoặc âm để di chuyển động cơ theo hướng tiến hoặc lùi.

  Ghi Chú:
  - Mã sử dụng ngắt để phát hiện khi nào nút dừng được nhấn.
  - Hãy đảm bảo kết nối đúng và cung cấp nguồn điện phù hợp cho trình điều khiển động cơ bước.
*/

// [Phần mã của bạn điều tiếp theo ở đây]


// Định nghĩa các chân kết nối và cấu trúc cho hệ thống
byte const puL_ = 4;     // Chân kết nối đến Motor Driver - Pulse
byte const diR_ = 5;     // Chân kết nối đến Motor Driver - Direction
byte const forward_ = 3; // Chân nút nhấn Forward
byte const reverse_ = 6; // Chân nút nhấn Reverse
byte const stop_ = 2;    // Chân nút nhấn Stop (không được thay đổi)

// Cấu trúc chứa trạng thái và thông tin của stepper motor
struct
{
  bool current_button[3] = {0, 0, 0}; // forward, reverse, stop
  int totalMun_ = 20;                 // Số bước tối đa cho mỗi lần chuyển động
  int pulse_delay = 100;              // Thời gian giữa các xung PWM
  int count;                          // Biến đếm số bước
  int inputValue;                     // Giá trị nhập từ Serial Monitor
  String inputString;                 // Chuỗi để xử lý dữ liệu nhập từ Serial Monitor
} stepmotor;

// Hàm thiết lập cho Arduino
void setup()
{
  // Cấu hình chân I/O
  pinMode(puL_, OUTPUT);
  pinMode(diR_, OUTPUT);
  pinMode(stop_, INPUT_PULLUP);
  pinMode(forward_, INPUT_PULLUP);
  pinMode(reverse_, INPUT_PULLUP);

  // Kết nối hàm xử lý ngắt khi nút Stop được nhấn
  attachInterrupt(digitalPinToInterrupt(stop_), stopFun, FALLING);

  // Thiết lập trạng thái ban đầu
  digitalWrite(puL_, 0);
  Serial.begin(9600);
  while (!Serial)
  {
    // Chờ cho đến khi Serial sẵn sàng
  }
  menuDis();
  delay(1000);
}

// Hàm tạo xung PWM cho stepper motor
void pwm()
{
  digitalWrite(puL_, 1);
  delay(stepmotor.pulse_delay);
  digitalWrite(puL_, 0);
  delay(stepmotor.pulse_delay);
}

// Hàm thực hiện chuyển động của stepper motor
void stepFun(int valuIn)
{
  int lackPul;
  lackPul += valuIn;
  // if (lackPul != stepmotor.totalMun_)
  // {
  //   lackPul = (lackPul > stepmotor.totalMun_) ? lackPul - stepmotor.totalMun_ : stepmotor.totalMun_ - lackPul;
  // }
  for (int i{1}; i <= lackPul; ++i)
  {
    pwm();
    buttonFun();
    stepmotor.count++;
    if (stepmotor.current_button[2] == 1)
    {
      break;
      menuDis();
    }
  }
  resValueBut();
}

// Hàm thực hiện chuyển động theo hướng Forward
void forward()
{
  menuDis();
  digitalWrite(diR_, 1);
  stepFun(stepmotor.totalMun_);
}

// Hàm thực hiện chuyển động theo hướng Reverse
void reverse()
{
  menuDis();
  digitalWrite(diR_, 0);
  stepFun(stepmotor.totalMun_);
}

// Hàm xử lý sự kiện nút nhấn
void buttonFun()
{
  // Xử lý khi nút Forward được nhấn
  if (digitalRead(forward_) == 0 && !stepmotor.current_button[0])
  {
    stepmotor.current_button[0] = 1; // forward
    stepmotor.current_button[1] = 0; // reverse
    forward();
  }
  // Xử lý khi nút Reverse được nhấn
  else if (digitalRead(reverse_) == 0 && !stepmotor.current_button[1])
  {
    stepmotor.current_button[0] = 0; // forward
    stepmotor.current_button[1] = 1; // reverse
    reverse();
  }
  return;
}

// Hàm xử lý sự kiện nút Stop
void stopFun()
{
  // Xử lý khi nút Stop được nhấn
  if (digitalRead(stop_) == 0 && stepmotor.current_button[2] != 1)
  {
    digitalWrite(puL_, 1);
    stepmotor.current_button[2] = 1;
  }
}

// Hàm đặt lại giá trị của nút và các chân I/O khi kết thúc chuyển động
void resValueBut()
{
  stepmotor.current_button[0] = 0; // forward
  stepmotor.current_button[1] = 0; // reverse
  stepmotor.current_button[2] = 0; // stop
  digitalWrite(puL_, 0);
  digitalWrite(diR_, 0);
  menuDis();
  stepmotor.count = 0;
  stepmotor.inputValue = 0;
}

// Hàm hiển thị trạng thái của hệ thống
void menuDis()
{
  for (int i = 0; i < 60; i++)
  {
    Serial.println("\n");
  }
  Serial.println("Da_bat_Arduino\t | \tGBAO-HHoang-TTung|\tVIP-CODE|  \t\t  |");
  Serial.println("_________________| \t_________________| \t________| \t__________| \t");
  Serial.println("Forward_stepMotor| \tReverse_stepMotor| \tSTOP_!!!| \tTotal_Step| \t");
  Serial.println("V________________| \tV________________| \tV_______| \tV_________| \t");
  Serial.print(stepmotor.current_button[0] + String("\t\t\t") + stepmotor.current_button[1] + String("\t\t\t"));
  Serial.println(stepmotor.current_button[2] + String("\t\t") + stepmotor.count);
  Serial.print("So buoc vi chinh: ");
  Serial.println(stepmotor.inputValue);
}

// Hàm chính của chương trình
void loop()
{
  // Gọi hàm xử lý nút
  buttonFun();

  // Kiểm tra xem có dữ liệu từ Serial Monitor không
  while (Serial.available() > 0)
  {
    // Đọc một ký tự từ Serial Monitor
    char currentChar = Serial.read();

    // Kiểm tra xem ký tự có phải là số hoặc dấu trừ không
    if (isdigit(currentChar) || currentChar == '-')
    {
      // Nếu là số hoặc dấu trừ, thêm vào chuỗi
      stepmotor.inputString += currentChar;
    }
    // Nếu gặp dấu xuống dòng, xử lý chuỗi số
    else if (currentChar == '\n')
    {
      // Chuyển đổi chuỗi thành số nguyên
      stepmotor.inputValue = stepmotor.inputString.toInt();

      // Gọi hàm hiển thị menu và xử lý số nguyên
      menuDis();
      stepFun(stepmotor.inputValue);

      // Đặt lại chuỗi để chuẩn bị cho lần nhập tiếp theo
      stepmotor.inputString = "";
    }
    // Nếu ký tự không phải là số hoặc dấu trừ, xuất thông báo lỗi
    else
    {
      Serial.println("Khong phai so nguyen!!!!!!! ");
    }
  }
}
