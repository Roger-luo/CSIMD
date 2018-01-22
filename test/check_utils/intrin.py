def loadu(x):
    ymm = []
    for each in x:
        ymm.extend([each.real, each.imag])
    return ymm


def hadd_pd(x, y):
    return [x[0] + x[1], y[0] + y[1], x[2] + x[3], y[2] + y[3]]


def mul_pd(x, y):
    return [a * b for a, b in zip(x, y)]
