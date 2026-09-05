# 🛡️ StealthGuard
### Intrusion Detection System with File Integrity Monitoring

> A lightweight, dual-layer security monitoring system built on **Kali Linux** using **Bash Shell Scripting** and **Python 3**.  
> Built as an Operating Systems Lab Project — IIUC CSE Department | 6th Semester | Spring 2026

---

## 📌 What is StealthGuard?

StealthGuard is a silent security tool that automatically monitors your Linux system by:
- Taking **screenshots** of the desktop at regular intervals
- Recording **top 10 running processes** at each capture
- Verifying **file integrity** using SHA-256 cryptographic hashing
- Detecting **screen changes** between captures
- Watching for **file tampering** in real time
- Sending **email alerts** automatically when anything suspicious happens

Think of it as a **silent CCTV camera for your operating system.**

---

## 🗂️ Project Structure

```
stealthguard/
├── stealthguard.sh      # Shell Automation Engine (main controller)
├── verify.py            # Python Integrity Auditor (verifier)
└── README.md
```

### Two Layers

| File | Language | Role |
|---|---|---|
| `stealthguard.sh` | Bash / Shell | Takes screenshot, saves processes, calls Python, sends emails, watches folder |
| `verify.py` | Python 3 | Checks file integrity, calculates SHA-256 hash, compares hashes, writes audit log |

---

## ⚙️ Requirements

**Operating System:** Kali Linux

**Install dependencies:**
```bash
sudo apt update
sudo apt install scrot mutt zip inotify-tools python3 -y
```

| Tool | Purpose |
|---|---|
| `scrot` | Takes screenshots |
| `mutt` | Sends emails from terminal |
| `zip` | Creates ZIP archives |
| `inotify-tools` | Real-time folder watching |
| `python3` | Runs the integrity auditor |

---

## 🚀 Setup

```bash
# 1. Clone the repo
git clone https://github.com/yourusername/stealthguard.git
cd stealthguard

# 2. Give execute permission
chmod +x stealthguard.sh

# 3. Create the security vault
sudo mkdir /SecurityVault
sudo chmod 777 /SecurityVault

# 4. Configure email (Gmail)
nano ~/.muttrc
```

Paste this in `~/.muttrc`:
```
set from = "yourgmail@gmail.com"
set realname = "StealthGuard"
set smtp_url = "smtps://yourgmail%40gmail.com@smtp.gmail.com:465"
set smtp_pass = "YOUR_16_DIGIT_APP_PASSWORD"
set ssl_starttls = yes
set ssl_force_tls = yes
```

> **Note:** Get your App Password from Google Account → Security → 2-Step Verification → App Passwords

```bash
# 5. Update email addresses in stealthguard.sh
nano stealthguard.sh
# Edit these two lines at the top:
# TO_EMAIL="recipient@gmail.com"
# FROM_EMAIL="yourgmail@gmail.com"
```

---

## 📋 Usage

```bash
# Manual single capture
./stealthguard.sh --capture

# Auto mode — captures every 10 seconds automatically
./stealthguard.sh

# Zip all captures and send to email
./stealthguard.sh --sendemail

# Watch folder for real-time file modifications
./stealthguard.sh --watchfolder

# Show help
./stealthguard.sh --help
```

---

## ✅ Features

| # | Feature | Description |
|---|---|---|
| 1 | Screenshot Capture | Silently captures full desktop screenshot using `scrot` |
| 2 | Timestamp File Naming | Every file named with exact date and time — no overwrites |
| 3 | Process Monitoring | Top 10 running processes by CPU saved alongside each capture |
| 4 | Zero-Byte Detection | Corrupt/empty captures flagged immediately before logging |
| 5 | SHA-256 Hashing | Unique cryptographic fingerprint calculated for every screenshot |
| 6 | Change Detection | Hash compared with previous capture — alerts on any difference |
| 7 | Persistent Audit Log | All events logged permanently to `system_security_audit.log` |
| 8 | Manual Trigger | `--capture` flag for on-demand single capture |
| 9 | Auto Loop Mode | Captures every 10 seconds automatically with no user input |
| 10 | Zip + Email Report | Compresses all evidence and emails as attachment on demand |
| 11 | Screen Change Alert | Auto email when SHA-256 hash mismatch detected |
| 12 | Folder Watch + Alert | Real-time monitoring of `/SecurityVault` — instant email on tampering |

---

## 📁 Files Created Per Capture

```
/SecurityVault/
├── capture_2026-06-24_00-17-28.png       ← Desktop screenshot
├── processes_2026-06-24_00-17-28.txt     ← Top 10 processes
├── system_security_audit.log             ← Full audit history
└── .previous_hash                        ← Hidden SHA-256 hash file
```

---

## 🔄 How It Works

```
Trigger (manual / auto)
        ↓
Check /SecurityVault exists
        ↓
Take Screenshot (scrot)
        ↓
Save Process Snapshot (ps aux)
        ↓
Python Verifier called
        ↓
Zero-Byte Check → fail if empty
        ↓
SHA-256 Hash Calculated
        ↓
Compare with .previous_hash
        ↓
FIRST RUN / NO CHANGE / ALERT
        ↓
Write to Audit Log
        ↓
Send Alert Email (if ALERT)
        ↓
Wait → Repeat
```

---

## 📧 Email Alerts

StealthGuard sends automatic emails in two situations:

**1. Screen Change Detected**
```
Subject: ALERT - StealthGuard Detected Screen Change!

WARNING: Screen change detected on your system!
- File     : capture_2026-06-24_00-18-20.png
- New Hash : c705d3b533c50bb91c45...
- Time     : 2026-06-24_00-18-20
```

**2. File Modification Detected**
```
Subject: ALERT - File Modified: capture_xxx.png

WARNING: A file was modified inside /SecurityVault!
- File     : capture_2026-06-24_15-27-35.png
- Event    : MODIFY
- Location : /SecurityVault
- Time     : Wed Jun 24 03:36:12 PM EDT 2026
```

---

## 🧠 OS Concepts Demonstrated

| Concept | Where |
|---|---|
| Process Management | `ps aux` process monitoring |
| File System Operations | Creating, reading, writing in `/SecurityVault` |
| Shell Scripting | Functions, loops, conditions in `stealthguard.sh` |
| Inter-Process Communication | Shell calls Python via arguments, Python reads `sys.argv` |
| Cryptographic Hashing | SHA-256 using Python `hashlib` |
| File Integrity Monitoring | Zero-byte check + hash comparison |
| Persistent Logging | Append-mode audit log |
| Signal Handling | `Ctrl+C` stops auto loop (SIGINT) |
| Real-Time Event Monitoring | `inotifywait` folder watcher |
| Email Automation | `mutt` sends alerts from terminal |

---

## 👥 Team

| Name | Student ID |
|---|---|
| Tahasina Tasnim Afra | C233456 |
| Nusrat Jahan | C233464 |
| Asliraf Samaylan | C233446 |

**Supervisor:** Ms. Sauda Adiv Hanum — Lecturer, CSE, IIUC

---

## 🏫 Course Info

| | |
|---|---|
| University | International Islamic University Chittagong (IIUC) |
| Department | Computer Science and Engineering |
| Course | Operating Systems Lab |
| Semester | 6th — Spring 2026 |
| Section | 6BF |

---

## 📄 License

This project was developed for academic purposes as part of the IIUC CSE Operating Systems Laboratory.

---

<div align="center">
  <b>StealthGuard</b> — Built with 🖤 on Kali Linux
</div>
