import matplotlib.pyplot as plt

with open("org_freq.txt") as f:
    org_freq = [float(freq[0:-1]) for freq in f.readlines()]
    f.close()
with open("inp.txt") as f:
    inp = [float(freq[0:-1]) for freq in f.readlines()]
    f.close()
with open("ext_imag_freq.txt") as f:
    imag_freq = [float(freq[0:-1]) for freq in f.readlines()]
    f.close()
with open("ext_real_freq.txt") as f:
    real_freq = [float(freq[0:-1]) for freq in f.readlines()]
    f.close()
with open("ext_complex_inv.txt") as f:
    complex_inv = [list(map(float, freq[1:-2].split(",")))[0]
                   for freq in f.readlines()]
    f.close()

N = len(inp)
X = [x / N for x in range(0, N)]

fig, axis = plt.subplots(2, 1)
axis[0].plot(X, inp)
axis[0].set_title("in")
axis[1].plot(X, complex_inv)
axis[1].set_title("out")
plt.show()
