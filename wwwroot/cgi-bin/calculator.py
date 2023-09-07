#!/usr/bin/env python3

print("Content-Type: text/html\n")  # Adicione uma quebra de linha aqui
print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("  <title>Simple Calculator</title>")
print("</head>")
print("<body>")
print("  <h1>Simple Calculator</h1>")
print("  <form method='POST' action='/cgi-bin/calculator.py'>")
print("    <input type='number' name='num1' placeholder='Enter number 1' required><br><br>")
print("    <input type='number' name='num2' placeholder='Enter number 2' required><br><br>")
print("    <select name='operator'>")
print("      <option value='add'>Addition (+)</option>")
print("      <option value='subtract'>Subtraction (-)</option>")
print("      <option value='multiply'>Multiplication (*)</option>")
print("      <option value='divide'>Division (/)</option>")
print("    </select><br><br>")
print("    <input type='submit' value='Calculate'>")
print("  </form>")

import cgi

form = cgi.FieldStorage()

if "num1" in form and "num2" in form and "operator" in form:
    num1 = float(form["num1"].value)
    num2 = float(form["num2"].value)
    operator = form["operator"].value

    if operator == 'add':
        result = num1 + num2
    elif operator == 'subtract':
        result = num1 - num2
    elif operator == 'multiply':
        result = num1 * num2
    elif operator == 'divide':
        if num2 != 0:
            result = num1 / num2
        else:
            result = "Error: Division by zero is not allowed."

    print(f"  <p>Result: {result}</p>")

print("</body>")
print("</html>")
