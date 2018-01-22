x = [i + (i + 1) * 1.j for i in range(4)]
print(x)
c = 2.0 + 3.0j
norm = abs(c)**2

ymm15 = [c.real / norm, c.imag / norm, c.real / norm, c.imag / norm]
ymm14 = [-c.imag / norm, c.real / norm, -c.imag / norm, c.real / norm]


def loadu(x):
    ymm = []
    for each in x:
        ymm.extend([each.real, each.imag])
    return ymm


ymm0, ymm1 = loadu(x)[:4], loadu(x)[4:]
print(ymm0, ymm1)
