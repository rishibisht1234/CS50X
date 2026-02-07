def main():
    number = input("Number: ").strip()

    if isValid(number):
        print(cardType(number))
    else:
        print("INVALID")


def isValid(number):
    if not number.isdigit():
        return False

    total = 0
    reverse = number[::-1]

    for i, digit in enumerate(reverse):
        n = int(digit)
        if i % 2 == 1:
            n *= 2
            if n > 9:
                n -= 9
        total += n

    return total % 10 == 0


def cardType(number):
    length = len(number)

    if length == 15 and number.startswith(("34", "37")):
        return "AMEX"
    elif length == 16 and number.startswith(("51", "52", "53", "54", "55")):
        return "MASTERCARD"
    elif length in (13, 16) and number.startswith("4"):
        return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
