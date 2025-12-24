# 🚀 Born2beRoot - 42 School Project

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![VirtualBox](https://img.shields.io/badge/VirtualBox-183A61?style=for-the-badge&logo=virtualbox&logoColor=white)
![Debian](https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white)
![SSH](https://img.shields.io/badge/SSH-000000?style=for-the-badge&logo=openssh&logoColor=white)

**⭐ Master System Administration Fundamentals ⭐**

*Complete server setup and configuration in a virtual environment*

[![Build Status](https://img.shields.io/badge/setup-complete-brightgreen?style=flat-square)](https://github.com/your-username/born2beroot)
[![Norminette](https://img.shields.io/badge/norminette-compliant-brightgreen?style=flat-square)](https://github.com/42School/norminette)
[![Score](https://img.shields.io/badge/score-125%2F100-brightgreen?style=flat-square)](#)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [🏗️ Setup Requirements](#️-setup-requirements)
- [🚀 Installation](#-installation)
- [⚙️ Configuration](#️-configuration)
- [🛡️ Security](#️-security)
- [📊 Services](#-services)
- [🧪 Testing](#-testing)
- [📁 Project Structure](#-project-structure)
- [🤝 Contributing](#-contributing)
- [🙏 Acknowledgments](#-acknowledgments)

---

## 🎯 Overview

<div align="center">

### **The System Administrator Challenge**

Born2beRoot is a **42 School** system administration project that challenges you to set up a fully functional **Linux server** in a virtual machine. Master the fundamentals of server configuration, security, and service management!

🖥️ **Think you can configure a production-ready server?** Prove your sysadmin skills!

</div>

### 🎯 Project Goals

- **Virtual Machine Setup**: Configure a Debian-based server in VirtualBox
- **User Management**: Create users, groups, and permissions
- **Security Hardening**: Implement SSH, firewall, and encryption
- **Service Configuration**: Set up web server, monitoring, and automation
- **Partitioning**: Logical volume management and disk partitioning
- **Scripting**: Automated setup and monitoring scripts

---

## ✨ Features

<div align="center">

| 🚀 Feature | Description |
|------------|-------------|
| **🔐 SSH Configuration** | Secure remote access with key authentication |
| **🛡️ Firewall Setup** | UFW configuration for network security |
| **👥 User Management** | Sudo, groups, and password policies |
| **💾 LVM Partitioning** | Logical volumes for flexible storage |
| **🌐 Web Server** | Nginx/Apache with SSL certificates |
| **📊 Monitoring** | System monitoring and cron jobs |
| **🔄 Automation** | Setup scripts and service management |
| **📈 Performance** | Optimization and resource monitoring |

</div>

---

## 🏗️ Setup Requirements

### Hardware Requirements
- **RAM**: Minimum 1024 MB (recommended 2048 MB)
- **Storage**: 8 GB available disk space
- **CPU**: 1 core minimum (2 recommended)

### Software Requirements
- **VirtualBox**: Version 6.0 or higher
- **Debian ISO**: Debian 10 or 11 (netinst recommended)
- **Host OS**: Linux, macOS, or Windows

---

## 🚀 Installation

### Step 1: Download Debian ISO
```bash
# Download Debian netinst ISO
wget https://www.debian.org/CD/netinst/
```

### Step 2: Create Virtual Machine
1. Open VirtualBox
2. Create new VM with Debian (64-bit)
3. Allocate resources (RAM, CPU, disk)
4. Mount the Debian ISO
5. Start the VM and begin installation

### Step 3: Basic Installation
- Select language and location
- Configure hostname and domain
- Create root password
- Create user account
- Partition disk (use LVM for bonus)

---

## ⚙️ Configuration

### User and Group Setup
```bash
# Create user with sudo privileges
sudo adduser username
sudo usermod -aG sudo username

# Create evaluation user
sudo adduser evaluator
```

### SSH Configuration
```bash
# Install and configure SSH
sudo apt update
sudo apt install openssh-server

# Configure SSH for security
sudo nano /etc/ssh/sshd_config
# Change port, disable root login, etc.
sudo systemctl restart ssh
```

### Firewall Setup
```bash
# Install and configure UFW
sudo apt install ufw
sudo ufw enable
sudo ufw allow ssh
sudo ufw allow http
sudo ufw allow https
```

---

## 🛡️ Security

### Password Policy
- **Minimum length**: 10 characters
- **Complexity**: Uppercase, lowercase, numbers, symbols
- **Expiration**: 30 days maximum

### SSH Security
- **Port**: Changed from default 22
- **Root login**: Disabled
- **Password authentication**: Disabled (key-only)
- **Allowed users**: Restricted access

### Firewall Rules
- **Default**: Deny all incoming
- **Allowed**: SSH, HTTP, HTTPS
- **Monitoring**: UFW status and logging

---

## 📊 Services

### Web Server (Bonus)
```bash
# Install Nginx
sudo apt install nginx
sudo systemctl enable nginx

# Configure SSL
sudo apt install certbot
sudo certbot --nginx
```

### Monitoring Scripts
```bash
# Create monitoring script
sudo nano /usr/local/bin/monitoring.sh
# Add system info, disk usage, etc.

# Add to cron for automated monitoring
sudo crontab -e
# @reboot /usr/local/bin/monitoring.sh
```

---

## 🧪 Testing

### Evaluation Checklist
- [ ] VM setup and partitioning
- [ ] User creation and permissions
- [ ] SSH configuration and security
- [ ] Firewall rules and status
- [ ] Sudo configuration
- [ ] Password policies
- [ ] Services and automation
- [ ] Bonus features

### Testing Commands
```bash
# Check SSH configuration
sudo sshd -t

# Verify firewall status
sudo ufw status

# Test sudo access
sudo whoami

# Check services
sudo systemctl status nginx
```

---

## 📁 Project Structure

```
born2beroot/
├── signature.txt          # Project signature for evaluation
├── README.md             # This file
└── scripts/              # (Optional) Setup scripts
    ├── setup.sh
    └── monitoring.sh
```

---

## 🤝 Contributing

<div align="center">

**This is a 42 School project - contributions follow 42's peer-to-peer evaluation system.**

- 📝 **Code Reviews**: Submit for peer evaluation
- 🐛 **Bug Reports**: Open issues for problems found
- 💡 **Suggestions**: Discuss improvements with peers

</div>

---

## 🙏 Acknowledgments

<div align="center">

**Special thanks to:**

- **42 School** for the challenging curriculum
- **Peer evaluators** for constructive feedback
- **Open source community** for Linux and tools

---

**Built with ❤️ at 42 School**

[![42 Born2beRoot](https://img.shields.io/badge/42-Born2beRoot-000000?style=for-the-badge&logo=42&logoColor=white)](#)

</div>