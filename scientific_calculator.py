import math

class ScientificCalculator:
    """Advanced Scientific Task & Calculation Engine for G.L.A.S.S."""
    
    @staticmethod
    def add(a: float, b: float) -> float:
        return a + b

    @staticmethod
    def subtract(a: float, b: float) -> float:
        return a - b

    @staticmethod
    def multiply(a: float, b: float) -> float:
        return a * b

    @staticmethod
    def divide(a: float, b: float) -> float:
        if b == 0:
            raise ValueError("Division by zero is undefined.")
        return a / b

    @staticmethod
    def power(base: float, exponent: float) -> float:
        return math.pow(base, exponent)

    @staticmethod
    def square_root(x: float) -> float:
        if x < 0:
            raise ValueError("Cannot calculate square root of a negative number.")
        return math.sqrt(x)

    @staticmethod
    def sin(rad: float) -> float:
        return math.sin(rad)

    @staticmethod
    def cos(rad: float) -> float:
        return math.cos(rad)

    @staticmethod
    def tan(rad: float) -> float:
        return math.tan(rad)

    @staticmethod
    def log(x: float, base: float = math.e) -> float:
        return math.log(x, base)

    @staticmethod
    def factorial(n: int) -> int:
        return math.factorial(n)

if __name__ == "__main__":
    calc = ScientificCalculator()
    print("--- G.L.A.S.S. Scientific Calculator Test ---")
    print("2^10 =", calc.power(2, 10))
    print("sqrt(144) =", calc.square_root(144))
    print("sin(pi/2) =", calc.sin(math.pi / 2))
    print("log10(1000) =", calc.log(1000, 10))
    print("5! =", calc.factorial(5))
