# hello.py -- frozen demo: runs at import time as a smoke test.
import minios

t = minios.time_ms()
print("minios.time_ms() =", t)

try:
    h, m, s = minios.rtc()
    print("minios.rtc() = {:02d}:{:02d}:{:02d}".format(h, m, s))
except OSError:
    print("rtc: unavailable")

try:
    w, h, p = minios.fb_info()
    print("minios.fb_info() = {}x{}, pitch={}".format(w, h, p))
except OSError:
    print("fb_info: unavailable")
