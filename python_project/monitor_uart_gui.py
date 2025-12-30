import tkinter as tk
from tkinter import ttk, messagebox
import serial
from serial.tools import list_ports


class UartGui(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("STM32 UART Monitor (Simple)")
        self.geometry("780x480")

        self.ser = None

        # --- Top controls ---
        top = ttk.Frame(self, padding=10)
        top.pack(fill="x")

        ttk.Label(top, text="COM Port:").pack(side="left")
        self.port_var = tk.StringVar()
        self.port_combo = ttk.Combobox(top, textvariable=self.port_var, width=12, state="readonly")
        self.port_combo.pack(side="left", padx=(6, 12))

        ttk.Button(top, text="Refresh", command=self.refresh_ports).pack(side="left")

        ttk.Label(top, text="Baud:").pack(side="left", padx=(12, 0))
        self.baud_var = tk.StringVar(value="115200")
        ttk.Entry(top, textvariable=self.baud_var, width=10).pack(side="left", padx=(6, 12))

        ttk.Button(top, text="Start", command=self.start).pack(side="left")

        ttk.Button(top, text="Stop", command=self.stop).pack(side="left", padx=(6, 0))

        self.status_var = tk.StringVar(value="Idle")
        ttk.Label(top, textvariable=self.status_var).pack(side="right")

        # --- Receive box ---
        mid = ttk.Frame(self, padding=(10, 0, 10, 10))
        mid.pack(fill="both", expand=True)

        self.rx_text = tk.Text(mid, wrap="word")
        self.rx_text.pack(side="left", fill="both", expand=True)

        scroll = ttk.Scrollbar(mid, command=self.rx_text.yview)
        scroll.pack(side="right", fill="y")
        self.rx_text.configure(yscrollcommand=scroll.set)

        # --- Send controls ---
        bottom = ttk.Frame(self, padding=10)
        bottom.pack(fill="x")

        ttk.Label(bottom, text="Send:").pack(side="left")
        self.tx_var = tk.StringVar()
        tx_entry = ttk.Entry(bottom, textvariable=self.tx_var)
        tx_entry.pack(side="left", fill="x", expand=True, padx=(6, 8))
        tx_entry.bind("<Return>", lambda _e: self.send())

        ttk.Button(bottom, text="Send", command=self.send).pack(side="left")

        # Init ports and close behavior
        self.refresh_ports()
        self.protocol("WM_DELETE_WINDOW", self.on_close)

    def refresh_ports(self):
        ports = [p.device for p in list_ports.comports()]
        self.port_combo["values"] = ports
        if ports and not self.port_var.get():
            self.port_var.set(ports[0])

    def start(self):
        # Minimal "connect": open once, then keep reading until app closes
        if self.ser and self.ser.is_open:
            messagebox.showinfo("Info", "Already started.")
            return

        port = self.port_var.get().strip()
        if not port:
            messagebox.showerror("Error", "Select a COM port.")
            return

        try:
            baud = int(self.baud_var.get().strip())
        except ValueError:
            messagebox.showerror("Error", "Baud rate must be a number (e.g., 115200).")
            return

        try:
            self.ser = serial.Serial(port=port, baudrate=baud, timeout=0)  # non-blocking
            self.status_var.set(f"Running: {port} @ {baud}")
            self.log_line(f"[OPEN] {port} @ {baud}")
            self.poll_serial()
        except serial.SerialException as e:
            messagebox.showerror("Serial error", str(e))
            self.status_var.set("Idle")

    def stop(self):
        if self.ser and self.ser.is_open:
            try:
                self.ser.close()
            except Exception:
                pass
        self.status_var.set("Idle")
        self.log_line("[CLOSE] Stopped")

    def poll_serial(self):
        if not (self.ser and self.ser.is_open):
            return

        try:
            n = self.ser.in_waiting
            if n:
                data = self.ser.read(n)
                text = data.decode("utf-8", errors="replace")
                # show bytes as numbers (0–255)
                # self.rx_text.insert("end", " ".join(str(b) for b in data) + "\n")
                # self.rx_text.insert("end", data.hex(" ").upper() + "\n")
                self.rx_text.insert("end", f"[Received Hex] {data.hex(' ').upper()}\n")
                # self.rx_text.insert("end", text)
                # self.rx_text.see("end")
        except serial.SerialException as e:
            self.log_line(f"\n[ERROR] {e}\n")
            self.status_var.set("Error")
            return

        self.after(50, self.poll_serial)

    def send(self):
        if not (self.ser and self.ser.is_open):
            messagebox.showerror("Error", "Not started yet. Click Start first.")
            return

        msg = self.tx_var.get()
        if not msg:
            return

        try:
            # Common STM32 pattern: send with CRLF
            #payload = (msg + "\r\n").encode("utf-8")
            #self.ser.write(payload)
            #self.log_line(f"\n[Transmitted message] {msg}\n")
            #self.tx_var.set("")
            # Example input: "01 0A FF 00"  or "010AFF00"
            hex_str = msg.replace("0x", "").replace(",", " ").strip()
            payload = bytes.fromhex(hex_str)      # converts hex string -> bytes
            self.ser.write(payload)
            self.log_line(f"\n[Transmitted HEX] {payload.hex(' ').upper()}\n")
            self.tx_var.set("")
            
        except serial.SerialException as e:
            messagebox.showerror("Serial error", str(e))

    def log_line(self, s: str):
        self.rx_text.insert("end", s + "\n")
        self.rx_text.see("end")

    def on_close(self):
        try:
            if self.ser and self.ser.is_open:
                self.ser.close()
        except Exception:
            pass
        self.destroy()


if __name__ == "__main__":
    UartGui().mainloop()
