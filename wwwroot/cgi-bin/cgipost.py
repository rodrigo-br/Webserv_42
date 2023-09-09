#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cgi
import sys
import os

print()

sys.stdout.reconfigure(encoding='utf-8')

# Gera a página HTML
print("<html>")
print("<head><title>Script CGI Python</title></head>")
print("<body>")
print(f"<h1>Ola, {os.environ.get('NAME')}!</h1>")
print("<p>Eu sou um script CGI Python COM POST.</p>")
print("</body>")
print("</html>")
