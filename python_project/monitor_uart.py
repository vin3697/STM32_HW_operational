import argparse
import sys
import time
from datetime import datetime

import serial


def open_serial(port: str, baud: int, timeout: float) -> serial.Serial:
    return serial.Serial(
        port=port,
        baudrate=baud,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=timeout,          # read timeout
        write_timeout=1.0,
    )


def fmt_timestamp() -> str:
    return datetime.now().strftime("%H:%M:%S.%f")[:-3]


def safe_ascii(data: bytes) -> str:
    # Replace non-printable bytes so you can still see the stream nicely
    return "".join(chr(b) if 32 <= b <= 126 else "." for b in data)


def main() -> int:
    ap = argparse.ArgumentParser(description="Simple UART monitor for STM32 (ASCII + HEX).")
    ap.add_argument("--port", required=True, help="COM port, e.g. COM5")
    ap.add_argument("--baud", type=int, default=115200, help="Baudrate (default: 115200)")
    ap.add_argument("--timeout", type=float, default=0.2, help="Read timeout in seconds")
    ap.add_argument("--log", default="", help="Optional log file path (appends)")
    ap.add_argument("--hex-only", action="store_true", help="Print only HEX")
    args = ap.parse_args()

    ser = None
    log_f = None
    try:
        ser = open_serial(args.port, args.baud, args.timeout)
        print(f"[+] Opened {args.port} @ {args.baud} baud. Ctrl+C to stop.")

        if args.log:
            log_f = open(args.log, "a", encoding="utf-8")
            log_f.write(f"\n--- UART log start {datetime.now().isoformat()} ({args.port} {args.baud}) ---\n")
            log_f.flush()

        buffer = bytearray()

        while True:
            chunk = ser.read(256)  # read up to 256 bytes per loop
            if not chunk:
                continue

            buffer.extend(chunk)

            # If your STM32 sends \r\n line endings, this prints line-by-line.
            while b"\n" in buffer:
                line, _, rest = buffer.partition(b"\n")
                buffer = bytearray(rest)

                # Keep the original newline behavior
                raw = line.rstrip(b"\r")

                ts = fmt_timestamp()
                hex_str = raw.hex(" ").upper()
                if args.hex_only:
                    out = f"{ts}  {hex_str}"
                else:
                    out = f"{ts}  ASCII: {safe_ascii(raw)}\n{ts}  HEX  : {hex_str}"

                print(out)
                if log_f:
                    log_f.write(out + "\n")
                    log_f.flush()

    except KeyboardInterrupt:
        print("\n[!] Stopped.")
        return 0
    except serial.SerialException as e:
        print(f"[ERROR] Serial error: {e}", file=sys.stderr)
        return 2
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        return 3
    finally:
        if log_f:
            log_f.close()
        if ser and ser.is_open:
            ser.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
