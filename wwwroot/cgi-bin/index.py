import os
import sys

print("Hello from Pythono, seus putosI!")
print("SERVER_PROTOCOL: ", os.environ["SERVER_PROTOCOL"])
body = sys.argv[1]
print(body)
print("--------------------------------------")
print("Request body payload size: " + str(len(body)))