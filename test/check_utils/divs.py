from intrin import *

x = [i + (i + 1) * 1.j for i in range(4)]
print(x)
c = 2.0 + 3.0j
norm = abs(c)**2

ymm15 = [c.real / norm, c.imag / norm, c.real / norm, c.imag / norm]
ymm14 = [-c.imag / norm, c.real / norm, -c.imag / norm, c.real / norm]

ymm0, ymm1 = loadu(x)[:4], loadu(x)[4:]
print(ymm0, ymm1)

ymm2_1, ymm2_2 = mul_pd(ymm0, ymm15), mul_pd(ymm1, ymm15)
ymm2 = hadd_pd(ymm2_1, ymm2_2)

print(ymm2)
