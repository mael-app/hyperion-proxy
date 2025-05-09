# Hyperion Proxy

A lightweight, CLI-based C++ alternative to Ngrok — enables **secure traffic redirection** from a public host to devices on private networks.

---

## 🔧 Overview

Hyperion Proxy allows forwarding of incoming traffic from a **public IP and port** to a **private device's IP and port**, effectively bypassing NAT/firewall restrictions.

It works in **2 modes**:

### 🔹 Host (Server)
- Runs on a public server.
- Listens for incoming traffic and configuration from devices.
- Handles routing between clients and destination machines.

### 🔹 Device (Client)
- Connects to the host.
- Forwards traffic to a local destination IP/port.

---

## 🛠 Features

- 🔁 Persistent connection between host and devices.
- 🔌 Port forwarding from **public_port → destination_host:destination_port**.
- 🌐 Supports both **raw sockets** and **websockets** (to bypass strict firewalls).
- 🔧 Configurable via simple YAML file.

---

## 📁 Example Routing

```yaml
# config.yaml
mappings:
  - public_port: 1234
    destination_host: "192.168.1.10"
    destination_port: 25565
```
This means:
> Incoming traffic to port 1234 on the host will be forwarded to 192.168.1.10:25565 on the device.
