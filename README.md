# 🏥 Hospital Management System (C Project)
📌 Overview

This is a console-based Hospital Management System written in C.  
It simulates a real-world hospital environment with multiple user roles, including patients, doctors, nurses, administrators, and directors.

Above `src` folder contains C source files along with text files used in the program for persistent storage.  
`Documentation` file contains pseudocode, data structures, and function-by-function explanations.

The system handles:

- Patient registration & login
- Appointment booking, rescheduling, and cancellation
- Billing & payments (card, online banking, cash)
- Medical record management
- Staff registration & reporting
- Inventory management
- Hospital-wide reporting

All data is stored using text files to keep the project lightweight and beginner-friendly.

---

🧑‍💼 User Roles & Features

👤 Patient  
- Register & Login  
- Book appointments with doctors  
- Reschedule or cancel appointments  
- View billing details  
- Make payments (card, online banking, cash)  
- Access medical history  

👨‍⚕️ Doctor  
- Secure login  
- View assigned appointments  
- Add medical records (diagnosis, prescriptions, notes)  
- View patient history  

👩‍⚕️ Nurse  
- Secure login  
- View doctor schedules  
- Add/View/Search inventory items  
- Generate staff & inventory reports  

🛠 Administrator  
- Secure login  
- Register patients, doctors, and nurses  
- View/Search patient records  
- Manage hospital inventory  

👨‍💼 Director  
- Secure login  
- Add/View administrators  
- Generate staff reports  
- View appointment summaries  

---

💳 Payment Methods Supported
- Card (with validation and retry attempts)  
- Online Banking (username/password confirmation)  
- Cash  

Payments are automatically linked to billing records.

---

📁 Files Used (Persistent Storage)

| File Name         | Purpose                          |
|-------------------|----------------------------------|
| patients.txt      | Registered patients              |
| doctors.txt       | Registered doctors               |
| nurses.txt        | Registered nurses                |
| admin.txt         | Administrator accounts           |
| director.txt      | Director accounts                |
| appointments.txt  | Appointment records              |
| medicalrecords.txt| Patient medical history          |
| inventory.txt     | Hospital inventory               |
| billing.txt       | Billing & payment records        |

---

🧠 Key Concepts Demonstrated
- File handling (read, write, append)  
- Input validation & error handling  
- Role-based access control  
- Modular programming in C  
- Unique ID generation (patients, doctors, appointments)  
- Date validation (future date checks)  

---

⚠ Limitations
- Uses plain text files instead of a database  
- Passwords are not encrypted  
- Console-based UI only  
- Limited error handling for concurrent access  

---

👨‍🎓 Author Notes
This project is suitable for:
- Beginner to intermediate C learners  
- Academic coursework  
- Understanding real-world system design logic  
